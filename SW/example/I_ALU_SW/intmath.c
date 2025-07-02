#include "intmath.h" // Includes the custom interval math header, which defines interval_t and CFU instruction macros.
#include "neorv32.h" // Provides access to NEORV32-specific functions, such as UART communication (neorv32_uart0_puts) and Custom Function Unit (CFU) instructions.
#include <math.h>    // Standard C math library, crucial for floating-point constants like INFINITY and NAN.

/**
 * @brief Converts a 16-bit 'half-precision' floating-point number to a 32-bit single-precision float.
 *
 * This function parses a 16-bit input (assumed to be a half-precision float format,
 * similar to IEEE 754 float16 with 1 sign bit, 5 exponent bits, and 10 mantissa bits)
 * and converts it into a standard 32-bit `float`. It handles special cases like
 * infinity, NaN (Not a Number), zero, and denormalized numbers according to typical
 * floating-point conversion rules.
 *
 * @param h The 16-bit half-precision floating-point number.
 * @return The converted 32-bit single-precision floating-point number.
 */
float h_t_f(uint16_t h) {
    // Extract the sign bit (MSB of the 16-bit number).
    uint32_t sign = (h >> 15) & 0x1;
    // Extract the 5-bit exponent.
    int32_t exponent = (h >> 10) & 0x1F; // 0x1F is 5'b11111
    // Extract the 10-bit mantissa (fractional part).
    uint16_t mantissa = h & 0x3FF; // 0x3FF is 10'b1111111111

    // Handle special cases: Infinity or NaN (exponent is all 1s).
    if (exponent == 0x1F) {
        if (mantissa == 0) {
            // If mantissa is zero, it's Infinity (positive or negative).
            neorv32_uart0_puts(sign ? "-INF" : "INF"); // Output to UART for debugging/information.
            return sign ? -INFINITY : INFINITY; // Return standard C infinity constant.
        } else {
            // If mantissa is non-zero, it's NaN.
            neorv32_uart0_puts("NAN"); // Output to UART.
            return NAN; // Return standard C NaN constant.
        }
    }

    // Handle special case: Zero or Denormalized numbers (exponent is all 0s).
    if (exponent == 0) {
        if (mantissa == 0) {
            // If mantissa is also zero, it's a signed zero.
            return sign ? -0.0f : 0.0f;
        } else {
            // It's a denormalized number. Normalize it and adjust the exponent.
            // The implicit leading '1' is not present in denormalized numbers,
            // so we effectively find the true leading '1' and shift.
            exponent = 1; // Start with a minimal exponent for denormalized numbers.
            while ((mantissa & 0x400) == 0) { // Shift mantissa left until the implicit '1' (at bit 10) appears.
                mantissa <<= 1;
                exponent--; // Decrement exponent for each left shift.
            }
            mantissa &= ~0x400; // Clear the now explicit leading '1' as it's implicit in normalized form.
        }
    }

    // Adjust the exponent bias for conversion from 16-bit (bias 15) to 32-bit float (bias 127).
    // The adjusted exponent for 32-bit float is `exponent_16bit + (127 - 15)`.
    exponent = exponent + (127 - 15); // (127 - 15) = 112

    // Assemble the 32-bit floating-point bit pattern.
    // Sign bit at position 31.
    // Exponent bits at positions 23-30.
    // Mantissa bits (10-bit) shifted left by 13 to fill 32-bit float's 23-bit mantissa space.
    uint32_t f_bits = (sign << 31) | (exponent << 23) | (mantissa << 13);

    // Use a union to re-interpret the 32-bit integer bit pattern as a float.
    union {
        uint32_t u; // Integer representation.
        float f;    // Float representation.
    } uconv;

    uconv.u = f_bits; // Assign the raw bit pattern.
    return uconv.f;   // Return the float value.
}

/**
 * @brief Converts a 32-bit single-precision float to a 16-bit 'half-precision' floating-point number.
 *
 * This function takes a standard 32-bit `float` and converts it to the custom 16-bit
 * half-precision float format (1 sign bit, 5 exponent bits, 10 mantissa bits).
 * It handles overflow and underflow scenarios by clamping to infinity/zero or denormalizing.
 *
 * @param f The 32-bit single-precision floating-point number.
 * @return The converted 16-bit half-precision floating-point number.
 */
uint16_t f_t_h(float f) {
    // Use a union to get the raw 32-bit integer bit pattern of the float.
    union {
        float f;    // Float representation.
        uint32_t u; // Integer representation.
    } uconv;

    uconv.f = f; // Assign the float value to the union.

    uint32_t f_bits = uconv.u; // Get the raw bit pattern.

    // Extract the sign bit from the 32-bit float and place it at bit 15 for 16-bit format.
    uint16_t sign = (f_bits >> 16) & 0x8000; // Shift by 16 (31 - 15 = 16).

    // Extract the 8-bit exponent from the 32-bit float, subtract its bias (127),
    // and add the 16-bit format's bias (15) to get the new exponent.
    int32_t exponent = ((f_bits >> 23) & 0xFF) - 127 + 15;

    // Extract the 23-bit mantissa from the 32-bit float and truncate it to 10 bits for 16-bit format.
    uint16_t mantissa = (f_bits >> 13) & 0x3FF; // Shift right by 13 (23 - 10 = 13).

    // Handle underflow/denormalized cases: If exponent is too small.
    if (exponent <= 0) {
        // If the exponent is zero or negative, the number is too small for normalized representation.
        // Return signed zero (or potential denormal if more complex handling was implemented).
        return sign;
    }
    // Handle overflow cases: If exponent is too large.
    else if (exponent >= 31) {
        // If the exponent exceeds the 16-bit max (30, as 31 is reserved for INF/NaN),
        // represent it as infinity or NaN.
        // 0x7C00 sets the 5 exponent bits to all 1s.
        // If mantissa is non-zero, it's a NaN; otherwise, it's infinity.
        return sign | 0x7C00 | (mantissa ? 1 : 0);
    }

    // Normal conversion: Assemble the 16-bit floating-point bit pattern.
    return sign | (exponent << 10) | mantissa;
}

/**
 * @brief Creates an `interval_t` structure.
 *
 * This utility function takes two float values and constructs an `interval_t`
 * representing a closed interval [lower, upper].
 *
 * @param lower The lower bound of the interval.
 * @param upper The upper bound of the interval.
 * @return An `interval_t` structure.
 */
interval_t interval(float lower, float upper) {
    interval_t result;
    result.lower = lower;
    result.upper = upper;
    return result;
}

/**
 * @brief Combines an `interval_t` into a single 32-bit unsigned integer for CFU processing.
 *
 * This function takes an `interval_t` (which contains two 32-bit floats for lower and upper bounds),
 * converts each float into its 16-bit half-precision representation using `f_t_h`,
 * and then packs these two 16-bit values into a single 32-bit `uint32_t`.
 * The lower bound occupies the most significant 16 bits, and the upper bound the least significant 16 bits.
 * This packing is essential for passing interval data to the CFU as a single 32-bit operand.
 *
 * @param x The `interval_t` structure to combine.
 * @return A `uint32_t` containing the packed 16-bit representations of the interval's bounds.
 */
uint32_t combine(interval_t x) {
    uint16_t lower_half = f_t_h(x.lower); // Convert lower bound to 16-bit.
    uint16_t upper_half = f_t_h(x.upper); // Convert upper bound to 16-bit.
    // Pack: lower_half into bits 31:16, upper_half into bits 15:0.
    return ((uint32_t)lower_half << 16) | (uint32_t)upper_half;
}

/**
 * @brief Extracts an `interval_t` from a single 32-bit unsigned integer received from CFU.
 *
 * This function reverses the `combine` operation. It takes a `uint32_t` (expected to contain
 * two packed 16-bit half-precision numbers) and separates them. It then converts each 16-bit
 * value back into a 32-bit float using `h_t_f` to reconstruct the `interval_t`.
 *
 * @param combined The `uint32_t` containing the packed interval bounds.
 * @return An `interval_t` structure with the extracted and converted float bounds.
 */
interval_t extract(uint32_t combined) {
    uint16_t lower_half = (combined >> 16) & 0xFFFF; // Extract the upper 16 bits as lower_half.
    uint16_t upper_half = combined & 0xFFFF;         // Extract the lower 16 bits as upper_half.

    interval_t result;
    result.lower = h_t_f(lower_half); // Convert 16-bit lower_half back to 32-bit float.
    result.upper = h_t_f(upper_half); // Convert 16-bit upper_half back to 32-bit float.

    return result;
}

// --- Basic Interval Arithmetic Operations via CFU ---
// These functions perform standard interval arithmetic using the Custom Function Unit (CFU).
// They combine the input intervals, send them to the CFU via a specific instruction macro,
// and then extract the CFU's 32-bit result back into an interval_t.

/**
 * @brief Performs interval addition (a + b) using the CFU.
 * @param a The first interval operand.
 * @param b The second interval operand.
 * @return The result of the interval addition.
 */
interval_t interval_add(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a); // Pack interval 'a'.
    uint32_t combined_b = combine(b); // Pack interval 'b'.
    uint32_t result = addint(combined_a, combined_b); // Call CFU's interval addition instruction.
    return extract(result); // Unpack and return the result.
}

/**
 * @brief Performs interval subtraction (a - b) using the CFU.
 * @param a The first interval operand.
 * @param b The second interval operand.
 * @return The result of the interval subtraction.
 */
interval_t interval_sub(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    uint32_t result = subint(combined_a, combined_b); // Call CFU's interval subtraction instruction.
    return extract(result);
}

/**
 * @brief Performs interval multiplication (a * b) using the CFU.
 * @param a The first interval operand.
 * @param b The second interval operand.
 * @return The result of the interval multiplication.
 */
interval_t interval_mul(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    uint32_t result = mulint(combined_a, combined_b); // Call CFU's interval multiplication instruction.
    return extract(result);
}

/**
 * @brief Performs interval division (a / b) using the CFU.
 * @param a The first interval operand (dividend).
 * @param b The second interval operand (divisor).
 * @return The result of the interval division.
 */
interval_t interval_div(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    uint32_t result = divint(combined_a, combined_b); // Call CFU's interval division instruction.
    return extract(result);
}

// --- Complex Operations ---

/**
 * @brief Calculates the integer power of an interval (x^n).
 *
 * This function computes `x` raised to the power of `n` using repeated
 * interval multiplication. Note that this is a software-implemented function
 * and does not directly use a single CFU instruction for power.
 *
 * @param x The base interval.
 * @param n The integer exponent.
 * @return The result of the interval power operation.
 */
interval_t interval_pow(interval_t x, int n) {
    interval_t result = x; // Initialize result with the base interval.
    for (int i = 1; i < n; i++) {
        result = interval_mul(result, x); // Multiply 'result' by 'x' (n-1) times.
    }
    return result;
}

/**
 * @brief Creates a 'point' interval from a single constant float value.
 *
 * A point interval has identical lower and upper bounds (e.g., [c, c]).
 * This is useful for representing precise numbers within the interval arithmetic framework.
 *
 * @param c The constant float value.
 * @return An `interval_t` where both `lower` and `upper` bounds are `c`.
 */
interval_t interval_const(float c) {
    interval_t result;
    result.lower = c;
    result.upper = c;
    return result;
}

// --- Interval Property Functions ---
// These functions calculate specific properties of an interval using dedicated CFU instructions.
// The CFU typically returns a 16-bit half-precision float, which is then converted back to a 32-bit float.

/**
 * @brief Calculates the width of an interval using the CFU.
 *
 * The width of an interval [a, b] is (b - a).
 * @param a The interval operand.
 * @return The width of the interval as a 32-bit float.
 */
float wdtint_interval(interval_t a) {
    uint32_t combined_a = combine(a); // Pack the interval.
    // Call CFU's width instruction and convert the 16-bit result to a 32-bit float.
    return h_t_f(wdtint(combined_a));
}

/**
 * @brief Calculates the midpoint of an interval using the CFU.
 *
 * The midpoint of an interval [a, b] is (a + b) / 2.
 * @param a The interval operand.
 * @return The midpoint of the interval as a 32-bit float.
 */
float midint_interval(interval_t a) {
    uint32_t combined_a = combine(a);
    return h_t_f(midint(combined_a));
}

/**
 * @brief Calculates the radius of an interval using the CFU.
 *
 * The radius of an interval [a, b] is (b - a) / 2.
 * @param a The interval operand.
 * @return The radius of the interval as a 32-bit float.
 */
float radint_interval(interval_t a) {
    uint32_t combined_a = combine(a);
    return h_t_f(radint(combined_a));
}

/**
 * @brief Returns the lower bound (minimum value) of an interval using the CFU.
 * @param a The interval operand.
 * @return The lower bound of the interval as a 32-bit float.
 */
float minint_interval(interval_t a) {
    uint32_t combined_a = combine(a);
    return h_t_f(minint(combined_a));
}

/**
 * @brief Returns the upper bound (maximum value) of an interval using the CFU.
 * @param a The interval operand.
 * @return The upper bound of the interval as a 32-bit float.
 */
float maxint_interval(interval_t a) {
    uint32_t combined_a = combine(a);
    return h_t_f(maxint(combined_a));
}

// --- Temporal Logic Operations (Allen's Interval Algebra) ---
// These functions determine specific qualitative relationships between two intervals
// based on Allen's Interval Algebra. They use CFU instructions and typically return
// a boolean (0 or 1) indicating if the relationship holds. `stateint` returns a more
// complex state code.

/**
 * @brief Determines the temporal relationship state between two intervals using the CFU.
 *
 * This function likely returns a multi-bit code representing the complex
 * Allen's Interval Algebra relationship between intervals `a` and `b`.
 * The result is masked with `0xF` (binary `1111`) to extract relevant bits.
 *
 * @param a The first interval.
 * @param b The second interval.
 * @return An integer representing the state code, masked to the lower 4 bits.
 */
int stateint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return stateint(combined_a, combined_b) & 0xF; // Call CFU instruction and apply 4-bit mask.
}

/**
 * @brief Checks if interval `a` is 'during' interval `b` using the CFU.
 *
 * (a_lower > b_lower AND a_upper < b_upper)
 * @param a The first interval.
 * @param b The second interval.
 * @return 1 if `a` is during `b`, 0 otherwise.
 */
int durint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return durint(combined_a, combined_b) & 1; // Mask with 1 to ensure boolean result.
}

/**
 * @brief Checks if interval `a` 'finishes' interval `b` using the CFU.
 *
 * (a_lower > b_lower AND a_upper == b_upper)
 * @param a The first interval.
 * @param b The second interval.
 * @return 1 if `a` finishes `b`, 0 otherwise.
 */
int finint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return finint(combined_a, combined_b) & 1;
}

/**
 * @brief Checks if interval `a` is 'before' interval `b` using the CFU.
 *
 * (a_upper < b_lower)
 * @param a The first interval.
 * @param b The second interval.
 * @return 1 if `a` is before `b`, 0 otherwise.
 */
int bfrint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return bfrint(combined_a, combined_b) & 1;
}

/**
 * @brief Checks if interval `a` 'meets' interval `b` using the CFU.
 *
 * (a_upper == b_lower)
 * @param a The first interval.
 * @param b The second interval.
 * @return 1 if `a` meets `b`, 0 otherwise.
 */
int mtsint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return mtsint(combined_a, combined_b) & 1;
}

/**
 * @brief Checks if interval `a` 'overlaps' interval `b` using the CFU.
 *
 * (a_lower < b_lower AND a_upper > b_lower AND a_upper < b_upper)
 * @param a The first interval.
 * @param b The second interval.
 * @return 1 if `a` overlaps `b`, 0 otherwise.
 */
int ovrint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return ovrint(combined_a, combined_b) & 1;
}

/**
 * @brief Checks if interval `a` 'starts' interval `b` using the CFU.
 *
 * (a_lower == b_lower AND a_upper < b_upper)
 * @param a The first interval.
 * @param b The second interval.
 * @return 1 if `a` starts `b`, 0 otherwise.
 */
int strint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return strint(combined_a, combined_b) & 1;
}

/**
 * @brief Checks if interval `a` 'equals' interval `b` using the CFU.
 *
 * (a_lower == b_lower AND a_upper == b_upper)
 * @param a The first interval.
 * @param b The second interval.
 * @return 1 if `a` equals `b`, 0 otherwise.
 */
int eqlint_interval(interval_t a, interval_t b) {
    uint32_t combined_a = combine(a);
    uint32_t combined_b = combine(b);
    return eqlint(combined_a, combined_b) & 1;
}