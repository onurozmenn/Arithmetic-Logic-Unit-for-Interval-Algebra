`timescale 1ns / 1ps

module ZeroComparatorG(
    input [7:0] A,
    output G
);
	 assign G = (~A[7] && A[6:0]) != 7'b0;
endmodule

module ZeroComparatorL(
    input [7:0] A,
    output L
);
	 assign L = (A[7] && A[6:0]) != 7'b0;
endmodule
