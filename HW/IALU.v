`define EXP 5       // Number of bits for the exponent
`define MANTISSA 10 // Number of bits for the mantissa (fractional part)
`define W 16        // INTERVAL LENGTH - Likely the width of a single floating-point number (e.g., 1 sign bit + 5 exponent bits + 10 mantissa bits = 16 bits)
`define TOTALW 32   // 2*W TOTAL INTERVAL LENGTH - Total width for two floating-point numbers or a combined result


// Error codes:
// 000 >= no error
// 001 >= zero case
// 010 >= +infinit overflow
// 011 >= -infinit overflow
// 100 >= Underflow
// 101 >= Div by infinit
// 110 >= +Div by zero
// 111 >= -Div by zero

module IALU (
    input  clk,             			  // Clock signal
    input  rst,             			  // Reset signal
    input  [(`TOTALW)-1:0]  a,        // First input operand (likely 32-bit, composed of two W-bit parts)
    input  [(`TOTALW)-1:0]  b,        // Second input operand (likely 32-bit, composed of two W-bit parts)
	 input  [ 4:0]  funct,   		  	  // Function code to determine the operation
	 input  [ 1:0]  fmt,     		     // Floating Point Format (not used)
	 input  [ 2:0]  rm,      		     // Rounding mode (not used)
    output [ 3:0]  stateCross, 		  // Output representing the state of cross-comparison
    output reg [`TOTALW-1:0]  result, // Output result of the operation
    output reg flag,        			  // Flag indicating completion or a special condition
    output reg [2:0] error,     		  // Error code output
    output dual               		  // Flag indicating a dual operation (e.g., for multiplication)
);
    // Internal wires for error signals from sub-modules
    wire [2:0] err_w, err_wal, err_wau, err_wml, err_wmu, err_wdl, err_wdu;
    // Internal wire for condition codes from ProcessRedirectorModule
    wire [  3:0] condition;
    // Wires for results from lower and upper parts of division
    wire [`W-1:0] ANSUDIV, ANSLDIV;
    // Wires for results from lower and upper parts of multiplication
    wire [`W-1:0] ANSUMUL, ANSLMUL;
    // Wires for results from lower and upper parts of addition/subtraction
    wire [`W-1:0] ANSLADD, ANSUADD;
    // Flags for completion of addition, multiplication, and division operations (lower and upper parts)
    wire flagadd1, flagadd2, flagmul1, flagmul2, flagdiv1, flagdiv2;
    // Registered flags to synchronize asynchronous flag signals
    reg flagadd1_reg, flagadd2_reg, flagdiv1_reg, flagdiv2_reg, flagmul1_reg, flagmul2_reg;

    // Combinational logic to determine the main error output
    always @(*) begin
        // If there's an error from the main error detector (err_w)
        if(|err_w)begin
            error <= err_w; // Assign that error
        end else begin
            // Otherwise, based on the function code, check for specific errors from sub-modules
            case (funct)
                5'b00000, 5'b00001: begin // Addition/Subtraction operations
                    error <= (|err_wau != 1'b0) ? err_wau : // Error from upper adder/subtractor
                                   (|err_wal != 1'b0) ? err_wal : 3'b000; // Error from lower adder/subtractor or no error
                end
                5'b00010: begin // Multiplication operation
                    error <= (|err_wmu != 1'b0) ? err_wmu : // Error from upper multiplier
                                   (|err_wml != 1'b0) ? err_wml : 3'b000; // Error from lower multiplier or no error
                end
                5'b00011: begin // Division operation
                    error <= (|err_wdu != 1'b0) ? err_wdu : // Error from upper divider
                                   (|err_wdl != 1'b0) ? err_wdl : 3'b000; // Error from lower divider or no error
                end
                default: begin
                    error <= 3'b000; // No operation or unknown function, set error to zero
                end
            endcase
        end
    end

    // Register to manage dual operation state (for division, specifically)
    reg [1:0] fdual = 0;
    // Wires for the processed inputs (F1, F2, S1, S2) from ProcessRedirectorModule
    wire [`W-1:0] F1, F2, S1, S2;

    // Instance of ProcessRedirectorModule
    // This module likely handles the initial processing of input operands 'a' and 'b',
    // extracting their upper (AU, BU) and lower (AL, BL) parts,
    // determining conditions for operations, and potentially detecting initial errors.
    ProcessRedirectorModule islem(
        .AL(a[`TOTALW-1:`W]),      // Lower part of 'a'
        .AU(a[      `W-1:0]),      // Upper part of 'a'
        .BL(b[`TOTALW-1:`W]),      // Lower part of 'b'
        .BU(b[      `W-1:0]),      // Upper part of 'b'
        .F1(F1),                    // First processed operand for lower unit
        .F2(F2),                    // First processed operand for upper unit
        .S1(S1),                    // Second processed operand for lower unit
        .S2(S2),                    // Second processed operand for upper unit
        .stateCross(stateCross),    // Output state from cross-comparator
        .condition(condition),      // Condition determined by the module
        .OPCODE(funct),             // Function code
        .dual(dual),                // Dual operation flag
        .error(err_w)               // Error signal from this module
    );

    // Instances of Adder/Subtractor modules for lower and upper parts
    AdderSubtractorTopModule adderdown(F1, S1, funct, ANSLADD, flagadd1, err_wal); // Lower part
    AdderSubtractorTopModule adderup  (F2, S2, funct, ANSUADD, flagadd2, err_wau); // Upper part

    // Instances of Multiplier modules for lower and upper parts
    // Parameter `updown` is used to differentiate between the lower (0) and upper (1) multipliers
    MultiplierTopModule #(.updown(0)) multdown (clk, F1, S1, F2, S2, funct, dual, ANSLMUL, flagmul1, err_wml); // Lower part
    MultiplierTopModule #(.updown(1)) multup   (clk, F2, S2, F1, S1, funct, dual, ANSUMUL, flagmul2, err_wmu); // Upper part

    // Instances of Divider modules for lower and upper parts
    DividerTopModule divdown(F1, S1, funct, ANSLDIV, flagdiv1, err_wdl); // Lower part
    DividerTopModule divup(F2, S2, funct, ANSUDIV, flagdiv2, err_wdu);   // Upper part

    // Register flags to handle asynchronous setting and synchronize with clock
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            // On reset, clear all flags and results
            flagadd1_reg <= 1'b0;
            flagadd2_reg <= 1'b0;
            flagdiv1_reg <= 1'b0;
            flagdiv2_reg <= 1'b0;
            flagmul1_reg <= 1'b0;
            flagmul2_reg <= 1'b0;
            result <= 32'b0;
            flag <= 1'b0;
            fdual <= 2'b0;
        end else begin
            // Register flags when they become 1 (edge detection for combinatorial flags)
            if (flagadd1) flagadd1_reg <= 1'b1;
            if (flagadd2) flagadd2_reg <= 1'b1;
            if (flagdiv1) flagdiv1_reg <= 1'b1;
            if (flagdiv2) flagdiv2_reg <= 1'b1;
            if (flagmul1) flagmul1_reg <= 1'b1;
            if (flagmul2) flagmul2_reg <= 1'b1;

            // Handle add/subtract operations (when both lower and upper parts are ready)
            if (flagadd1_reg && flagadd2_reg) begin
                if (funct == 5'b00001 || funct == 5'b00000) begin
                    result <= {ANSLADD, ANSUADD}; // Concatenate results from lower and upper adders
                    flag <= 1'b1; // Set main flag indicating operation complete
                    // Reset flags after capturing result
                    flagadd1_reg <= 1'b0;
                    flagadd2_reg <= 1'b0;
                end
                // Specific add/sub cases where only the upper part result is relevant, padded with zeros
                if (funct == 5'b01001 || funct == 5'b01000 || funct == 5'b01010) begin
                    result <= {{16{1'b0}}, ANSUADD}; // Pad upper result with 16 zeros for lower part
                    flag <= 1'b1;
                    // Reset flags after capturing result
                    flagadd1_reg <= 1'b0;
                    flagadd2_reg <= 1'b0;
                end
            end

            // Pass-through for specific function codes, taking parts of 'a' as result
            if (funct == 5'b01011 ) begin // Function code for directly taking the upper part of 'a'
                result <= {{16{1'b0}}, a[`TOTALW-1:`W]};
                flag <= 1'b1;
            end
            if (funct == 5'b01100) begin // Function code for directly taking the lower part of 'a'
                result <= {{16{1'b0}}, a[      `W-1:0]};
                flag <= 1'b1;
            end

            // Handle multiply operations
            if (flagmul1_reg && flagmul2_reg) begin
                if (funct == 5'b00010) begin
                    result <= {ANSLMUL, ANSUMUL}; // Concatenate results from lower and upper multipliers
                    flag <= 1'b1;
                    // Reset flags after capturing result
                    flagmul1_reg <= 1'b0;
                    flagmul2_reg <= 1'b0;
                end
            end

            // Handle divide operations
            if (flagdiv1_reg && flagdiv2_reg) begin
                if (funct == 5'b00011) begin
                    result <= {ANSLDIV, ANSUDIV}; // Concatenate results from lower and upper dividers
                    // Logic for dual division, likely a multi-cycle operation
                    if (dual == 1'b1 && fdual == 2'b00) begin
                        fdual <= 2'b01;
                    end else if (dual == 1'b1 && fdual == 2'b01) begin
                        fdual <= 2'b10;
                    end else if (dual == 1'b1 && fdual == 2'b10) begin
                        fdual <= 2'b11;
                    end else begin
                        flag <= 1'b1; // Set main flag when dual operation is complete or not dual
                    end
                    // Reset flags after capturing result
                    flagdiv1_reg <= 1'b0;
                    flagdiv2_reg <= 1'b0;
                end
            end

            // Handle other operation results (e.g., comparisons)
            if (funct[4:3] == 2'b10) begin
                if(funct == 5'b10000)begin // Specific function for stateCross direct output
                    result <= {{28{1'b0}},stateCross}; // Pad stateCross with zeros to TOTALW
                    flag <= 1'b1;
                end else begin // General comparison function
                    result <= {{31{1'b0}},((stateCross[2:0] == funct[2:0]) && (stateCross[3] == 1'b0)?1'b1:1'b0)};
                    flag <= 1'b1;
                end
            end

            // Final flag reset and result invalidation if flag is set (likely for next cycle)
            if (flag) begin
                flag <= 1'b0;
                // If dual, result is from multiplier, otherwise undefined (32'bz)
                result <= dual?{ANSLMUL, ANSUMUL}: 32'bz;
            end
        end
    end
endmodule

module ProcessRedirectorModule(
        input [`W-1:0] AU,        // Upper part of operand A
        input [`W-1:0] AL,        // Lower part of operand A
        input [`W-1:0] BU,        // Upper part of operand B
        input [`W-1:0] BL,        // Lower part of operand B
        input [4:0] OPCODE,       // Operation code
        output [3:0] stateCross,  // Output from cross-comparator
        output reg [3:0] condition = 4'b1111, // Condition code for operand selection
        output reg [`W-1:0] F1, S1, F2, S2, // Processed operands for computation units
        output reg dual,                  // Flag for dual operation mode
        output reg [2:0] error            // Error output
        );

    wire [2:0] errore; // Internal error wire from ErrorDetector
    reg flag = 0;       // Internal flag, likely for indicating processing completion
    wire G_AU_0;       // True if AU > 0
    wire G_BU_0;       // True if BU > 0
    wire L_AL_0;       // True if AL < 0
    wire L_BL_0;       // True if BL < 0

    // Instances of ZeroComparator modules
    ZeroComparatorG cmp_AU_0(.A(AU), .G(G_AU_0)); // Compares AU with 0 for greater than
    ZeroComparatorL cmp_AL_0(.A(AL), .L(L_AL_0)); // Compares AL with 0 for less than
    ZeroComparatorG cmp_BU_0(.A(BU), .G(G_BU_0)); // Compares BU with 0 for greater than
    ZeroComparatorL cmp_BL_0(.A(BL), .L(L_BL_0)); // Compares BL with 0 for less than

    // Instance of CrossComparator module
    CrossComparator cross_comp(.AU(AU), .AL(AL), .BU(BU), .BL(BL), .state(stateCross)); // Compares cross-boundaries of intervals

    // Instance of ErrorDetector module
    ErrorDetector errdet(.AU(AU[`W-2:0]), .AL(AL[`W-2:0]), .BU(BU[`W-2:0]), .BL(BL[`W-2:0]), .error(errore)); // Detects NaN/Inf errors

    reg errordiv = 1'b0; // Flag for division-specific errors (e.g., division by zero)

    // Combinational logic for processing operands and setting flags/errors
    always @(*) begin
        errordiv = 1'b0;  // Reset division error flag
        dual = 1'b0;      // Reset dual flag
        condition = 4'b0000; // Reset condition code
        flag = 0;         // Reset internal flag
        F1 = `W'b0;       // Reset processed operands
        S1 = `W'b0;
        F2 = `W'b0;
        S2 = `W'b0;

        // Check any error bit is 1 or not from ErrorDetector
        if(|errore) begin
            error = errore;
        end
        // Then check for specific division error
        else if(errordiv) begin
            error = {3'b110}; // Error code for division by zero
        end

        // Logic based on the OPCODE (function code)
        if(OPCODE[4:2] == 3'b000) begin // Arithmetic operations (Add, Subtract, Multiply, Divide)
            if(OPCODE[1:0] == 2'b10 || OPCODE[1:0] == 2'b11) begin // Multiply or Divide
                // Case 1: AL >= 0 && BL >= 0
                if (!L_AL_0 && !L_BL_0) begin
                    // Condition setting based on OPCODE
                    condition = (OPCODE == 4'b0010) ? 4'b0011 : 4'b0110;
                end
                // Case 2: AL >= 0 && BL < 0 < BU
                else if (!L_AL_0 && L_BL_0 && G_BU_0) begin
                    condition = (OPCODE == 5'b00010) ? 4'b1011 : 4'b1111;
                    errordiv = (OPCODE == 5'b00010) ? 1'b0 : 1'b1; // Set division error if not multiplication
                end
                // Case 3: AL >= 0 && BU <= 0
                else if (!L_AL_0 && !G_BU_0) begin
                    condition = (OPCODE == 5'b00010) ? 4'b1001 : 4'b1100;
                end
                // Case 4: AL < 0 < AU && BL >= 0
                else if (L_AL_0 && G_AU_0 && !L_BL_0) begin
                    condition = (OPCODE == 5'b00010) ? 4'b0111 : 4'b0010;
                end
                // Case 5: AL < 0 < AU && BU <= 0
                else if (L_AL_0 && G_AU_0 && !G_BU_0) begin
                    condition = (OPCODE == 5'b00010) ? 4'b1000 : 4'b1101;
                end
                // Case 6: AU <= 0 && BL >= 0
                else if (!G_AU_0 && !L_BL_0) begin
                    condition = (OPCODE == 5'b00010) ? 4'b0110 : 4'b0011;
                end
                // Case 7: AU <= 0 && BL < 0 < BU
                else if (!G_AU_0 && L_BL_0 && G_BU_0) begin
                    condition = (OPCODE == 5'b00010) ? 4'b0100 : 4'b1111;
                    errordiv = (OPCODE == 5'b00010) ? 1'b0 : 1'b1; // Set division error if not multiplication
                end
                // Case 8: AU <= 0 && BU <= 0
                else if (!G_AU_0 && !G_BU_0 ) begin
                    condition = (OPCODE == 5'b00010) ? 4'b1100 : 4'b1001;
                end
                // Case 9: AL < 0 < AU && BL < 0 < BU
                else if (L_AL_0 && G_AU_0 && L_BL_0 && G_BU_0) begin
                    condition = (OPCODE == 5'b00010) ? 4'b1110 : 4'b1111;
                    errordiv = (OPCODE == 5'b00010) ? 1'b0 : 1'b1; // Set division error if not multiplication
                    dual = (OPCODE == 5'b00010); // Set dual flag specifically for multiplication
                end
                // Default case if no specific condition matches
                else begin
                    condition = 4'b0000;
                end
            end
            else if (OPCODE[1:0] == 2'b01) begin // Subtraction
                // Condition based on cross-comparison state
                condition = (stateCross == 4'b0111) ? 4'b0011 : 4'b0110;
            end
            else begin // Addition
                condition = 4'b0011;
            end

            // Assign F1, S1, F2, S2 based on the determined condition
            // These assignments effectively select which part (AU/AL, BU/BL) goes to which operand slot
            F1 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[3] ? AU : AL) : AL;
            S1 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[2] ? BU : BL) : BU;
            F2 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[1] ? AU : AL) : AU;
            S2 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[0] ? BU : BL) : BL;
            flag = 1'b1; // Set internal flag as processing is complete
        end
        else if (OPCODE[4:3] == 2'b01)begin // Other operation group (e.g., for specific data movements)
            if(OPCODE[2:0] == 3'b000 || OPCODE[2:0] == 3'b001 || OPCODE[2:0] == 3'b010) begin
                // Direct assignment of AU and AL to F2 and S2, F1/S1 are zeroed
                F1 = 16'b0;
                S1 = 16'b0;
                F2 = AU;
                S2 = AL;
            end
        end
    end
endmodule

module Comparator
        #(parameter ws = 1)( // Parameter 'ws' likely indicates signed (1) or unsigned (0) comparison
        input [`W-1:0] A, // First operand
        input [`W-1:0] B, // Second operand
        output reg G,     // True if A > B
        output reg E,     // True if A == B
        output reg flag   // Flag indicating comparison completion
        );

    // Extract sign, exponent, and fractional parts from A
    wire A_S = A[`W-1];                // Sign bit of A
    wire [`EXP-1:0] A_EXP = A[`W-2:`W-1-`EXP]; // Exponent of A
    wire [`MANTISSA-1:0] A_FRACT = A[`MANTISSA-1:0]; // Mantissa/Fraction of A

    // Extract sign, exponent, and fractional parts from B
    wire B_S = B[`W-1];                // Sign bit of B
    wire [`EXP-1:0] B_EXP = B[`W-2:`W-1-`EXP]; // Exponent of B
    wire [`MANTISSA-1:0] B_FRACT = B[`MANTISSA-1:0]; // Mantissa/Fraction of B

    reg L; // Internal flag for A < B

    // Combinational logic for comparison
    always @(*) begin
        G = 0;   // Initialize Greater than flag
        E = 0;   // Initialize Equal flag
        L = 0;   // Initialize Less than flag
        flag = 0; // Initialize completion flag

        if (A == B) begin
            E = 1; // If A and B are exactly equal
        end else if ((A_S != B_S)) begin // If signs are different
            if (A_S) L = 1; // If A is negative, B is positive, then A < B
            else G = 1;     // If A is positive, B is negative, then A > B
        end else begin // If signs are the same
            if(ws)begin // If 'ws' (signed comparison) is enabled
                // Compare exponents
                if (A_EXP > B_EXP) begin
                     if (!A_S ) G = 1; // If positive, A > B
                     else L = 1;       // If negative, A < B
                end else if (A_EXP < B_EXP) begin
                     if (!A_S) L = 1;  // If positive, A < B
                     else G = 1;       // If negative, A > B
                end else begin // If exponents are the same, compare mantissas
                     if (A_FRACT > B_FRACT) begin
                         if (!A_S) G = 1; // If positive, A > B
                         else L = 1;       // If negative, A < B
                     end else begin
                         if (!A_S) L = 1;  // If positive, A < B
                         else G = 1;       // If negative, A > B
                     end
                end
            end else begin // If 'ws' (unsigned comparison) is disabled or 0
                // Compare exponents directly (effectively unsigned for magnitude)
                if (A_EXP > B_EXP) begin
                     G = 1;
                end else if (A_EXP < B_EXP) begin
                     L = 1;
                end else begin // If exponents are the same, compare mantissas directly
                     if (A_FRACT > B_FRACT) begin
                         G = 1;
                     end else begin
                         L = 1;
                     end
                end
            end
        end
        flag = 1; // Set completion flag
    end
endmodule

module Four_Bit_Divider(input [`MANTISSA:0] a,         // Dividend (mantissa + implicit leading bit)
                                 input [`MANTISSA:0] b,         // Divisor (mantissa + implicit leading bit)
                                 output reg [`MANTISSA+1:0] div_result); // Division result

    integer i = 0; // Loop counter
    reg [`MANTISSA+1:0] n; // Intermediate remainder
    reg [`MANTISSA+1:0] c; // Current remainder

    // Combinational logic for non-restoring division
    always @(*)begin
        n=0; // Initialize
        c=0; // Initialize

        // Determine the first bit of the quotient
        div_result[`MANTISSA+1] = (a >= b)? 1 : 0;
        // Calculate the initial remainder
        c = (a >= b)? (a-b)<<1 : a<<1; // If a >= b, c = (a-b)*2, else c = a*2

        // Loop to calculate the remaining quotient bits
        for(i = 1; i<`MANTISSA+2; i=i+1)begin
            n = c-{1'b1,b}; // n = c - (1 + b) (effectively c - b if b is treated as 1.mantissa)
            if(n[`MANTISSA+1])begin // If n is negative (most significant bit is 1)
                div_result[`MANTISSA+1-i] = 1; // Quotient bit is 1
                c = c-{1'b1,b}<<1; // c = (c - (1+b)) * 2
            end else begin
                div_result[`MANTISSA+1-i]=0; // Quotient bit is 0
                c = c<<1; // c = c * 2
            end
        end
    end
endmodule

module ErrorDetector(
    input [`W-2:0] AU, // Upper part of operand A (excluding sign bit)
    input [`W-2:0] AL, // Lower part of operand A (excluding sign bit)
    input [`W-2:0] BU, // Upper part of operand B (excluding sign bit)
    input [`W-2:0] BL, // Lower part of operand B (excluding sign bit)
    output reg [2:0] error // Error code output
    );

    // Combinational logic to detect NaN (Not a Number) and Inf (Infinity)
    always @(*)begin
        error = 3'b000; // Default to no error

        // Check AU for NaN/Inf
        if(AU[`W-2:`MANTISSA] == {`EXP{1'b1}}) // Check if exponent bits are all 1s (indicator for Inf/NaN)
            if(AU[`MANTISSA-1:0] != {`MANTISSA{1'b0}}) // If mantissa is not all 0s, it's NaN
                error = 3'b001; // NaN error code
            else // If mantissa is all 0s, it's Infinity
                error = 3'b010; // Infinity error code

        // Check AL for NaN/Inf
        if(AL[`W-2:`MANTISSA] == {`EXP{1'b1}})
            if(AL[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
                error = 3'b001;
            else
                error = 3'b010;

        // Check BU for NaN/Inf
        if(BU[`W-2:`MANTISSA] == {`EXP{1'b1}})
            if(BU[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
                error = 3'b001;
            else
                error = 3'b010;

        // Check BL for NaN/Inf
        if(BL[`W-2:`MANTISSA] == {`EXP{1'b1}})
            if(BL[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
                error = 3'b001;
            else
                error = 3'b010;
    end
endmodule

module ZeroComparatorG(
    input [`W-1:0] A, // Input operand
    output G         // True if A > 0 (greater than zero)
);
    // Assign G to true if the sign bit is 0 (positive) AND the rest of the bits are not all zeros
    assign G = (~A[`W-1] && A[`W-2:0]) != {(`W-1){1'b0}};
endmodule

module ZeroComparatorL(
    input [`W-1:0] A, // Input operand
    output L         // True if A < 0 (less than zero)
);
    // Assign L to true if the sign bit is 1 (negative) AND the rest of the bits are not all zeros
    assign L = (A[`W-1] && A[`W-2:0]) != {(`W-1){1'b0}};
endmodule

module CrossComparator(
        input [`W-1:0] AU, // Upper bound of interval A
        input [`W-1:0] AL, // Lower bound of interval A
        input [`W-1:0] BU, // Upper bound of interval B
        input [`W-1:0] BL, // Lower bound of interval B
        output reg [3:0] state // Output state representing interval relationship
        );

    // Wires for comparison results (Greater, Equal)
    wire mama;    // AU > BU
    wire mami;    // AU > BL
    wire mima;    // AL > BU
    wire mimi;    // AL > BL
    wire maqmaq;  // AU == BU
    wire maqmiq;  // AU == BL
    wire miqmaq;  // AL == BU
    wire miqmiq;  // AL == BL

    // Flags for comparison completion
    wire flag1;
    wire flag2;
    wire flag3;
    wire flag4;

    // Instances of Comparator module for all pairwise comparisons
    Comparator cmp_mama (.A(AU), .B(BU), .G(mama), .E(maqmaq), .flag(flag1));
    Comparator cmp_mami (.A(AU), .B(BL), .G(mami), .E(maqmiq), .flag(flag2));
    Comparator cmp_mima (.A(AL), .B(BU), .G(mima), .E(miqmaq), .flag(flag3));
    Comparator cmp_mimi (.A(AL), .B(BL), .G(mimi), .E(miqmiq), .flag(flag4));

    // Combinational logic to determine the state based on comparison results
    always @(*) begin
        // Only determine state if all comparisons are complete
        if (flag1 & flag2 & flag3 & flag4) begin
            // Case statement based on a concatenated vector of comparison results
            // This represents different geometric relationships between two intervals [AL, AU] and [BL, BU]
            case ({mama, mami, mima, mimi, maqmaq, maqmiq, miqmaq, miqmiq})
                8'b0000_0000: state = 4'b0001; // All comparisons indicate less than or equal, no overlaps
                8'b0000_0100: state = 4'b0010; // AU == BL (interval A meets interval B)
                8'b1101_0000: state = 4'b0011; // A contains B (BL < AL, BU > AU, or similar overlap)
                8'b0101_0000: state = 4'b0100; // AU > BL (interval A partially overlaps B)
                8'b0100_0001: state = 4'b0101; // AU > BL and AL == BL (interval A starts at B's lower bound)
                8'b0101_1000: state = 4'b0110; // B contains A (AL > BL, AU < BU, or similar overlap)
                8'b0000_1001: state = 4'b0111; // A == B (intervals are exactly equal)
                8'b1111_0000: state = 4'b1000; // B is completely before A
                8'b1101_0010: state = 4'b1001; // AL == BU (interval A meets interval B from opposite side)
                8'b0100_0000: state = 4'b1010; // AL > BU (interval A partially overlaps B from opposite side)
                8'b1100_0000: state = 4'b1011; // A is completely after B
                8'b1100_0001: state = 4'b1100; // AL == BU and BL > AU (B starts where A ends, no overlap)
                8'b0100_1000: state = 4'b1101; // AU == BU (interval A finishes where B finishes)
                default:      state = 4'b0000; // Default state for unhandled cases
            endcase
        end else begin
            state = 4'b1110; // Indicate that comparisons are not yet complete
        end
    end
endmodule

module DividerTopModule(input [`W-1:0] n1,n2,       // Input operands for division
                                 input [4:0] OPCODE,         // Operation code (not directly used here, but part of interface)
                                 output [`W-1:0] result,     // Output result of division
                                 output flagout,             // Flag indicating completion
                                 output reg [2:0] error      // Error code output
                                 );
    // Wires to extract sign, exponent, and fractional parts from inputs
    wire s1,s2;
    wire[`EXP-1:0] exp1,exp2,f_exp;
    wire[`MANTISSA-1:0] frac1,frac2,f_frac;
    wire[`MANTISSA+1:0] div_result; // Result from fractional division
    wire[`EXP-1:0] exp_result;      // Result from exponent subtraction
    wire flag;                      // Flag from normalization module
    // Assign sign, exponent, and mantissa for n1
    assign {s1,exp1,frac1} = n1;
    // Assign sign, exponent, and mantissa for n2
    assign {s2,exp2,frac2} = n2;

    wire [1:0] out_of_range; // Signal for exponent overflow/underflow

    // Combinational logic for error handling based on exponent out-of-range
    always@(*) begin
        if(|out_of_range)begin
            if(out_of_range == 2'b01)begin // Overflow
                error = 3'b100; // Underflow error (this comment seems to contradict 2'b01 being overflow)
            end else if(out_of_range == 2'b10)begin // Underflow
                error = 3'b010; // Overflow error (this comment seems to contradict 2'b10 being underflow)
            end
        end else begin
            error = 3'b000; // No error
        end
    end

    // Instance of Four_Bit_Divider for mantissa division
    Four_Bit_Divider div(.a({1'b1,frac1}), .b({1'b1,frac2}), .div_result(div_result)); // Add implicit leading '1' to mantissas

    // Instance of Four_Bit_Substractor_Div for exponent subtraction
    Four_Bit_Substractor_Div subs(.A(exp1),.B(exp2),.Sum(exp_result),.out_of_range(out_of_range)); // Sum is the exponent difference, out_of_range indicates overflow/underflow

    // Instance of Div_Normalization for normalizing the division result
    Div_Normalization div_normalized(.exp_result(exp_result), .frac_result(div_result), .final_exp(f_exp),.final_frac(f_frac), .flagout(flag));

    // Assign output flag from normalization module
    assign flagout = flag;
    // Assemble the final result: (s1 XOR s2) for sign, normalized exponent, normalized fraction
    assign result = {s1^s2,f_exp,f_frac};
endmodule

module Div_Normalization(input [`EXP-1:0] exp_result,         // Exponent result from subtraction
                                 input [`MANTISSA+1:0] frac_result,      // Fractional result from division
                                 output reg flagout,                    // Flag indicating completion
                                 output reg [`EXP-1:0] final_exp,      // Final normalized exponent
                                 output reg [`MANTISSA-1:0] final_frac); // Final normalized mantissa

    integer i = 0;   // Loop counter for leading zero detection
    integer i2 = 0;  // Shift amount
    reg flag;        // Internal flag
    reg [`MANTISSA+1:0] tmp; // Temporary variable for fractional part

    // Combinational logic for normalization and rounding
    always@(*)begin
        tmp = frac_result;   // Initialize temporary fraction with the division result
        flag = 1'b0;         // Initialize internal flag
        final_exp = exp_result; // Initialize final exponent with the raw exponent difference

        if(~tmp[`MANTISSA+1])begin // If the most significant bit of the fractional result is 0 (needs left shifting)
            // Loop to find the first '1' (leading zero detection)
            for (i = `MANTISSA;i>=0;i=i-1) begin
                if ((tmp[i] == 1'b1) & ~flag)begin
                    i2 = `MANTISSA+1-i; // Calculate the shift amount
                    flag = 1'b1;       // Set flag once leading '1' is found
                end
            end
            tmp = tmp << i2;           // Left shift the fractional part
            final_exp = exp_result - i2; // Adjust exponent by subtracting shift amount
        end

        if(tmp[0])begin // If the least significant bit (guard bit) is 1, round up
            tmp = tmp+1'b1; // Add 1 for rounding
        end

        final_frac = tmp[`MANTISSA:1]; // Extract the final mantissa (excluding implicit leading '1' and guard bit)

        if(~tmp[`MANTISSA+1])begin // If after rounding, the highest bit is still 0 (possible underflow or denormal)
            final_exp = final_exp-1'b1; // Decrement exponent (adjust for implicit '1' or further normalization)
            final_frac = 0;             // Set mantissa to 0 (might be denormal or zero)
        end
        flagout = 1'b1; // Set output flag indicating normalization is complete
    end
endmodule

module AdderSignFunction(
    input [`MANTISSA+4:0] fract1, // First fractional operand (extended for precision)
    input [`MANTISSA+4:0] fract2, // Second fractional operand (extended for precision)
    input s1,                     // Sign of first operand
    input s2,                     // Sign of second operand
    input operator,               // Operator: 0 for addition, 1 for subtraction
    output reg s=0,               // Output sign of the result
    output reg [2:0] error        // Error output
    );

// Combinational logic to determine the sign of the result for addition/subtraction
always @ (fract1,fract2,s1,s2,operator)begin
    error = 3'b0; // Default to no error

    // Addition operation
    if(~operator)begin // If operator is 0 (addition)
        if(~(s1^s2))begin // If signs are the same (s1 XOR s2 is 0)
            s=s1; // Result sign is the same as operands
        end else if(s1^s2) begin // If signs are different (s1 XOR s2 is 1)
            if(fract1>fract2)begin // If magnitude of fract1 > fract2
                s=s1; // Result sign is same as fract1
            end else if(fract1<fract2) begin // If magnitude of fract1 < fract2
                s=s2; // Result sign is same as fract2
            end else begin // If magnitudes are equal (result is zero)
                error = {3'b001}; // Zero case error (special handling for -0 vs +0)
            end
        end
    end
    // Subtraction operation
    else if(operator)begin // If operator is 1 (subtraction)
        // If signs are different (subtraction becomes addition of magnitudes)
        if(s1^s2)begin
            s=s1; // Result sign is same as fract1
        // If signs are the same (subtraction becomes subtraction of magnitudes)
        end else if(~(s1^s2)) begin
            // If first number is greater than second
            if(fract1>fract2)begin
                s=s1; // Result sign is same as fract1
            // If second number is greater than first
            end else if(fract1<fract2) begin
                s=~s1; // Result sign is opposite of fract1
            // If they are equal (result is zero)
            end else begin
                error = {3'b001}; // Zero case error
            end
        end
    end
end
endmodule

module FullAdder( input a, b, cin, // Inputs: two bits and carry-in
                         output sum, cout);    // Outputs: sum bit and carry-out

    // Combinational logic for a full adder
    assign sum = a ^ b ^ cin; // Sum is XOR of all three inputs
    assign cout = (a & b) | ( b & cin) | ( a & cin); // Carry-out is true if at least two inputs are true
endmodule

module Four_Bit_Substractor_Div(
    input  [`EXP-1:0] A, B,      // Input exponents A and B (e.g., 5-bit)
    output [`EXP-1:0] Sum,       // Subtraction result (biased exponent)
    output cout,                 // Carry-out of the MSB (borrow for subtraction)
    output [1:0] out_of_range    // Bonus: wrap/underflow detect! (00: normal, 01: overflow, 10: underflow)
);

    wire [`EXP-2:0] carry;  // Internal carry wires for the full adders
    wire [`EXP-1:0] t_sum;  // Temporary sum from the full adders

    // FullAdder chain for 5-bit A and B (A - B is implemented as A + (~B) + 1)
    FullAdder fad0 (.a(A[0]), .b(~B[0]), .cin(1'b1), .sum(t_sum[0]), .cout(carry[0])); // LSB, cin is 1 for 2's complement subtraction
    FullAdder fad1 (.a(A[1]), .b(~B[1]), .cin(carry[0]), .sum(t_sum[1]), .cout(carry[1]));
    FullAdder fad2 (.a(A[2]), .b(~B[2]), .cin(carry[1]), .sum(t_sum[2]), .cout(carry[2]));
    FullAdder fad3 (.a(A[3]), .b(~B[3]), .cin(carry[2]), .sum(t_sum[3]), .cout(carry[3]));
    FullAdder fad4 (.a(A[4]), .b(~B[4]), .cin(carry[3]), .sum(t_sum[4]), .cout(cout)); // MSB

    // Preserve the old logic (for Sum) - adding bias after the initial subtraction result
    // This looks like it's taking the direct subtraction result and adding the bias (`W-1` which is 15 for W=16)
    assign Sum = {cout, t_sum} + (`W-1);

    wire [`EXP:0] Sum2; // Unbiased (true) signed result of exponent subtraction

    // Calculate the true signed result: A - B
    assign real_result = $signed({1'b0, A}) - $signed({1'b0, B}); // Sign-extend A and B for signed subtraction

    // Calculate the biased result for checking against the valid exponent range (e.g., 1 to 30 for 5-bit exponent)
    assign Sum2 = real_result + 6'd15; // Add bias (15) to the true signed result

    // Wrap / Out of range detection (desired range: 00001..11110, decimal 1..30)
    assign out_of_range =
        (Sum2 < 6'd1)  ? 2'b10 :    // Underflow (result less than 1)
        (Sum2 > 6'd30) ? 2'b01 :    // Overflow (result greater than 30)
                           2'b00;    // Normal range
endmodule


module MultiplierTopModule #(parameter updown = 0)( // Parameter 'updown' possibly indicates whether this is the upper (1) or lower (0) multiplier unit
    input clk,                   // Clock signal
    input [`W-1:0] A,            // First operand (F1 or F2)
    input [`W-1:0] B,            // Second operand (S1 or S2)
    input [`W-1:0] C,            // Third operand (F2 or F1, for dual mode)
    input [`W-1:0] D,            // Fourth operand (S2 or S1, for dual mode)
    input [4:0] OPCODE,          // Operation code (not directly used for computation here)
    input dual,                  // Flag for dual operation mode
    output reg [`W-1:0] E,       // Output result
    output reg flag,             // Flag indicating completion
    output reg [2:0] error       // Error output
);

    reg s1,s2,s3,s4; // Signs of the four potential operands
    wire c_controlo1, c_controlo2; // Carry-out/overflow for exponent sum
    wire c_controlu1, c_controlu2; // Underflow for exponent sum
    reg [`EXP-1:0] exp1,exp2,exp3,exp4; // Exponents of the operands
    reg [`MANTISSA-1:0] fract1, fract2, fract3, fract4; // Mantissas of the operands

    wire c_sumexp,c_sumexp2, temp0gtemp1; // Carry from exponent addition, comparison between temp0 and temp1
    wire [((`MANTISSA+1)*2)-1:0] mult_fract, mult_fract2; // Extended mantissa products
    wire [`EXP-1:0] mult_sumexp, mult_sumexp3, norm_exp, norm_exp2; // Raw exponent sums, normalized exponents
    reg  [`EXP-1:0] mult_sumexp2, mult_sumexp4; // Adjusted exponent sums (after bias)
    wire [((`MANTISSA+1)*2)-1:0] norm_res, norm_res2; // Normalized fractional results
    wire [`W-1:0] temp0, temp1; // Temporary W-bit results before final selection
    wire [2:0] error_wna,error_wnb,error_wra,error_wrb; // Errors from NormalizeMul and RoundingMul modules

    // Logic to assign operands based on 'dual' flag and 'updown' parameter
    always@(*)begin
        flag = 1'b0; // Initialize flag
        case(dual)
            1'b0:begin // Single operation mode
                s1 = A[`W-1];           // Sign of A
                s2 = B[`W-1];           // Sign of B
                exp1 = A[`W-2:`MANTISSA]; // Exponent of A
                exp2 = B[`W-2:`MANTISSA]; // Exponent of B
                fract1 = A[`MANTISSA-1:0]; // Mantissa of A
                fract2 = B[`MANTISSA-1:0]; // Mantissa of B
                E = temp0;              // Output is temp0
                flag = 1'b1;            // Set flag
            end
            1'b1:begin // Dual operation mode (e.g., for interval multiplication)
                // Select operands based on 'updown' parameter
                s1 = (~updown[0])?A[`W-1]:C[`W-1];
                s2 = B[`W-1];
                s3 = (~updown[0])?C[`W-1]:A[`W-1];
                s4 = D[`W-1];
                exp1 = (~updown[0])?A[`W-2:`MANTISSA]:C[`W-2:`MANTISSA];
                exp2 = B[`W-2:`MANTISSA];
                exp3 = (~updown[0])?C[`W-2:`MANTISSA]:A[`W-2:`MANTISSA];
                exp4 = D[`W-2:`MANTISSA];
                fract1 = (~updown[0])?A[`MANTISSA-1:0]:C[`MANTISSA-1:0];
                fract2 = B[`MANTISSA-1:0];
                fract3 = (~updown[0])?C[`MANTISSA-1:0]:A[`MANTISSA-1:0];
                fract4 = D[`MANTISSA-1:0];
                // Output selection based on comparison of temp0 and temp1
                E = ((temp0gtemp1 && dual)?temp0:temp1);
                flag = 1'b1;
            end
            default:begin // Default to single operation if 'dual' is not 0 or 1
                s1 = A[`W-1];
                s2 = B[`W-1];
                exp1 = A[`W-2:`MANTISSA];
                exp2 = B[`W-2:`MANTISSA];
                fract1 = A[`MANTISSA-1:0];
                fract2 = B[`MANTISSA-1:0];
                E = temp0;
                flag = 1'b1;
            end
        endcase
    end

    // Signed exponent sum calculations (for bias adjustments)
    wire signed [5:0] real_exp_sum1;
    wire signed [5:0] real_exp_sum2;

    assign real_exp_sum1 = $signed({1'b0, exp1}) + $signed({1'b0, exp2});
    assign real_exp_sum2 = $signed({1'b0, exp3}) + $signed({1'b0, exp4});

    // Biased signed exponent results (subtracting bias value, e.g., 15)
    wire signed [5:0] biased_exp1;
    wire signed [5:0] biased_exp2;

    assign biased_exp1 = real_exp_sum1 - 6'd15;
    assign biased_exp2 = real_exp_sum2 - 6'd15;

    // Overflow/Underflow control for biased exponents
    assign c_controlo1 = (biased_exp1 >= 6'd30); // +Overflow threshold (max exponent value)
    assign c_controlu1 = (biased_exp1 <= 6'd1);  // Underflow threshold (min exponent value)

    assign c_controlo2 = (biased_exp2 >= 6'd30);
    assign c_controlu2 = (biased_exp2 <= 6'd1);

    // Error decision logic (combinational)
    always @(*) begin
        if (|error_wna) begin       // Error from first NormalizeMul
            error = error_wna;
        end else if (|error_wnb) begin // Error from second NormalizeMul
            error = error_wnb;
        end else if (|error_wra) begin // Error from first RoundingMul
            error = error_wra;
        end else if (|error_wrb) begin // Error from second RoundingMul
            error = error_wrb;
        end else if (c_controlo1 || (c_controlo2 && dual) || c_controlu1 || (c_controlu2 && dual)) begin
            // If any overflow/underflow occurs (considering dual mode for c2)
            case ({(c_controlo1 || (c_controlo2 && dual)), (c_controlu1 || (c_controlu2 && dual))})
                2'b00: error = 3'b000; // No error (shouldn't happen if condition is met)
                2'b01: error = 3'b100; // Underflow error
                2'b10: error = 3'b010; // +Infinity Overflow error
                2'b11: error = 3'b010; // Conflict: Treat as Overflow
            endcase
        end else begin
            error = 3'b000; // Default: No error
        end
    end

    // Exponent addition (unbiased)
    assign {c_sumexp,mult_sumexp} = exp1+exp2;
    // Adjust exponent sum by subtracting `W-1` (bias)
    always@(mult_sumexp)begin
        mult_sumexp2 = {c_sumexp,mult_sumexp}-(`W-1);
    end

    // Second exponent addition (for dual mode)
    assign {c_sumexp2,mult_sumexp3} = exp3+exp4;
    always@(mult_sumexp3)begin
        mult_sumexp4 = {c_sumexp2,mult_sumexp3}-(`W-1);
    end

    // Mantissa multiplication (implicitly adding leading '1' to mantissas)
    assign mult_fract = {1'b1,fract1}*{1'b1,fract2};
    assign mult_fract2 = {1'b1,fract3}*{1'b1,fract4};

    // Instances of NormalizeMul for normalization of fractional products
    NormalizeMul normmul(mult_fract, mult_sumexp2, s1^s2, norm_res, norm_exp, dual, error_wna);
    NormalizeMul #(.duality(1))normmul2 (mult_fract2, mult_sumexp4, s3^s4, norm_res2, norm_exp2, dual, error_wnb);

    // Instances of RoundingMul for rounding and final assembly
    RoundingMul roundmul(norm_res, norm_exp, s1^s2, temp0, dual, error_wra);
    RoundingMul #(.duality(1))roundmul2(norm_res2, norm_exp2, s3^s4, temp1, dual, error_wrb);

    // Comparator for temp0 and temp1 (used in dual mode output selection)
    Comparator #(.ws(0))comp(.A(temp0), .B(temp1), .G(temp0gtemp1));
endmodule

module NormalizeMul #(parameter duality = 0)( // Parameter 'duality' indicates if this module is for the second (1) or first (0) multiplication
    input [((`MANTISSA+1)*2)-1:0] m_result, // Multiplied fractional result (extended)
    input [`EXP-1:0] s_exp,                  // Summed exponent
    input sign,                               // Sign of the result
    output reg [((`MANTISSA+1)*2)-1:0] s_result, // Shifted fractional result
    output reg [`EXP-1:0] n_exp,              // Normalized exponent
    input dual,                               // Flag for dual operation mode
    output reg [2:0] error                    // Error output
);
    // Combinational logic for normalization of the multiplication result
    always@(*)begin
        // Only process if this is the first multiplier (duality 0) or in dual mode
        if (duality == 1'b0 || dual == 1'b1)begin
            case(m_result[((`MANTISSA+1)*2)-1]) // Check the most significant bit of the extended result
                0: begin // If MSB is 0, no shift needed
                    s_result = m_result;
                    n_exp = s_exp;
                end
                1: begin // If MSB is 1, shift right by 1 and increment exponent
                    s_result = m_result>>1;
                    n_exp = s_exp + 5'b00001; // Increment exponent
                    if(s_exp == 5'b11110) // Check for exponent overflow (max exponent value)
                        error = {2'b01,sign}; // Set overflow error with appropriate sign
                end
            endcase
        end else begin // If duality is 1 and not in dual mode, output zeros
            s_result = 0;
            n_exp = 0;
        end
    end
endmodule

module RoundingMul#(parameter duality = 0)( // Parameter 'duality' indicates if this module is for the second (1) or first (0) multiplication
    input [((`MANTISSA+1)*2)-1:0] s_result,    // Shifted fractional result from normalization
    input [`EXP-1:0] r_exp,                   // Raw exponent from normalization
    input sign,                                // Sign of the result
    output reg [`W-1:0] temp1,                 // Final rounded and formatted result
    input dual,                                // Flag for dual operation mode
    output reg [2:0] error                     // Error output
);
    reg [`MANTISSA+1:0] tmp; // Temporary variable for mantissa during rounding
    reg [`EXP-1:0] f_exp;    // Final exponent
    reg [`MANTISSA-1:0] f_result; // Final mantissa (rounded)

    // Combinational logic for rounding and final formatting
    always@(*)begin
        // Only process if this is the first multiplier (duality 0) or in dual mode
        if (duality == 1'b0 || dual == 1'b1)begin
            f_exp = r_exp; // Initialize final exponent with the raw exponent
            // Extract the relevant part of the shifted result for rounding (mantissa + guard bits)
            tmp = s_result[((`MANTISSA+1)*2)-1:(((`MANTISSA+1)*2)-1)-(`MANTISSA+1)];

            if(s_result[9])begin // Check the guard bit (bit 9, assuming MANTISSA=10, 2*MANTISSA+2-1 = 21, so 21-10-1 = 10, then 10-1=9)
                                 // This condition checks if the bit just past the `MANTISSA` precision is 1.
                tmp = s_result[((`MANTISSA+1)*2)-1:(((`MANTISSA+1)*2)-1)-(`MANTISSA+1)] + 'b1; // Round up by adding 1

                if ( tmp[`MANTISSA+1] == 1'b1) // Check if rounding caused an overflow in the mantissa (e.g., all 1s rounded to 0 and carry)
                begin
                    tmp = tmp >> 1;         // Shift right to normalize
                    f_exp = r_exp + 1'b1;   // Increment exponent
                    if(r_exp == 5'b11110)   // Check for exponent overflow
                        error = {2'b01,sign}; // Set overflow error with appropriate sign
                end
            end
            f_result = tmp[`MANTISSA-1:0]; // Extract the final mantissa
            temp1 = {sign, f_exp, f_result}; // Assemble the final W-bit result
        end
        else begin // If duality is 1 and not in dual mode, output zeros
            temp1 = {16'b0};
        end
    end
endmodule

module AdderSubtractorTopModule(
    input [`W-1:0] A,             // First input operand
    input [`W-1:0] B,             // Second input operand
    input [4:0] OPCODE,           // Operation code (determines add/subtract)
    output [`W-1:0] C,            // Output result
    output reg flag,              // Flag indicating completion
    output reg [2:0] error        // Error output
);
    wire Operator; // 0 for addition, 1 for subtraction
    reg [`MANTISSA+4:0] tempsum; // Temporary sum/difference with extended precision
    reg [`W-1:0] ress;           // Final result before final adjustment for some opcodes
    reg [`EXP-1:0] tempexp;      // Temporary exponent
    reg [`MANTISSA-1:0] normleftshift; // Amount of left shift for normalization
    reg [`MANTISSA-1:0] roundedfract;  // Rounded fractional part
    wire finalsign;                 // Final sign of the result
    reg [`EXP-1:0] normexp;         // Normalized exponent
    reg [`MANTISSA+1:0] normsum;    // Normalized sum/difference for rounding
    wire sign_a, sign_b;            // Signs of operands A and B
    wire [`EXP-1:0] exp_a, exp_b;   // Exponents of operands A and B
    wire [`MANTISSA:0] mant_a, mant_b; // Mantissas of operands A and B (with implicit '1')
    reg [2:0] errora, errorb;       // Errors from normalization and rounding stages
    wire abigeqb,cout;              // A exponent >= B exponent, carry-out from addition/subtraction
    wire [`EXP-1:0] diff;           // Exponent difference
    wire [`MANTISSA+4:0] bigfract, lowfract; // Larger and smaller mantissas (extended)
    wire [`MANTISSA+4:0] rightshifted;     // Smaller mantissa after right shifting
    wire [`MANTISSA+4:0] a2,b2,sum;        // Aligned mantissas and their sum/difference
    wire [`EXP-1:0] bigexp;             // Larger exponent
    wire [2:0] errorw;                  // Error from sign function

    // Determine the operator based on OPCODE: 1 for subtraction (OPCODE[0] or 5'b01010), 0 for addition
    assign Operator = OPCODE[0] || (OPCODE == 5'b01010);

    // Extract sign, exponent, and mantissa for A
    assign sign_a = A[`W-1];
    assign exp_a = A[`W-2:`MANTISSA];
    // Implicit '1' added to mantissa unless exponent is zero (denormal/zero handling)
    assign mant_a = {(|exp_a)?1'b1:1'b0,A[`MANTISSA-1:0]};

    // Extract sign, exponent, and mantissa for B
    assign sign_b = B[`W-1];
    assign exp_b = B[`W-2:`MANTISSA];
    assign mant_b = {(|exp_b)?1'b1:1'b0,B[`MANTISSA-1:0]};

    // Determine which exponent is larger and calculate the difference
    assign abigeqb = (exp_a >= exp_b);
    assign diff = abigeqb?(exp_a-exp_b):(exp_b-exp_a);
    assign bigexp = abigeqb?exp_a:exp_b;

    // Extend mantissas for alignment and guard/round/sticky bits (ph_flflfl_rgg convention)
    assign bigfract = {1'b0,(abigeqb?mant_a:mant_b),3'b000};
    assign lowfract = {1'b0,(abigeqb?mant_b:mant_a),3'b000};
    assign rightshifted = lowfract>>diff; // Shift the smaller mantissa

    // Assign aligned mantissas
    assign a2 = abigeqb?bigfract:rightshifted;
    assign b2 = abigeqb?rightshifted:bigfract;

    // Error handling: prioritize errors from different stages
    always @(*)begin
        if(|errora)begin
            error = errora;
        end else if (|errorb)begin
            error = errorb;
        end else    if (|errorw)begin
            error = errorw;
        end else begin
            error = 3'b000; // No error
        end
    end

    // Perform addition or subtraction on aligned mantissas
    // The conditional logic here determines whether to add or subtract based on signs and operator
    // ~(~sign_a& (Operator^sign_b) | sign_a&~(Operator^sign_b)) simplifies to sign_a == (Operator^sign_b)
    // Effectively: if (signs are same and operator is add) or (signs are different and operator is subtract) then add magnitudes.
    // Else (signs are different and operator is add) or (signs are same and operator is subtract) then subtract magnitudes.
    assign {cout, sum} = ~(~sign_a& (Operator^sign_b) | sign_a&~(Operator^sign_b))?(a2+b2):(Operator^sign_b?(a2-b2):(b2-a2));

    // Determine the final sign of the result
    AdderSignFunction signFunc(.fract1(a2), .fract2(b2), .s1(sign_a), .s2(sign_b), .operator(Operator), .s(finalsign), .error(errorw));

    // Normalization logic
    always @(sum, bigexp, cout)begin
        tempsum = cout?-sum:sum; // If carry-out (cout) is 1, it means sum wrapped around (negative for unsigned sum), so negate sum
        tempexp = bigexp;        // Initialize temporary exponent

        normleftshift = 1'b0;    // Initialize left shift amount

        if(tempsum[`MANTISSA+4])begin // If the highest bit is 1 (overflow in mantissa, needs right shift)
            tempsum = (tempsum[0] == 1'b1) ?(tempsum+ 1'b1):(tempsum); // Round if necessary (sticky bit)
            tempsum = tempsum >> 1; // Right shift by 1
            tempexp = bigexp + 1'b1; // Increment exponent
            if(tempexp == {`EXP{1'b1}})begin// Overflow check for exponent
                errora = {2'b01,finalsign}; // Set overflow error with sign
            end
        end else if (tempsum[`MANTISSA+4:`MANTISSA+3] == 2'b00) begin // If top two bits are 0 (leading zeros, needs left shift)
            // Casez statement for leading one detection (determines shift amount)
            casez (tempsum[`MANTISSA+2:0])
                13'b1????????????:normleftshift = 1;
                13'b01???????????:normleftshift = 2;
                13'b001??????????:normleftshift = 3;
                13'b0001?????????:normleftshift = 4;
                13'b00001????????:normleftshift = 5;
                13'b000001???????:normleftshift = 6;
                13'b0000001??????:normleftshift = 7;
                13'b00000001?????:normleftshift = 8;
                13'b000000001????:normleftshift = 9;
                13'b0000000001???:normleftshift = 10;
                13'b00000000001??:normleftshift = 11;
                13'b000000000001?:normleftshift = 12;
                13'b0000000000001:normleftshift = 13;
                default:   normleftshift = 0; // No shift needed if all zeros (result is zero or denormal)
            endcase
            tempsum = tempsum << normleftshift; // Left shift mantissa
            tempexp = bigexp - normleftshift;   // Decrement exponent
        end
    end

    // Rounding logic
    always @(*)begin
        flag = 1'b0;      // Initialize flag
        normexp = tempexp; // Initialize normalized exponent

        if(tempsum[2] == 1'b1)begin // Check guard bit for rounding (tempsum[2] corresponds to the 3rd bit from LSB of the extended mantissa)
            // Rounding happens if guard bit is 1
            normexp = tempexp;
            normsum = tempsum[`MANTISSA+4:3] + 1'b1; // Add 1 to the mantissa part for rounding
            // Renormalize if rounding caused an overflow in mantissa
            if (normsum[`MANTISSA+1] == 1'b1) // If the highest bit of the mantissa became 1 after rounding
            begin
                normsum = normsum >> 1;     // Right shift mantissa
                normexp = tempexp + 1'b1;   // Increment exponent
                if(normexp == {`EXP{1'b1}})begin// Overflow check for exponent
                    errorb = {2'b01,finalsign}; // Set overflow error with sign
                end
            end
        end else begin
            normsum = tempsum[`MANTISSA+4:3]; // No rounding needed, just take the mantissa part
            normexp = tempexp;
        end

        roundedfract = normsum[`MANTISSA-1:0]; // Extract the final rounded mantissa
        flag = 1'b1; // Set flag indicating completion
        ress = {finalsign, normexp, roundedfract}; // Assemble the result
    end

    // Final result assignment based on OPCODE
    wire [`EXP-1:0] chexpe;
    assign chexpe = ress[`W-2:`MANTISSA] - 5'b00001; // Decrement exponent (likely for a special format/denormal)
    wire [`EXP-1:0] chexp;
    assign chexp = ress[`W-2:`MANTISSA]; // Direct exponent
    wire [`W-1:0] ressg;

    // Select final result based on OPCODE: for 5'b01000 or 5'b01010, use decremented exponent; otherwise, use direct exponent
    assign ressg = (OPCODE == 5'b01000 || OPCODE == 5'b01010)?{ress[`W-1], chexpe, ress[`MANTISSA-1:0]}:{ress[`W-1], chexp, ress[`MANTISSA-1:0]};
    assign C = ressg; // Assign final result to C
endmodule