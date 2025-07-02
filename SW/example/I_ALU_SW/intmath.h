#ifndef INTMATH_H // Include guard: Prevents multiple inclusions of this header file.
#define INTMATH_H

#include <stdint.h> // Provides standard integer types like uint32_t and uint16_t.

/**********************************************************************//**
 * @name Define macros for easy CFU instruction wrapping
 * @brief These macros provide a convenient C-level interface to the custom
 * instructions implemented in the RISC-V Custom Function Unit (CFU).
 *
 * Each macro corresponds to a specific interval arithmetic or temporal
 * logic operation. They internally call `neorv32_cfu_r3_instr`, which is
 * responsible for generating the appropriate RISC-V instruction to
 * communicate with the CFU.
 *
 * `neorv32_cfu_r3_instr` typically takes parameters like:
 * `neorv32_cfu_r3_instr(funct7_opcode, funct3_opcode, rs1_operand, rs2_operand)`
 * Where `funct7_opcode` (7 bits) and `funct3_opcode` (3 bits) define the
 * specific custom instruction, and `rs1_operand` and `rs2_operand` are the
 * input registers. If an operand is not used, it's often passed as `0`.
 **************************************************************************/
/**@{*/ // Doxygen group start marker for documentation generation.

// Interval Arithmetic Functions Opcodes:
// These macros map standard arithmetic operations to specific CFU instructions.
// `funct3_opcode` is consistently `0b000` for these.
#define addint(v0, v1) neorv32_cfu_r3_instr(0b0000000, 0b000, v0,  v1) // Custom instruction for interval addition.
#define subint(v0, v1) neorv32_cfu_r3_instr(0b0000100, 0b000, v0,  v1) // Custom instruction for interval subtraction.
#define mulint(v0, v1) neorv32_cfu_r3_instr(0b0001000, 0b000, v0,  v1) // Custom instruction for interval multiplication.
#define divint(v0, v1) neorv32_cfu_r3_instr(0b0001100, 0b000, v0,  v1) // Custom instruction for interval division.

// Interval Properties Opcodes:
// These macros access CFU instructions that compute various properties of a single interval.
#define midint(v0) neorv32_cfu_r3_instr(0b0100000, 0b000, v0,  0) // Custom instruction for interval midpoint.
#define wdtint(v0) neorv32_cfu_r3_instr(0b0100100, 0b000, v0,  0) // Custom instruction for interval width.
#define radint(v0) neorv32_cfu_r3_instr(0b0101000, 0b000, v0,  0) // Custom instruction for interval radius.
#define minint(v0) neorv32_cfu_r3_instr(0b0101100, 0b000, v0,  0) // Custom instruction for interval minimum (lower bound).
#define maxint(v0) neorv32_cfu_r3_instr(0b0110000, 0b000, v0,  0) // Custom instruction for interval maximum (upper bound).

// Temporal Logic Opcodes (Allen's Interval Algebra):
// These macros wrap CFU instructions designed to determine specific qualitative
// relationships between two time intervals.
#define stateint(v0, v1) neorv32_cfu_r3_instr(0b1000000, 0b000, v0,  v1) // Custom instruction for general interval state comparison.
#define bfrint(v0, v1) neorv32_cfu_r3_instr(0b1000100, 0b000, v0,  v1) // Custom instruction for 'before' relationship.
#define mtsint(v0, v1) neorv32_cfu_r3_instr(0b1001000, 0b000, v0,  v1) // Custom instruction for 'meets' relationship.
#define ovrint(v0, v1) neorv32_cfu_r3_instr(0b1001100, 0b000, v0,  v1) // Custom instruction for 'overlaps' relationship.
#define durint(v0, v1) neorv32_cfu_r3_instr(0b1010000, 0b000, v0,  v1) // Custom instruction for 'during' relationship.
#define strint(v0, v1) neorv32_cfu_r3_instr(0b1010100, 0b000, v0,  v1) // Custom instruction for 'starts' relationship.
#define finint(v0, v1) neorv32_cfu_r3_instr(0b1011000, 0b000, v0,  v1) // Custom instruction for 'finishes' relationship.
#define eqlint(v0, v1) neorv32_cfu_r3_instr(0b1011100, 0b000, v0,  v1) // Custom instruction for 'equals' relationship.
/**@}*/ // Doxygen group end marker.

// Interval type definition:
// A structure to represent a closed interval, comprising a lower and an upper bound.
typedef struct {
    float lower; // The lower bound of the interval.
    float upper; // The upper bound of the interval.
} interval_t;

// --- Function Prototypes (Declarations) ---
// These declarations inform the compiler about the functions defined in intmath.c,
// allowing them to be called from other C files that include this header.

// Packs an `interval_t` structure (containing two 32-bit floats) into a single 32-bit unsigned integer.
uint32_t combine(interval_t x);
// Extracts an `interval_t` structure (with two 32-bit floats) from a single 32-bit unsigned integer.
interval_t extract(uint32_t combined);

// Interval Arithmetic Functions:
// These functions implement the basic interval arithmetic operations,
// leveraging the `combine` and `extract` functions to interact with the CFU.
interval_t interval_add(interval_t a, interval_t b); // Adds two intervals.
interval_t interval_sub(interval_t a, interval_t b); // Subtracts two intervals.
interval_t interval_mul(interval_t a, interval_t b); // Multiplies two intervals.
interval_t interval_div(interval_t a, interval_t b); // Divides two intervals.

// Advanced Operations:
interval_t interval_pow(interval_t x, int n); // Calculates the integer power of an interval.

// Utility Functions:
interval_t interval_const(float c);         // Creates a 'point' interval from a constant float value.
interval_t interval(float lower, float upper); // Creates an interval from lower and upper bounds.

// Interval Property Functions:
// These functions compute specific properties of an interval using CFU instructions.
float midint_interval(interval_t x); // Returns the midpoint of the interval.
float wdtint_interval(interval_t x); // Returns the width of the interval.
float radint_interval(interval_t x); // Returns the radius of the interval.
float minint_interval(interval_t x); // Returns the minimum (lower bound) of the interval.
float maxint_interval(interval_t x); // Returns the maximum (upper bound) of the interval.

// Temporal Logic Operations:
// These functions check Allen's Interval Algebra relationships between two intervals.
int stateint_interval(interval_t a, interval_t b); // Returns the temporal relationship state code.
int bfrint_interval(interval_t a, interval_t b); // Checks for 'before' relationship.
int finint_interval(interval_t a, interval_t b); // Checks for 'finishes' relationship.
int mtsint_interval(interval_t a, interval_t b); // Checks for 'meets' relationship.
int ovrint_interval(interval_t a, interval_t b); // Checks for 'overlaps' relationship.
int durint_interval(interval_t a, interval_t b); // Checks for 'during' relationship.
int strint_interval(interval_t a, interval_t b); // Checks for 'starts' relationship.
int eqlint_interval(interval_t a, interval_t b); // Checks for 'equals' relationship.

#endif // End of INTMATH_H include guard.