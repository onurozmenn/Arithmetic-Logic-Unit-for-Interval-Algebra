// ================================================================================ //
// The NEORV32 RISC-V Processor - https://github.com/stnolting/neorv32             //
// Copyright (c) NEORV32 contributors.                                             //
// Copyright (c) 2020 - 2024 Stephan Nolting. All rights reserved.                 //
// Licensed under the BSD-3-Clause license, see LICENSE for details.               //
// SPDX-License-Identifier: BSD-3-Clause                                           //
// ================================================================================ //

/**
 * @file demo_cfu/main.c
 * @author Stephan Nolting (original template)
 * @brief Example program showing how to use the CFU's custom instructions
 * for interval arithmetic and temporal logic on the NEORV32 processor.
 * @note This C-code is the software counterpart to the custom CFU hardware
 * defined in 'rtl/core/neorv32_cpu_cp_cfu.vhd', which implements the
 * Interval Arithmetic Logic Unit (IALU).
 */

#include <neorv32.h>    // NEORV32 processor runtime environment definitions (e.g., UART, CSRs).
#include <stdint.h>     // Standard integer types (e.g., uint32_t, int16_t).
#include <stdio.h>      // Standard I/O functions (e.g., printf, for sprintf/atof/atoi in full C libraries).
#include <stdlib.h>     // Standard library functions (e.g., atof, atoi for string to number conversions).
#include <intmath.h>    // Custom header for interval arithmetic functions and CFU instruction macros.
#include <stdbool.h>    // Boolean type definition (true/false).
#include <math.h>       // Standard math functions and constants like INFINITY, NAN.

/**********************************************************************//**
 * @name User Configuration
 * @brief Configuration macros for the demo program.
 **************************************************************************/
/**@{*/
/** UART BAUD rate for serial communication. */
#define BAUD_RATE 19200

/**
 * @brief Global polynomial degree for root-finding algorithm.
 * This determines the number of coefficients used in the polynomial `f(x)`.
 */
int degree = 2; // Default polynomial degree (e.g., for ax^2 + bx + c).

/**
 * @brief Array of polynomial coefficients.
 * `coeffs[0]` is for the highest degree term (e.g., a in ax^2),
 * `coeffs[degree]` is the constant term.
 */
float coeffs[3] = {1.0f, -2.05f, 1.05f}; // Default coefficients for a 2nd degree polynomial.
/**@}*/

/**
 * @brief Converts a floating-point number to a string representation.
 * @note This is a custom implementation as full `sprintf` with float support
 * might not be available or optimized on bare-metal embedded systems.
 *
 * @param value The float value to convert.
 * @param buffer The character buffer to store the string.
 * @param precision The number of decimal places to include.
 */
void float_to_string(float value, char* buffer, int precision) {
    int idx = 0;

    // Handle negative sign.
    if (value < 0.0f) {
        buffer[idx++] = '-';
        value = -value; // Work with positive value.
    }

    // Extract integer part.
    int int_part = (int)value;
    float frac_part = value - (float)int_part;

    // Convert integer part to string.
    int int_digits = 0;
    int temp = int_part;
    // Count digits of the integer part. Handle zero case.
    if (temp == 0) {
        int_digits = 1;
    } else {
        do {
            int_digits++;
            temp /= 10;
        } while (temp > 0);
    }
    // Convert digits to characters (in reverse order).
    for (int i = int_digits - 1; i >= 0; i--) {
        buffer[idx + i] = '0' + (int_part % 10);
        int_part /= 10;
    }
    idx += int_digits;

    // Convert fractional part if precision > 0.
    if (precision > 0) {
        buffer[idx++] = '.'; // Add decimal point.
        for (int i = 0; i < precision; i++) {
            frac_part *= 10.0f; // Shift decimal.
            int digit = (int)frac_part; // Get the digit.
            buffer[idx++] = '0' + digit; // Convert to char.
            frac_part -= digit; // Remove the extracted digit.
        }
    }

    buffer[idx] = '\0'; // Null-terminate the string.
}

/**
 * @brief Converts a 16-bit 'half-precision' floating-point number to a 32-bit single-precision float.
 * @param h The 16-bit half-precision number.
 * @return The 32-bit float representation.
 * @note This function is a direct copy of `h_t_f` from `intmath.c`. It's replicated here,
 * likely for convenience or to avoid linking issues in a specific build environment
 * where `intmath.c` might not be fully linked for all external calls.
 */
float half_to_float(uint16_t h) {
    uint32_t sign = (h >> 15) & 0x1;
    int32_t exponent = (h >> 10) & 0x1F;
    uint16_t mantissa = h & 0x3FF;

    if (exponent == 0x1F) {
        if (mantissa == 0) {
            neorv32_uart0_puts(sign ? "-INF" : "INF");
            return sign ? -INFINITY : INFINITY;
        } else {
            neorv32_uart0_puts("NAN");
            return NAN;
        }
    }

    if (exponent == 0) {
        if (mantissa == 0) {
            return sign ? -0.0f : 0.0f;
        } else {
            exponent = 1;
            while ((mantissa & 0x400) == 0) {
                mantissa <<= 1;
                exponent--;
            }
            mantissa &= ~0x400;
        }
    }

    exponent = exponent + (127 - 15);

    uint32_t f_bits = (sign << 31) | (exponent << 23) | (mantissa << 13);

    union {
        uint32_t u;
        float f;
    } uconv;

    uconv.u = f_bits;
    return uconv.f;
}

/**
 * @brief Converts a 32-bit single-precision float to a 16-bit 'half-precision' floating-point number.
 * @param f The 32-bit float number.
 * @return The 16-bit half-precision representation.
 * @note Similar to `half_to_float`, this is a copy of `f_t_h` from `intmath.c`.
 */
uint16_t float_to_half(float f) {
    union {
        float f;
        uint32_t u;
    } uconv;

    uconv.f = f;

    uint32_t f_bits = uconv.u;

    uint16_t sign = (f_bits >> 16) & 0x8000;
    int32_t exponent = ((f_bits >> 23) & 0xFF) - 127 + 15;
    uint16_t mantissa = (f_bits >> 13) & 0x3FF;

    if (exponent <= 0) {
        return sign;
    } else if (exponent >= 31) {
        return sign | 0x7C00 | (mantissa ? 1 : 0);
    }

    return sign | (exponent << 10) | mantissa;
}

/**
 * @brief Structure to hold test case data for CFU operations.
 * Each test case includes two 32-bit combined interval inputs and an expected 32-bit result.
 */
typedef struct {
    uint32_t a;        // Combined interval A.
    uint32_t b;        // Combined interval B.
    uint32_t result;   // Expected combined interval result.
} TestCase;

// Test cases for various interval operations. These are combined 32-bit hex values
// representing 16-bit half-precision floating-point intervals.

TestCase test_cases[] = {
    {0xdaf0d8a3, 0xd94fd4c0, 0xde20db03},
    {0xda0f4cca, 0x570f5a0a, 0xd50f5aa3},
    {0xd92354ee, 0xc5255880, 0xd94c5af7},
    {0xd681594f, 0xd0a15535, 0xd8695bea},
    {0x55f65922, 0xd8abd539, 0xd2c0550b},
    {0x570f5824, 0x54ec5924, 0x59fe5ca4},
    {0xcc2fcb33, 0xd9a4d810, 0xda2ad883},
    {0xd8c459ea, 0x59065bee, 0x48205eec},
    {0x4a2b5493, 0xd86659eb, 0xd8035c1a},
    {0xd6a459c9, 0xdb9ada9b, 0xdd76ce90},
    {0xc15d587f, 0xda104cef, 0xda25591d},
    {0x551f58f9, 0xda035a52, 0xd6e75da6},
    {0xd9715b2d, 0xd644d634, 0xdc4a5813},
    {0xd995598e, 0xd67159e4, 0xdc675db9},
    {0xd22a598b, 0x5198594a, 0xc4905d6b},
    {0xd0fe57d8, 0xd928564c, 0xda685b12},
    {0xd80758ec, 0xd9a2d470, 0xdcd55568},
    {0xca17582c, 0x561857ce, 0x55555c0a},
    {0xd9285a05, 0xd8d4d5d3, 0xdcfe5637},
    {0xd16e529d, 0x587d5b51, 0x56435c7c},
    {0xdb3857cf, 0xc88f5497, 0xdb815a33},
    {0xd9415b7b, 0xcb1f5547, 0xd9b35d0f},
    {0xd5284908, 0xd7dbcd9f, 0xda82ca36},
    {0xdb53d848, 0xd8f7ce0e, 0xde25d90a},
    {0xd968d4bf, 0x4b1b5517, 0xd8f64580},
    {0xd8d05be2, 0x4cdc5b0f, 0xd8355f79},
    {0xdacc5afc, 0xd9e8566b, 0xde5a5d19},
    {0xd69c5a8e, 0xd881568d, 0xdbcf5cea},
    {0xd9f1d0fc, 0xd9bbd6f8, 0xddd6d8bb},
    {0xda1fd447, 0x5229546e, 0xd89540e0},
    {0x59865afd, 0xd96ed27a, 0x4200595f},
    {0xd333c8e1, 0xdb115ae4, 0xdc6f5a96},
    {0x4f0557fd, 0xc8c658d5, 0x4ca25c6a},
    {0xd1d34dba, 0xda08d607, 0xdb7dd499},
    {0xd2ad5711, 0xdaebda48, 0xdc4bd57f},
    {0xda185ba5, 0x4be558d3, 0xd99a5e3c},
    {0x533b54a6, 0xcd51ccec, 0x509352d6},
    {0xc7c758d6, 0xdada5a99, 0xdb185db8},
    {0xd73655bd, 0xd5cf51e4, 0xda835858},
    {0xda73581e, 0xd98451b6, 0xddfc598c},
    {0xdb9053da, 0xd968d234, 0xde7c4a98},
    {0x58cb59f2, 0xd2395a93, 0x567a5e43},
    {0xda58d30f, 0x508252e6, 0xd938bd20},
    {0xd8195b0b, 0xd16c5869, 0xd9745dba},
    {0xdb3159d5, 0xda9d4620, 0xdee75a06},
    {0xcf6e4fa5, 0x58cb590c, 0x57bb5a01},
    {0xdb7d5b63, 0xd6605b09, 0xdd575f36},
    {0xdabb5957, 0xd987d89d, 0xde214dd0},
    {0xd8ca4b5e, 0xd85ad08b, 0xdc92cd67},
    {0xd5efd574, 0xd84c5073, 0xdb44d275},
    {0xdb4c59ad, 0xd33b5bc6, 0xdc8d5eba},
    {0xd8d95560, 0xd8715a5b, 0xdca55c86},
    {0xd6e0523f, 0x55bd585c, 0xcc8c59ec},
    {0xdb965a37, 0xd30c564c, 0xdcad5caf},
    {0x59615ae9, 0xd6835b16, 0x543f5f00},
    {0x46425702, 0x517d5b96, 0x52455d8c},
    {0xd8ba50a7, 0xd90dc2bf, 0xdce4503b},
    {0xd0b84ca9, 0xd3d557ee, 0xd647588c},
    {0x40b358d1, 0xdb8b5824, 0xdb785c7b},
    {0x56115908, 0xd6c159a6, 0xc9805d57},
    {0xd7eec843, 0xd4985bcb, 0xda435b87},
    {0x4e6c56e9, 0xdb3655a1, 0xda695a45},
    {0xdb60d76c, 0xd6995b51, 0xdd565736},
    {0xccb159ee, 0xd82a4ff1, 0xd8c05aec},
    {0x59875acf, 0x542d5b56, 0x5b9e5f13},
    {0xd60b5864, 0xd1c6cd69, 0xd877576e},
    {0xdb975871, 0x51cb5811, 0xda245c41},
    {0x4fea5854, 0xd373568a, 0xcefc5b99},
    {0x55c458aa, 0x55ad5988, 0x59b95d19},
    {0xd90ed7f7, 0x542e5bb3, 0xd5ee576f},
    {0xda2a5232, 0xd624553b, 0xdc9e582a},
    {0xd9784fff, 0xd903d3b4, 0xdd3ecf69},
    {0xdaf3da6d, 0xda41cc6b, 0xde9adafa},
    {0xd9215bf1, 0x4eb85a3e, 0xd84a5f18},
    {0xcfe2cf73, 0xd58057c0, 0xd77955e3},
    {0xdbdc5924, 0xd891581c, 0xde375ca0},
    {0x550c59e7, 0x5509553c, 0x590b5c43},
    {0xdb2acf97, 0xdae2511b, 0xdf06493e},
    {0xda38d907, 0xd8705469, 0xdd54d5a5},
    {0xd97d5b9c, 0x559556a4, 0xd5655d77},
    {0x446e542f, 0xdae8d926, 0xdac5d61d},
    {0xd4ee5ad2, 0xd7da430d, 0xda645aee},
    {0xd7a259e7, 0x56f4596a, 0xc9705da9},
    {0xd4e858bb, 0x586e5bec, 0x53e85e54},
    {0xdafcda83, 0xd8fa593a, 0xddfbd124},
    {0xd1b35a77, 0x54745bd0, 0x4e6a5f24},
    {0xdb96c9f0, 0xdad9d8c5, 0xdf38d924},
    {0xdb20500a, 0x48d94c89, 0xdad3524f},
    {0xdaf3d945, 0xdabdd915, 0xded8dd2d},
    {0xdbf45be8, 0xd4124c3e, 0xdcff5c38},
    {0xd49958b0, 0x5a3c5a7d, 0x57df5d97},
    {0xd18f591c, 0x59de5bb1, 0x587a5e67},
    {0xd2235a94, 0xdbf4d714, 0xdcbe5614},
    {0xdac45b2e, 0xd7aec7b2, 0xdd4e5af1},
    {0x55005a8a, 0xda70d8f4, 0xd7e05258},
    {0x515e58ae, 0xc7a25642, 0x506a5bcf},
    {0xd4755ba6, 0x4e725898, 0xd1b15e1f},
    {0xd9775b9c, 0xd14f54c5, 0xdacb5cff},
    {0xda78587b, 0x56f3586f, 0xd5fd5c75},
    {0xd8544cec, 0x406458d5, 0xd8435973},
    {0xdae15ac9, 0xd7b45bdd, 0xdf5f5d52},
    {0xd69d595f, 0xda78503a, 0xd85d5dec},
    {0xd00854ea, 0xd956d8de, 0x57b85bcb},
    {0xdac353aa, 0xd830d3be, 0xd8d45a1b},
    {0xda6ad718, 0xdac04d05, 0xdb0b5668},
    {0xdb33d9d4, 0x54675b53, 0xdf43dc04},
    {0xdb3bd8a2, 0xd87d5b7b, 0xdf5bc4a0},
    {0x4bfb52b3, 0xd753d32a, 0x54945956},
    {0x473d51a0, 0xd85753cb, 0xd2e359bf},
    {0x534b597b, 0xdb26d436, 0x57dc5e51},
    {0x55685bc5, 0xdb295b00, 0xd84c5f77},
    {0xd942580b, 0xd6095227, 0xdacc5b10},
    {0xdb1d582e, 0xdb055714, 0xdd545d9a},
    {0xd88f5b11, 0x59995b86, 0xde0b51e0},
    {0x53315680, 0xd9c04621, 0x526d5c80},
    {0xd82e535d, 0xd892d473, 0xd3d25a69},
    {0xda76d9aa, 0xd00c4da6, 0xdb2bd8a7},
    {0x54a254e0, 0xdbb4d887, 0x5ad85d12},
    {0xd10a5a14, 0xcb2b5bf2, 0xdc9a5a87},
    {0xd17d5976, 0xda42507e, 0xd4fe5ddc},
    {0x52c1577d, 0x4d915bd7, 0xda275619},
    {0xd1315567, 0xd8f6d0ac, 0xc4285baa},
    {0xd0645664, 0xd4845b9c, 0xdc5b5974},
    {0x50ee57a5, 0xd9c5554c, 0xd1aa5ccc},
    {0xd42b5abd, 0xd805cfb4, 0xd07c5d61},
    {0x53e15a93, 0x59475b21, 0xd9295130},
    {0xdbf55836, 0x546b5995, 0xdec55401},
    {0xd18d5a73, 0xd80fd45b, 0x4e525d41},
    {0xdb885175, 0xd6d85521, 0xdd0c58c9},
    {0xdaedd2a8, 0x59535b6e, 0xdf2edafd},
    {0xd8315bc2, 0xd96b586f, 0xdc505e97},
    {0xc6355541, 0x55ea5743, 0xd7a6c948},
    {0xd5a8c43a, 0xdabf5856, 0xdb2a5a9d},
    {0xca7f5bf3, 0xd81ad528, 0x54585e07},
    {0xd9d0d04b, 0xda0bd9cb, 0xb90058f8},
    {0xdb54d94f, 0xdb68584b, 0xddd05432},
    {0xd5535aea, 0x56f85aa8, 0xdca956dc},
    {0xda4e5ab5, 0x52c85a41, 0xde485903},
    {0xd8b3d838, 0xd941d439, 0xd52d5024},
    {0xd691c4ea, 0x542b5b21, 0xdd35d47a},
    {0x52ca57e0, 0xd2564859, 0x51b45986},
    {0x566b5ab9, 0xd5984b81, 0x557b5cc3},
    {0xdb205bd7, 0xd8e4d4a8, 0xd8cc5e5e},
    {0x590b5b02, 0x525857f5, 0x5042596c},
    {0xd9d15851, 0xdbb1daaf, 0x4ef05e01},
    {0xd7ba5a0b, 0xdbc45306, 0xd99f5ee8},
    {0xd4d458d3, 0xd68d596e, 0xdbd85c0d},
    {0xd61ad318, 0xd2c154ee, 0xd984c170},
    {0xd0c85bf7, 0xd1d4c56f, 0xd01a5cb6},
    {0x58ba5afa, 0xd5f6c803, 0x58fa5cfb},
    {0xd55055b0, 0x54f15bd7, 0xdd4049f8},
    {0xdb2bcbe4, 0x4e5b58bf, 0xddf5d127},
    {0x56805874, 0xda14d304, 0x59015d44},
    {0xda7dce34, 0xd901b723, 0xda7a583b},
    {0xd719541d, 0xd5fe5bdb, 0xddb4590e},
    {0xd2ef5043, 0xdaadd24a, 0xc5285bbe},
    {0x572f5a94, 0xccac5329, 0x53355b2a},
    {0xcc855aa9, 0xd59a5bd0, 0xdc305cbb},
    {0xda4c4b08, 0xd95e59df, 0xde1659cf},
    {0xd0244f8a, 0x57c85af4, 0xdbfdd5e6},
    {0x4f144fdf, 0xdb4fda2b, 0x5b0e5c26},
    {0xdadb5a69, 0xd588d3ea, 0xd8e15c97},
    {0x5b085b1e, 0xd8edd795, 0x5d695e06},
    {0xd52a515a, 0xd8abcb64, 0xd43e5a02},
    {0x56f45a1e, 0xcde6549b, 0x50b25adb},
    {0xd6b1542f, 0x590c5a86, 0xdcefd5e9},
    {0xd1db5b7f, 0xd86dd04d, 0xca385df6},
    {0x54215a1f, 0xdb06cc8e, 0x55455e93},
    {0xd8f35872, 0xd9fa5907, 0xdcfd5d36},
    {0xd4e55be5, 0xc8bb3c99, 0xd4f75c18},
    {0xd8df5acd, 0x51035bb7, 0xde4b598c},
    {0x595a5be2, 0xd8075b1f, 0xd3145df5},
    {0xd9cdd8c1, 0xd12650cf, 0xdb01d6ef},
    {0xd99350c3, 0xd61e5a7e, 0xde095840},
    {0xd8b15b6b, 0x516c548e, 0xdaf85a10},
    {0x54875720, 0xcc1c549e, 0xbdc05814},
    {0xc94c4ec2, 0xda905b50, 0xdba55b68},
    {0x55d357b9, 0xd831d4ef, 0x59615c07},
    {0x5052584c, 0x5867594d, 0xd839c2c0},
    {0xdb8b4cce, 0xd5bf5b9a, 0xdf9356f3},
    {0xda235aa3, 0xd96d493f, 0xda775e08},
    {0xd97a5349, 0x55255aa2, 0xde0ece02},
    {0x572f5963, 0x52845b10, 0xd6f15784},
    {0xd4405595, 0xdace51f2, 0xd7395ccc},
    {0x55d15648, 0xdb494cfa, 0x54935d37},
    {0xd5425448, 0xd779d561, 0x3fc059e1},
    {0x58c25bb7, 0xdb77d89e, 0x5cb05f97},
    {0xd12858dc, 0xd8b35891, 0xd9db5cc8},
    {0xda1e58d2, 0x574c5ac5, 0xde7250b0},
    {0xd096cf7a, 0xda56d0b1, 0x3ac05967},
    {0xd8bc5931, 0x58d95b2b, 0xddf44980},
    {0xdba3da89, 0xd9005008, 0xdc53d224},
    {0xd41559c5, 0xc91c5ac7, 0xdc695a17},
    {0xd0b05957, 0xda2b5aec, 0xdc0c5dc1},
    {0x581a59d9, 0xd8815b1b, 0xd6025d2d},
    {0x5131590f, 0xdb1c549d, 0xd0095e16},
    {0xd9e2c59e, 0x59a65b3e, 0xde90d9d3},
    {0xb6b65ab8, 0x54015879, 0xd87c58b8},
    {0xd1a94030, 0xdae95983, 0xdaed5afa},
    {0xd8f84dbc, 0xd7c64adc, 0xd966589b},
    {0xd655d53f, 0xda8ad519, 0x6eb0752d},
    {0xd6afccc6, 0x5a8a5b66, 0xf62eebce},
    {0xda99581f, 0xd9d9d96d, 0xf60678d3},
    {0xcf495b8a, 0xd5bf5a4d, 0xf56a79f0},
    {0xda4c522d, 0xd8f65094, 0xefa977cf},
    {0xd8ead5d7, 0x58cf59a2, 0xf6ecf305},
    {0xdbc1d13c, 0x5ac45b16, 0xfadef06d},
    {0xd956516d, 0xd8a2d83e, 0xee49762e},
    {0xda8f595d, 0xdb90c586, 0xf9127a33},
    {0xd8de58b2, 0xd56ccc33, 0xf25d7299},
    {0xdb36d480, 0x4f7e544f, 0xf3c4e837},
    {0xd17f5788, 0xd2da577b, 0xee73730b},
    {0xdb174339, 0xd6f355b4, 0xf50e7629},
    {0xdb9d58d7, 0xd9344e38, 0xf64c78f4},
    {0xda545864, 0xd96057b3, 0xf6177840},
    {0xd60ed58f, 0xd6a256bc, 0xf1197105},
    {0xd64852ad, 0xd8b55687, 0xf1207364},
    {0xdb945747, 0x54075b83, 0xfb1e76d5},
    {0xd71551c2, 0xd70655a9, 0xf1037238},
    {0xd69c5638, 0xd63f5407, 0xf0db7129},
    {0xd9e455b0, 0x52e25aae, 0xf8eb74c0},
    {0xd902ce98, 0xdb84d9e2, 0x6cd978b4},
    {0xd24a56e1, 0xd71d5335, 0xf21e6e32},
    {0x431a54dd, 0xd9a257b0, 0xf2d970ac},
    {0xdb4754ba, 0xd859555e, 0xf4e277e9},
    {0xd5e15650, 0xd88655c1, 0xf32372a6},
    {0xd87a52ed, 0xdb75d8fe, 0xf275782c},
    {0xd1c4576a, 0xae6c58dc, 0xef017481},
    {0xdb5c5a16, 0xd8c057aa, 0xf73a785f},
    {0xd89c4e93, 0xd9505adc, 0xf7e8761f},
    {0xd5ed4ddf, 0xda52558e, 0xf01d74ae},
    {0xd49d5b47, 0xd33ccd9d, 0xf2956c2c},
    {0xd7ebd24d, 0x59045bb6, 0xf7a2efe7},
    {0x4cf45841, 0x4edd5b56, 0x604077cd},
    {0xdbb1cf92, 0x57965900, 0xf8cfeb2e},
    {0xd78759b9, 0xd973d4c4, 0xf7cc7521},
    {0xd8c2d6cb, 0xd7dad5f0, 0x710b74ab},
    {0xda814e99, 0x4fb9565c, 0xf52c693f},
    {0xd4fa5b17, 0x490659ad, 0xf3107908},
    {0xd7a55b41, 0xd65d4eee, 0xf5c57215},
    {0xcfac5a37, 0xd85d543a, 0xf6c77291},
    {0x55ee5b29, 0x5a3a5a64, 0x749d79b8},
    {0xdb585ad2, 0xda45ca2d, 0xf95879c1},
    {0xd4fc5b92, 0xd3cc5317, 0xf36172b6},
    {0xd8b15520, 0xd93b5b17, 0xf8287622},
    {0xda0f5bc6, 0xca415b3b, 0xf97a7b07},
    {0xd2035ba8, 0x531d579e, 0xedb9774a},
    {0xcf335b6b, 0xd8a55832, 0xf84e77c8},
    {0xd86b569d, 0xcf745966, 0xf5f67476},
    {0xd920d551, 0xdab15ad2, 0xf85f7849},
    {0xdab5d4b2, 0xdaeed966, 0x725679cf},
    {0xd5115b34, 0xd3f65180, 0xf32b70f4},
    {0xdb7f55ba, 0xdaf753cf, 0xf4fc7a87},
    {0xd7ed5b84, 0xdbd3dacc, 0xfb5a77c0},
    {0xd7024fec, 0xd9235779, 0xf28c7480},
    {0xd3175912, 0xda815951, 0xf81f76bd},
    {0x4ea6599c, 0xcf7f583e, 0xed4275f3},
    {0xd4a65517, 0xdbc1d924, 0xf4ef7481},
    {0xd035568c, 0xd1395303, 0xec466dbd},
    {0x55aa55cb, 0xda7358af, 0xf4ac72c8},
    {0xdb95d864, 0xd7cbccaf, 0x69247763},
    {0xd021460f, 0xda01d94e, 0xe48c6e33},
    {0xd9cc5bca, 0xdabf5628, 0xfa9178e3},
    {0xd07858a1, 0xd03c548e, 0xece67145},
    {0xd85758ee, 0x5a395ab2, 0xf7447820},
    {0xd6d45aa4, 0xd9ac58d1, 0xf8b577ff},
    {0xd4ba50ce, 0xdb615475, 0xf06f745c},
    {0xd4ff5783, 0xd95a596f, 0xf506751a},
    {0x45455852, 0xd7ac5a32, 0xf42576b1},
    {0xd66eca9f, 0x5805590f, 0xf411e6a7},
    {0xd53754a1, 0xdbdec6f1, 0xf48d7521},
    {0xd91e593c, 0xdae75a8e, 0xf884786a},
    {0x5acb5b15, 0xdb9a5be0, 0xfabb7af9},
    {0xda23d217, 0x50d95b58, 0xf9a2e761},
    {0x5877588f, 0xdb70d5c0, 0xf83df26b},
    {0x580258e5, 0xd94ed602, 0xf67ef205},
    {0xdae55917, 0xd66f587f, 0xf7c075b9},
    {0x501b5ae9, 0xdaaf5994, 0xf9c678d1},
    {0x5803589f, 0xd9d95ba3, 0xf6c17869},
    {0xd825588b, 0xdac3d827, 0xf7ae7702},
    {0xd65258c0, 0xd9605746, 0xf6627452},
    {0xc58958c4, 0x58895a55, 0xe462778b},
    {0xd94cd73e, 0xcd1c586a, 0xf5d86ac4},
    {0xd5875b8f, 0xc98c5a7e, 0xf47c7a22},
    {0x55de58e3, 0xd70f5691, 0xf4507403},
    {0xda1fd22c, 0xdb2f5976, 0xf82e797f},
    {0x43815881, 0x5ad35bc1, 0x6267785e},
    {0xcfac529e, 0x555658c9, 0xec976feb},
    {0xd6a55911, 0xd64259e4, 0xf4e47776},
    {0xda04576d, 0xd8bad3ca, 0xf463771c},
    {0xd10855ba, 0xdaf64f11, 0xf4fc7061},
    {0xd6735306, 0xd5cd55af, 0xf09570ad},
    {0xd8bc5a9a, 0xd2175a10, 0xf72d7901},
    {0xda77d199, 0xd2e15b12, 0xf9b7718f},
    {0xdac3da3f, 0x4fd05a41, 0xf949ee1a},
    {0xce414e31, 0xdb0f58e3, 0xed766d85},
    {0xdb52cddd, 0x580b597b, 0xf904e9ed},
    {0xdb954fde, 0xda15d968, 0xedfb79c4},
    {0xda6258bc, 0xd845d1d2, 0xf50e76d0},
    {0xd82d55e1, 0xd49a539d, 0xeff370ce},
    {0xd0c6cb5f, 0xdb21da0f, 0x2c23324d},
    {0xd329cde2, 0x58865894, 0xb655b124},
    {0xda5ad605, 0x4cb45b6e, 0xc967b67b},
    {0x585058c6, 0xda8ad454, 0xc069b946},
    {0x55df5b4c, 0x5a105a84, 0x37353cd0},
    {0x5a505bca, 0xd90ad69f, 0xc0b5bd03},
    {0x506c5b92, 0x4d4f57e7, 0x347949b4},
    {0xd878d2f4, 0x45a8570c, 0xce52b7e4},
    {0x54285769, 0xd4fccf9d, 0xc3c9baab},
    {0xdbcad3f8, 0xdb04da49, 0x348b3cf5},
    {0xdb4ed699, 0x5151564d, 0xc57fbc30},
    {0xd8f1d773, 0xd851d83c, 0x3ae73cab},
    {0xda83da64, 0xd96ad7fe, 0x3cb93e84},
    {0x4d0f591a, 0xd596d397, 0xc160b33e},
    {0xd79ed2b5, 0xd8bcd606, 0x35ab3d0f},
    {0x50a5540d, 0x5275586e, 0x34323d04},
    {0x58ae5a49, 0x541e58c6, 0x3bd7421b},
    {0x598f5a5c, 0x517f5b35, 0x3a2b44a1},
    {0xda65da30, 0x53cd56e7, 0xc28ebf2b},
    {0xd5fad5bb, 0x5ad75b20, 0xb6fdb66f},
    {0x5a7a5ad8, 0x562c5945, 0x3ceb406f},
    {0x54d05879, 0x4a664b95, 0x45134997},
    {0x54a3571e, 0x599f5a11, 0x361d3911},
    {0xdb03d88b, 0x585a5978, 0xbe72baa5},
    {0xdbe3d7e1, 0x47664827, 0xd044cb97},
    {0xdb96cd08, 0x56535a65, 0xc0ccae4b},
    {0x49cd58c5, 0xda03d622, 0xbe38abb8},
    {0x57675aac, 0xd4ded034, 0xc659be15},
    {0xda5dd94b, 0xdbb8dab8, 0x397c3b93},
    {0xd9d9d69c, 0x4a315856, 0xcb8eba19},
    {0x4c9a5438, 0xd8cdd839, 0xb7feafab},
    {0xda8fd659, 0x561f56c9, 0xc049bb7b},
    {0x561256b0, 0xd341d2a5, 0xc007beb1},
    {0xd905d5e6, 0x54055a36, 0xc0ffb798},
    {0xd889d287, 0xd9eed379, 0x346740da},
    {0x57be59a9, 0x546b5acc, 0x388e4120},
    {0xda32d516, 0xdbe2da82, 0x35293b9d},
    {0x52f6552b, 0xd487cdb3, 0xc341ba26},
    {0xd3fccfe5, 0x5a345a90, 0xb526b0d0},
    {0xd60dd124, 0xd898d0a2, 0x347a4139},
    {0xdb55d43d, 0xdbaed77a, 0x346a3fd8},
    {0x49604df1, 0x52de59cc, 0x2b6a36eb},
    {0x59215aaa, 0xd92cd665, 0xc02bbbee},
    {0x4d3959e1, 0x54db5651, 0x329d40d8},
    {0x4fbe551f, 0x4a4d529d, 0x38af4680},
    {0x59eb5a41, 0x504f54cf, 0x40ec45ce},
    {0xd871d29b, 0xda20d870, 0x34503c01},
    {0x54305808, 0xdaa0d9d1, 0xb98bb50e},
    {0x583e5958, 0xdbcbd851, 0xbcf4b85a},
    {0x44f259f5, 0x5b075b4f, 0x25693ac8},
    {0xd40bd34d, 0x57805b7a, 0xb850b3cf},
    {0x50575bb4, 0x3cf74f19, 0x3ce45a35},
    {0xda41d5bd, 0x54675b46, 0xc1afb64f},
    {0xda3fcc81, 0xdad8c4c1, 0x2d435141},
    {0x5a395b87, 0x4d265850, 0x3dc649d9},
    {0xd81ac692, 0xdbd5db40, 0x26b63886},
    {0xdaa7d553, 0xd376d063, 0x3db54611},
    {0xd5e8d564, 0x518b5998, 0xc043b7b5},
    {0xd991d034, 0x5804594b, 0xbd8bb25a},
    {0x53805733, 0x5641582e, 0x372d3c9b},
    {0x4dda4e50, 0x585a5bc9, 0x2e0331cd},
    {0x5b8d5b97, 0x5119563c, 0x40d845f5},
    {0xdadad394, 0xdad2d4a8, 0x347241e3},
    {0xda2ed89b, 0xd9cec562, 0x3a585098},
    {0x4085575b, 0xd8e8d88c, 0xba79a35e},
    {0x55375a2f, 0x54815900, 0x382c417e},
    {0xd985ccbb, 0xda6bd994, 0x2de53bea},
    {0x56ab57aa, 0xd795d60f, 0xbd0fbb09},
    {0x58305906, 0x54435afb, 0x38cc40b7},
    {0x531f55d7, 0x55fb5716, 0x38053bcf},
    {0x547557b9, 0x564f5a16, 0x35db3ce6},
    {0xda70d8c4, 0x551e588b, 0xc108bc32},
    {0xdb93cb56, 0xd76fd48e, 0x2fe542a7},
    {0x4d0c505f, 0x52bc5a8f, 0x2e273931},
    {0x58275a48, 0xdb7dd754, 0xbedbb86f},
    {0x50935bca, 0x55b1588d, 0x34054179},
    {0xd9ead956, 0xdb5ed4a7, 0x39cb4116},
    {0x4f37594b, 0xd9f2d45c, 0xc0dbb0db},
    {0x50c85b48, 0xd750d617, 0xc0c8b53b},
    {0x561058cf, 0x41415692, 0x3b615352},
    {0x550658b3, 0xdbdecc72, 0xc83ab51b},
    {0x57845a09, 0xdab8ccb7, 0xc91fb879},
    {0x51185ac3, 0x58d45a4e, 0x32763d9a},
    {0x45b358a3, 0xdb46cd54, 0xc6f6a644},
    {0xdbc2d8aa, 0xd7dfd67d, 0x3cbd40c8},
    {0x56625afb, 0xd3cad2d0, 0xc419be8e},
    {0xd3dbd23b, 0x523b564b, 0xbd0bb7eb},
    {0x54cf574b, 0x59345a0c, 0x365c399b},
    {0xd91bc1da, 0xda56d0bf, 0x2363444e},
    {0x458b5b18, 0xd7cdd6e2, 0xc01fa9af},
    {0xda13d91c, 0x59e95b19, 0xbc1cb9c2},
    {0x4de659b8, 0x4852594b, 0x30754d4b},
    {0x58625b47, 0xdac3d9a4, 0xbd29b92f},
    {0xdaa1d4b4, 0x595059dc, 0xbcfeb66b},
    {0x57125855, 0x57db58db, 0x39d33c69},
    {0xdaefda0c, 0x4908520c, 0xcd83c400},
    {0xd9efd3e2, 0xda5bd8e1, 0x34f63cdd},
    {0xdb71d96e, 0xdb50da2e, 0x39f03cd1},
    {0x444c59a4, 0xd94cce5e, 0xc716a67d},
    {0x50385b80, 0x58625985, 0x321d3ed8}
};


/**
 * @brief Evaluates a polynomial function `f(x)` for an interval input `x`.
 *
 * Implements the polynomial evaluation using Horner's method for interval arithmetic.
 * `f(x) = c_0 * x^degree + c_1 * x^(degree-1) + ... + c_degree`
 * where `c_0` is `coeffs[0]`, `c_1` is `coeffs[1]`, etc.
 * The coefficients `coeffs` are global.
 *
 * @param x The input interval for which to evaluate the polynomial.
 * @return The interval result of `f(x)`.
 */
interval_t f(interval_t x) {
    // Initialize result with the highest degree coefficient (coeffs[0]).
    // For Horner's method, the first step is typically the coefficient of the highest power.
    // If polynomial is a_n x^n + ... + a_1 x + a_0
    // Horner's: ((... (a_n * x + a_{n-1}) * x + a_{n-2}) * x ... ) + a_0
    // The `coeffs` array seems to be ordered from highest degree to lowest, so coeffs[0] is a_n.
    interval_t result = interval_const(coeffs[0]);

    // Iterate through the remaining coefficients.
    for (int i = 1; i <= degree; i++) {
        // Apply Horner's method: result = (result * x) + coeffs[i]
        // This leverages the CFU's interval multiplication and addition.
        result = interval_add(interval_mul(result, x), interval_const(coeffs[i]));
    }
    return result;
}

/**
 * @brief Prompts the user to define a polynomial (degree and coefficients).
 *
 * This function interacts with the user via UART to get the degree of the polynomial
 * and then its coefficients. It uses `neorv32_uart0_scan` for input and `atoi`/`atof`
 * for string to number conversions. The coefficients are stored in the global `coeffs` array.
 *
 * @return A dummy `interval_t` (interval_const(0.0f)) as this function's primary purpose
 * is to set global polynomial parameters, not return a computed interval.
 */
interval_t horner() {
    char buf[32]; // Buffer for user input.

    neorv32_uart0_printf("\nEnter polynomial degree: ");
    neorv32_uart0_scan(buf, sizeof(buf), 1); // Read degree from UART.
    degree = atoi(buf); // Convert string to integer and set global degree.

    neorv32_uart0_printf("\nEnter coefficients from highest degree to lowest:\n");

    // Loop to get each coefficient.
    for (int i = 0; i <= degree; i++) {
        neorv32_uart0_printf("\na_%d: ", degree - i); // Prompt for coefficient (a_n, a_{n-1}, ..., a_0).
        neorv32_uart0_scan(buf, sizeof(buf), 1);      // Read coefficient from UART.
        coeffs[i] = atof(buf); // Convert string to float and store.
    }

    return interval_const(0.0f); // Dummy return value.
}

/**
 * @brief Checks if an interval `a` intersects zero.
 * @param a The interval to check.
 * @return `true` (1) if the interval `a` contains or touches zero, `false` (0) otherwise.
 * @note Uses the `durint_interval` CFU instruction for more robust intersection check
 * compared to simple `a.lower <= 0.0f && a.upper >= 0.0f`.
 * `interval(-1e-5f, 1e-5f)` creates a small interval around zero for comparison.
 */
int intersects_zero(interval_t a) {
    // Check if the small interval [-1e-5, 1e-5] is 'during' interval 'a'.
    // This is a robust way to check if 'a' contains zero or a very small neighborhood around it.
    return (durint_interval(interval(-1e-5f, 1e-5f), a) & 1);
}

/**
 * @brief Checks if there's a sign change between the values of `f(a_lower)` and `f(a_upper)`
 * by examining if the interval `[f(a_lower), f(a_upper)]` spans zero.
 * @param a The first interval (representing f(a_lower)).
 * @param b The second interval (representing f(a_upper)).
 * @return `true` (1) if there's a potential sign change (zero intersection), `false` (0) otherwise.
 * @note This function seems to be designed to check if the interval *between* the function
 * values at two points (a and b) contains zero, implying a root might exist.
 */
int intersects_sign_change(interval_t a, interval_t b) {
    // Check if the interval formed by [min(a_upper, b_lower), max(a_lower, b_upper)] intersects zero.
    // This looks for an overlap of the two intervals that might span zero.
    // It's a more conservative check for a sign change in interval arithmetic.
    return intersects_zero(interval(a.upper, b.lower)) ||
           intersects_zero(interval(a.lower, b.upper));
}

/**
 * @brief Implements the Bisection Method for finding roots of a polynomial `f(x)` within an interval.
 *
 * This interval version of the bisection method iteratively narrows down an interval `a`
 * where `f(a)` is known to contain zero (or a sign change has occurred). It uses interval
 * arithmetic (via CFU) for robust calculations.
 *
 * @param a The initial search interval [a.lower, a.upper].
 * @param tol The tolerance (desired width of the final interval).
 * @param max_iter Maximum number of iterations.
 * @param f A function pointer to the polynomial evaluation function (e.g., `f(interval_t x)`).
 * @return The narrowed interval containing the root, or NaN interval if no root is found/sign change.
 */
interval_t bisection(interval_t a, float tol, int max_iter, interval_t (*f)(interval_t)) {
    int iter = 0;
    char stl[32], stu[32], rtl[32], rtu[32], mt[32]; // Buffers for string conversion.

    // Initial check: If f(a) does not contain zero, a root is unlikely in this interval.
    if (!intersects_zero(f(a))) {
        float_to_string(a.lower, stl, 8);
        float_to_string(a.upper, stu, 8);
        neorv32_uart0_printf("\nNo sign change at the start. (%s, %s)\n", stl, stu);
        return interval(NAN, NAN); // Return NaN interval.
    }

    // Main bisection loop: Continue as long as width > tolerance AND iterations < max_iter.
    // Uses `bfrint_interval` (before relation) to check `tolerance < width` and `iter < max_iter`.
    while ((bfrint_interval(interval_const(tol), interval_const(wdtint_interval(a)))) &&
           bfrint_interval(interval_const((float)iter), interval_const((float)max_iter))) {

        // Calculate f(midpoint(a)).
        interval_t fc = f(interval_const(midint_interval(a)));
        interval_t fca = f(a); // Evaluate f(a) for logging.

        // Print current iteration details.
        float_to_string(a.lower, stl, 8);
        float_to_string(a.upper, stu, 8);
        float_to_string(fca.lower, rtl, 8);
        float_to_string(fca.upper, rtu, 8);
        float_to_string(midint_interval(a), mt, 8);
        neorv32_uart0_printf("Iteration %d: [%s, %s], f(c)=[%s, %s] Mid = %s\n",
             iter, stl, stu, rtl, rtu, mt);

        // If f(midpoint) contains zero, we've found a root (within the interval).
        if (intersects_zero(fc)) {
            float_to_string(midint_interval(a), stl, 8);
            neorv32_uart0_printf("Root found: c = %s\n", stl);
            return interval_const(midint_interval(a)); // Return the midpoint as a point interval.
        }

        // Determine which sub-interval contains the root.
        interval_t f_low = f(interval_const(a.lower)); // Evaluate f at lower bound.

        // Check for sign change between f(a.lower) and f(midpoint).
        if (intersects_sign_change(f_low, fc)) {
            // Narrow the interval to [a.lower, midpoint(a)].
            // Check for non-narrowing case to prevent infinite loops for very small intervals.
            if (a.lower == midint_interval(a) || a.upper == midint_interval(a)) {
                neorv32_uart0_printf("Interval cannot be narrowed further\n");
                break;
            }
            a = interval(a.lower, midint_interval(a));
        } else {
            // If no sign change with f(a.lower), then it must be in [midpoint(a), a.upper].
            // Check for non-narrowing.
            if (a.lower == midint_interval(a) || a.upper == midint_interval(a)) {
                neorv32_uart0_printf("Interval cannot be narrowed further\n");
                break;
            }
            a = interval(midint_interval(a), a.upper);
        }

        // Re-assign 'a' with the narrowed interval (redundant if assignments above are direct).
        a = interval(a.lower, a.upper);
        iter++;
    }

    // After loop, report the final interval and its function value.
    interval_t result = a;
    interval_t fc_result = f(result);
    float_to_string(result.lower, stl, 8);
    float_to_string(result.upper, stu, 8);
    float_to_string(fc_result.lower, rtl, 8);
    float_to_string(fc_result.upper, rtu, 8);
    neorv32_uart0_printf("Total iterations: %d\n", iter);
    neorv32_uart0_printf("Resulting root: [%s, %s], f(root) = [%s, %s]\n", stl, stu,
         rtl, rtu);
    return result;
}

/**
 * @brief Scans a broader range to find an initial interval that might contain a root.
 *
 * This function iterates through sub-intervals within a `full_range` with a given `step` size.
 * For each sub-interval, it evaluates `f(x)` and checks if it intersects zero, indicating a root.
 *
 * @param full_range The total range to scan.
 * @param step The size of each sub-interval.
 * @param foundedint Pointer to an `interval_t` where the found root interval will be stored.
 * @return 1 if a root-containing interval is found, 0 otherwise.
 */
int find_root_interval(interval_t full_range, double step, interval_t* foundedint) {
    // Initialize current interval with the lower bound of full_range.
    interval_t lt = interval_const(full_range.lower);
    // Expand it by the `step` to form the first interval [lower, lower+step].
    lt = interval_add(lt, interval(0.0f, step));

    char stl[32], stu[32], rtl[32], rtu[32]; // Buffers for string conversion.

    // Loop while the current interval's upper bound is within the full_range's upper bound.
    // Uses `bfrint_interval` (before) and `durint_interval` (during) to check if `lt.upper` is
    // still less than or equal to `full_range.upper`.
    while (bfrint_interval(interval_const(lt.upper), interval_const(full_range.upper)) ||
           durint_interval(interval_const(lt.upper), interval_const(full_range.upper))) {

        interval_t flt = f(lt); // Evaluate polynomial for the current sub-interval.
        if (intersects_zero(flt)) { // Check if f(lt) intersects zero.
            *foundedint = lt; // If it does, store this interval as the candidate root interval.

            float_to_string(lt.lower, stl, 8);
            float_to_string(lt.upper, stu, 8);
            float_to_string(flt.lower, rtl, 8);
            float_to_string(flt.upper, rtu, 8);

            neorv32_uart0_printf("\nRoot interval found: [%s, %s]\n", stl, stu);
            neorv32_uart0_printf("\nf(lt.l, lt.u) = [%s, %s]\n", rtl, rtu);

            return 1; // Success: a root interval was found.
        }
        // Move to the next interval: Set new lower bound to current upper bound, then expand by step.
        lt = interval(lt.upper, lt.upper); // Make it a point interval.
        lt = interval_add(lt, interval(0.0f, step)); // Add the step.
    }

    return 0; // No root interval found in the specified full_range.
}

/**
 * @brief Main function of the NEORV32 CFU demo program.
 *
 * This function initializes the NEORV32 system, checks for CFU and counter
 * availability, and then enters a main menu loop. The user can select to
 * run automated test cases, perform manual interval operations, query interval
 * properties, check temporal logic relationships, or find roots of a polynomial
 * using the bisection method.
 *
 * @return 0 if the program completes successfully, -1 if essential hardware
 * (UART0, CFU, or counters) is not available.
 */
int main() {

  // Initialize NEORV32 run-time environment (including caches, memories, etc.).
  neorv32_rte_setup();

  // Check if UART0 (Universal Asynchronous Receiver-Transmitter) is implemented.
  if (neorv32_uart0_available() == 0) {
    // UART0 is required for user interaction and output.
    return -1; // Exit if not available.
  }

  // Setup UART0: Set baud rate and disable interrupts.
  neorv32_uart0_setup(BAUD_RATE, 0);

  // Check if the Custom Function Unit (CFU) is implemented.
  // The CFU is part of the 'Zxcfu' ISA extension in NEORV32.
  if (neorv32_cpu_cfu_available() == 0) {
    neorv32_uart0_printf("ERROR! CFU ('Zxcfu' ISA extensions) not implemented!\n");
    return -1;
  }

  // Check if the CPU base counters are implemented.
  // These are part of the 'Zicntr' ISA extension and are used for timing operations.
  if ((neorv32_cpu_csr_read(CSR_MXISA) & (1 << CSR_MXISA_ZICNTR)) == 0) {
    neorv32_uart0_printf("ERROR! Base counters ('Zicntr' ISA extensions) not implemented!\n");
    return -1;
  }

  // Introduction message.
  neorv32_uart0_printf("\n<<< NEORV32 Custom Functions Unit (CFU) - Custom Instructions Example >>>\n\n");
  neorv32_uart0_printf("[NOTE] This program relies on the CFU hardware in 'rtl/core/neorv32_cpu_cp_cfu.vhd'\n"
                       "       that implements the Arithmetic Logic Unit for Interval Algebra (IALU).\n\n\n");

  // Buffers for storing user input (float strings) for interval bounds and results.
  char bufferal[16];   // Buffer for interval A lower bound.
  char bufferau[16];   // Buffer for interval A upper bound.
  char bufferbl[16];   // Buffer for interval B lower bound.
  char bufferbu[16];   // Buffer for interval B upper bound.
  char buffercl[32];   // Buffer for result interval lower bound (string conversion).
  char buffercu[32];   // Buffer for result interval upper bound (string conversion).
  
  // Main menu loop: Program runs indefinitely until explicitly exited.
  while(1) {
    // Display main menu options.
    neorv32_uart0_printf("\n\n===== Interval Calculator Menu =====\n");
    neorv32_uart0_printf("1. Run test cases\n");
    neorv32_uart0_printf("2. Calculate manual interval operation\n");
    neorv32_uart0_printf("3. Interval properties\n");
    neorv32_uart0_printf("4. Temporal logic (Boolean result)\n");
    neorv32_uart0_printf("5. Temporal logic (State of two input)\n");
    neorv32_uart0_printf("6. Root finding with Bisection Algorithm\n");
    neorv32_uart0_printf("7. Exit\n");
    neorv32_uart0_printf("Enter your choice (1-7): "); // Corrected prompt to include '7'

    char choice[2]; // Buffer for user's menu choice.
    neorv32_uart0_scan(choice, sizeof(choice), 1); // Read user's choice.
    
    // --- Option 1: Run Test Cases ---
    if (choice[0] == '1') {
        neorv32_uart0_printf("\nRunning all %d test cases...\n", sizeof(test_cases)/sizeof(TestCase));
        
        int correct_count = 0;
        int incorrect_count = 0;
        
        uint32_t time_enc_hw; // Variable to store execution time (CPU cycles).
        neorv32_cpu_csr_write(CSR_MCYCLE, 0); // Reset machine cycle counter for timing.

        // Iterate through all defined test cases.
        for (int i = 0; i < sizeof(test_cases)/sizeof(TestCase); i++) {
            uint32_t a_combined = test_cases[i].a;
            uint32_t b_combined = test_cases[i].b;
            uint32_t expected_result_combined = test_cases[i].result;
            uint32_t actual_result_combined = 0;

            // Perform the operation using the CFU based on test case index (simplistic distribution).
            // This is a fixed logic for a small test_cases array (e.g., if there are 2 test cases,
            // the first 100 will use addint, next 100 subint, etc., but given only 2, this will always be addint for these specific cases).
            if(i<100){
                actual_result_combined = addint(a_combined, b_combined);
            }else if(i<200){
                actual_result_combined = subint(a_combined, b_combined);
            }else if(i<300){
                actual_result_combined = mulint(a_combined, b_combined);
            }else{
                actual_result_combined = divint(a_combined, b_combined);
            }
            
            // Compare actual result with expected result.
            bool match = (actual_result_combined == expected_result_combined);
            
            if (match) {
                correct_count++;
            } else {
                incorrect_count++;
            }
            
            // Print only incorrect results or every 40th result for progress.
            if (i % 40 == 0 || !match) {
                if (!match) { // Only print full details for mismatches.
                    neorv32_uart0_printf("Test %d: 0x%x + 0x%x = 0x%x (INCORRECT! Expected: 0x%x)\n",
                                 i, a_combined, b_combined, actual_result_combined, expected_result_combined);
                }
            }
            
            // Allow user to stop the test with 'q'.
            if (neorv32_uart0_char_received()) {
                char c = neorv32_uart0_getc();
                if (c == 'q' || c == 'Q') {
                    neorv32_uart0_printf("\nTest stopped by user after %d cases.\n", i+1);
                    break;
                }
            }
        }
        
        time_enc_hw = neorv32_cpu_csr_read(CSR_MCYCLE); // Read elapsed cycles since CSR_MCYCLE was reset.
        // neorv32_uart0_printf("ENC HW = %u cycles\n", time_enc_hw); // Debug print for cycle count.

        // Print test summary.
        neorv32_uart0_printf("\nTest Summary:\n");
        neorv32_uart0_printf("Total cases: %d\n", sizeof(test_cases)/sizeof(TestCase));
        neorv32_uart0_printf("Correct: %d\n", correct_count);
        neorv32_uart0_printf("Incorrect: %d\n", incorrect_count);
    }
    // --- Option 2: Calculate Manual Interval Operation ---
    else if (choice[0] == '2') {
        while (1) { // Loop for manual calculations until 'q' is pressed.
            neorv32_uart0_printf("\nHW MANUAL TEST (press 'q' to return to menu)\n");
        
            // Get input for first interval's lower bound.
            neorv32_uart0_puts("Enter lower bound of the first interval: ");
            neorv32_uart0_scan(bufferal, sizeof(bufferal), 1);
            if (bufferal[0] == 'q' && bufferal[1] == '\0') break; // Exit if 'q'.
        
            // Get input for first interval's upper bound.
            neorv32_uart0_puts("\nEnter upper bound of the first interval: ");
            neorv32_uart0_scan(bufferau, sizeof(bufferau), 1);
            if (bufferau[0] == 'q' && bufferau[1] == '\0') break;
        
            // Get desired operation.
            char input_char[2];
            neorv32_uart0_puts("\nSelect an operation (+, -, *, /): ");
            neorv32_uart0_scan(input_char, sizeof(input_char), 1);
            if (input_char[0] == 'q') break;
        
            // Get input for second interval's lower bound.
            neorv32_uart0_puts("\nEnter lower bound of the second interval: ");
            neorv32_uart0_scan(bufferbl, sizeof(bufferbl), 1);
            if (bufferbl[0] == 'q' && bufferbl[1] == '\0') break;
        
            // Get input for second interval's upper bound.
            neorv32_uart0_puts("\nEnter upper bound of the second interval: ");
            neorv32_uart0_scan(bufferbu, sizeof(bufferbu), 1);
            if (bufferbu[0] == 'q' && bufferbu[1] == '\0') break;
        
            neorv32_uart0_printf("\nProcessing...\n");
        
            // Convert string inputs to float values.
            float valueal = atof(bufferal);
            float valueau = atof(bufferau);
            float valuebl = atof(bufferbl);
            float valuebu = atof(bufferbu);
        
            // Create interval_t structures.
            interval_t a_input = interval(valueal, valueau);
            interval_t b_input = interval(valuebl, valuebu);
        
            interval_t result_interval;
            uint32_t time_enc_hw_op; // Variable for operation timing.

            // Perform selected interval operation using CFU-backed functions.
            if (input_char[0] == '+') {
                neorv32_cpu_csr_write(CSR_MCYCLE, 0); // Start timer.
                result_interval = interval_add(a_input, b_input);
                time_enc_hw_op = neorv32_cpu_csr_read(CSR_MCYCLE); // Stop timer.
            } else if (input_char[0] == '-') {
                neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                result_interval = interval_sub(a_input, b_input);
                time_enc_hw_op = neorv32_cpu_csr_read(CSR_MCYCLE);
            } else if (input_char[0] == '*') {
                neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                result_interval = interval_mul(a_input, b_input);
                time_enc_hw_op = neorv32_cpu_csr_read(CSR_MCYCLE);
            } else if (input_char[0] == '/') {
                neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                result_interval = interval_div(a_input, b_input);
                time_enc_hw_op = neorv32_cpu_csr_read(CSR_MCYCLE);
            } else {
                neorv32_uart0_printf("\nInvalid operation. Defaulting to addition.\n");
                neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                result_interval = interval_add(a_input, b_input);
                time_enc_hw_op = neorv32_cpu_csr_read(CSR_MCYCLE);
            }
        
            // neorv32_uart0_printf("Time HW = %u cycles\n", time_enc_hw_op); // Debug: print cycles.
            // neorv32_uart0_printf("\nError CSR: 0x%x\n\n", neorv32_cpu_csr_read(CSR_CFUREG0)); // Debug: print CFU error register.
        
            // Convert result interval bounds to strings for display.
            float_to_string(result_interval.lower, buffercl, 10);
            float_to_string(result_interval.upper, buffercu, 10);
        
            neorv32_uart0_printf("\nResult interval from calculation [%s, %s]\n",buffercl, buffercu);
            break; // Exit manual test loop.
        }
    }
    // --- Option 3: Interval Properties ---
    else if (choice[0] == '3') {
        while (1) {
            neorv32_uart0_printf("\nHW MANUAL TEST (press 'q' to return to menu)\n");
        
            // Get input for interval lower bound.
            neorv32_uart0_puts("Enter lower bound of the interval: ");
            neorv32_uart0_scan(bufferal, sizeof(bufferal), 1);
            if (bufferal[0] == 'q' && bufferal[1] == '\0') break;
        
            // Get input for interval upper bound.
            neorv32_uart0_puts("\nEnter upper bound of the interval: ");
            neorv32_uart0_scan(bufferau, sizeof(bufferau), 1);
            if (bufferau[0] == 'q' && bufferau[1] == '\0') break;
        
            // Get desired property operation.
            char input_char[2];
            neorv32_uart0_puts("\nSelect an operation (mid = a, width = b, radius = c, min = d, max = e): ");
            neorv32_uart0_scan(input_char, sizeof(input_char), 1);
            if (input_char[0] == 'q') break;
        
            neorv32_uart0_printf("\nProcessing...\n");
        
            // Convert user input to float and create interval.
            float valueal = atof(bufferal);
            float valueau = atof(bufferau);
            interval_t a_prop = interval(valueal, valueau);
        
            // Combine interval for CFU input.
            uint32_t combined_a_prop = combine(a_prop);
            uint32_t cfu_result_raw = 0; // Raw 32-bit result from CFU.
            uint32_t time_enc_hw_prop;

            // Perform selected property operation using CFU-backed functions.
            switch (input_char[0]) {
                case 'a': // Midpoint
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_raw = midint(combined_a_prop);
                    time_enc_hw_prop = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case 'b': // Width
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_raw = wdtint(combined_a_prop);
                    time_enc_hw_prop = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case 'c': // Radius
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_raw = radint(combined_a_prop);
                    time_enc_hw_prop = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case 'd': // Minimum (Lower Bound)
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_raw = minint(combined_a_prop);
                    time_enc_hw_prop = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case 'e': // Maximum (Upper Bound)
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_raw = maxint(combined_a_prop);
                    time_enc_hw_prop = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                default:
                    neorv32_uart0_printf("\nInvalid operation. Defaulting to midpoint.\n");
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_raw = midint(combined_a_prop);
                    time_enc_hw_prop = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
            }
        
            // neorv32_uart0_printf("Time HW = %u cycles\n", time_enc_hw_prop); // Debug: print cycles.
        
            // The CFU property functions return a 16-bit half-precision float in the lower 16 bits.
            uint16_t result_half_precision = cfu_result_raw & 0xFFFF;
            neorv32_uart0_printf("\nCombined 32-bit raw CFU value: 0x%x\n", cfu_result_raw);
        
            // Convert the 16-bit result back to a 32-bit float for display.
            float float_result_prop = half_to_float(result_half_precision);
            float_to_string(float_result_prop, buffercu, 10); // Use buffercu for single float result.
        
            neorv32_uart0_printf("\nResult from calculation: %s\n", buffercu);
            break;
        }
    }
    // --- Option 4: Temporal Logic (Boolean Result) ---
    else if (choice[0] == '4') {
        while (1) {
            neorv32_uart0_printf("\nHW MANUAL TEST (press 'q' to return to menu)\n");
        
            neorv32_uart0_puts("Enter lower bound of the first interval: ");
            neorv32_uart0_scan(bufferal, sizeof(bufferal), 1);
            if (bufferal[0] == 'q' && bufferal[1] == '\0') break;
        
            neorv32_uart0_puts("\nEnter upper bound of the first interval: ");
            neorv32_uart0_scan(bufferau, sizeof(bufferau), 1);
            if (bufferau[0] == 'q' && bufferau[1] == '\0') break;
        
            // Get desired temporal logic operation.
            char input_char[2];
            neorv32_uart0_puts("\nSelect an operation (i bfr j = 1, i mts j = 2, i ovr j = 3, i dur j = 4, i str j = 5, i fin j = 6, i eql j = 7): ");
            neorv32_uart0_scan(input_char, sizeof(input_char), 1);
            if (input_char[0] == 'q') break;
        
            neorv32_uart0_puts("\nEnter lower bound of the second interval: ");
            neorv32_uart0_scan(bufferbl, sizeof(bufferbl), 1);
            if (bufferbl[0] == 'q' && bufferbl[1] == '\0') break;
        
            neorv32_uart0_puts("\nEnter upper bound of the second interval: ");
            neorv32_uart0_scan(bufferbu, sizeof(bufferbu), 1);
            if (bufferbu[0] == 'q' && bufferbu[1] == '\0') break;
        
            neorv32_uart0_printf("\nProcessing...\n");
        
            // Convert inputs and create intervals.
            float valueal = atof(bufferal);
            float valueau = atof(bufferau);
            float valuebl = atof(bufferbl);
            float valuebu = atof(bufferbu);
        
            interval_t a_temp = interval(valueal, valueau);
            interval_t b_temp = interval(valuebl, valuebu);
        
            // Combine intervals for CFU input.
            uint32_t combined_a_temp = combine(a_temp);
            uint32_t combined_b_temp = combine(b_temp);
        
            uint32_t cfu_result_temp = 0; // Raw 32-bit result from CFU.
            uint32_t time_enc_hw_temp;

            // Perform selected temporal logic operation.
            switch (input_char[0]) {
                case '1': // Before
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = bfrint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case '2': // Meets
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = mtsint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case '3': // Overlaps
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = ovrint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case '4': // During
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = durint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case '5': // Starts
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = strint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case '6': // Finishes
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = finint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                case '7': // Equals
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = eqlint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
                default:
                    neorv32_uart0_printf("\nInvalid operation. Defaulting to 'equals'.\n");
                    neorv32_cpu_csr_write(CSR_MCYCLE, 0);
                    cfu_result_temp = eqlint(combined_a_temp, combined_b_temp);
                    time_enc_hw_temp = neorv32_cpu_csr_read(CSR_MCYCLE);
                    break;
            }
        
            // neorv32_uart0_printf("Time HW = %u cycles\n", time_enc_hw_temp); // Debug: print cycles.
        
            // Boolean temporal logic results are typically a single bit (0 or 1).
            bool result_boolean = (cfu_result_temp & 0x1);
            neorv32_uart0_printf("\n32-bit Combined Raw Result: 0x%x\n", cfu_result_temp);
            neorv32_uart0_printf("\nTemporal Logic Result (Boolean): %d\n", result_boolean);
            break;
        }
    }
    // --- Option 5: Temporal Logic (State of Two Inputs) ---
    else if (choice[0] == '5') {
        while (1) {
            neorv32_uart0_printf("\nHW MANUAL TEST (press 'q' to return to menu)\n");
        
            neorv32_uart0_puts("Enter lower bound of the first interval: ");
            neorv32_uart0_scan(bufferal, sizeof(bufferal), 1);
            if (bufferal[0] == 'q' && bufferal[1] == '\0') break;
        
            neorv32_uart0_puts("\nEnter upper bound of the first interval: ");
            neorv32_uart0_scan(bufferau, sizeof(bufferau), 1);
            if (bufferau[0] == 'q' && bufferau[1] == '\0') break;
        
            neorv32_uart0_puts("\nEnter lower bound of the second interval: ");
            neorv32_uart0_scan(bufferbl, sizeof(bufferbl), 1);
            if (bufferbl[0] == 'q' && bufferbl[1] == '\0') break;
        
            neorv32_uart0_puts("\nEnter upper bound of the second interval: ");
            neorv32_uart0_scan(bufferbu, sizeof(bufferbu), 1);
            if (bufferbu[0] == 'q' && bufferbu[1] == '\0') break;
        
            neorv32_uart0_printf("\nProcessing...\n");
        
            // Convert inputs and create intervals.
            float valueal = atof(bufferal);
            float valueau = atof(bufferau);
            float valuebl = atof(bufferbl);
            float valuebu = atof(bufferbu);
        
            interval_t a_state = interval(valueal, valueau);
            interval_t b_state = interval(valuebl, valuebu);
        
            // Combine intervals for CFU input.
            uint32_t combined_a_state = combine(a_state);
            uint32_t combined_b_state = combine(b_state);
        
            uint32_t cfu_state_result = 0; // Raw 32-bit result from CFU.
            uint32_t time_enc_hw_state;
        
            // Call the `stateint` CFU instruction for detailed temporal relationship.
            neorv32_cpu_csr_write(CSR_MCYCLE, 0);
            cfu_state_result = stateint(combined_a_state, combined_b_state);
            time_enc_hw_state = neorv32_cpu_csr_read(CSR_MCYCLE);
        
            // neorv32_uart0_printf("Time HW = %u cycles\n", time_enc_hw_state); // Debug: print cycles.
        
            // Extract the 4-bit state code from the raw CFU result.
            uint16_t result_state_code = cfu_state_result & 0xF;
        
            neorv32_uart0_printf("\n4-bit status: 0x%X (Binary: %d%d%d%d)\n",
                result_state_code,
                (result_state_code >> 3) & 0x1, // MSB
                (result_state_code >> 2) & 0x1,
                (result_state_code >> 1) & 0x1,
                result_state_code & 0x1          // LSB
            );
        
            // Array of descriptive strings for each possible 4-bit state code.
            // These correspond to Allen's Interval Algebra relationships.
            const char *status_text[16] = {
                "Status: No relation (disjoint/no overlap)", // 0x0
                "Status: i before j (i < j)",               // 0x1
                "Status: i meets j (i m j)",                // 0x2
                "Status: i overlaps j (i o j)",             // 0x3
                "Status: i during j (i d j)",               // 0x4
                "Status: i starts j (i s j)",               // 0x5
                "Status: i finishes j (i f j)",             // 0x6
                "Status: i equals j (i = j)",               // 0x7
                "Status: j before i (j < i)",               // 0x8
                "Status: j meets i (j m i)",                // 0x9
                "Status: j overlaps i (j o i)",             // 0xA
                "Status: j during i (j d i)",               // 0xB
                "Status: j starts i (j s i)",               // 0xC
                "Status: j finishes i (j f i)",             // 0xD
                "Status: Unknown (E)",                      // 0xE
                "Status: Unknown (F)"                       // 0xF
            };
        
            // Print the descriptive text based on the state code.
            if (result_state_code < 14) // Valid relationship codes are 0x0 to 0xD.
                neorv32_uart0_printf("%s\n", status_text[result_state_code]);
            else // For unknown/reserved codes.
                neorv32_uart0_printf("Status: Unknown (%X)\n", result_state_code);

            break;
        }
    }
    // --- Option 6: Root Finding with Bisection Algorithm ---
    else if (choice[0] == '6') {
        while (1) {
            // Define initial search parameters.
            interval_t founded_root_interval;
            interval_t search_range = interval(-10.0f, 10.0f); // Initial broad search range.
            double step_size = 1.0;                            // Step size for initial scanning.
            double tolerance = 1e-5;                           // Tolerance for bisection method.
            int max_iterations = 100;                          // Maximum iterations for bisection.

            // Prompt user to define the polynomial (degree and coefficients).
            horner();

            // Find an initial interval that potentially contains a root.
            if (find_root_interval(search_range, step_size, &founded_root_interval)) {
                neorv32_uart0_printf("------------------------------\n");
                // If a potential interval is found, run the bisection method.
                interval_t final_root_interval = bisection(founded_root_interval, tolerance, max_iterations, f);

                // Print the final root interval if valid.
                if (!isnan(final_root_interval.lower) && !isnan(final_root_interval.upper)) {
                    char stl[32], stu[32];
                    float_to_string(final_root_interval.lower, stl, 8);
                    float_to_string(final_root_interval.upper, stu, 8);
                    neorv32_uart0_printf("\nFound root interval: [%s, %s] (Combined hex: 0x%x)\n", stl, stu, combine(final_root_interval));

                    // Also print the function's value at this root interval.
                    interval_t f_at_root = f(final_root_interval);
                    char rtl[32], rtu[32];
                    float_to_string(f_at_root.lower, rtl, 8);
                    float_to_string(f_at_root.upper, rtu, 8);
                    neorv32_uart0_printf("\nf(root) = [%s, %s]\n", rtl, rtu);
                }
            } else {
                neorv32_uart0_printf("\nNo root found in the specified broad interval.\n");
            }
            break; // Exit root finding loop.
        }
    }
    // --- Option 7: Exit Program ---
    else if (choice[0] == '7') {
        neorv32_uart0_printf("\nExiting program.\n");
        return 0; // Terminate the program.
    }
    // --- Invalid Choice ---
    else {
        neorv32_uart0_printf("\nInvalid choice. Please try again.\n");
    }
  } // End of main menu while loop.

  // ----------------------------------------------------------
  // Execute an unimplemented CFU instruction word
  // ----------------------------------------------------------
  // This section is commented out in the provided code, but typically in a demo,
  // it might attempt to execute a non-existent CFU instruction to test
  // the CPU's illegal instruction exception handling.
  // neorv32_uart0_printf("\nExecuting non-implemented CFU instruction (raise ILLEGAL INSTRUCTION exception)...\n");
  // Some unimplemented CFU instruction call here (e.g., neorv32_cfu_r3_instr(0xFF, 0, 0, 0);)

  neorv32_uart0_printf("\nCFU demo program completed.\n");
  return 0; // Final return for completeness (though unreachable if main loop is infinite and not exited by '7').
}