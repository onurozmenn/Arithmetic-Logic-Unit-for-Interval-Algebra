`timescale 1ns / 1ps
module VerilogTopModule(
		input  wire clk,
		input  wire rst,
		input  wire [31:0]  a,
		input  wire [31:0]  b,
		input  wire [ 4:0]  funct,
		input  wire [ 1:0]  fmt,
		input  wire [ 2:0]  rm, 
		output [ 3:0]  stateCross,
		output [31:0]  result,
		output flag1, flag2, dual
   );
	wire [3:0] condition;
	wire [7:0] ANSU,ANSL;
	wire [7:0] F1,F2,S1,S2;
	assign result = {16'b0, ANSL, ANSU};
	
	ProcessRedirectorModule islem(
		.AL(a[15:8]),
		.AU(a[ 7:0]),
		.BL(b[15:8]),
		.BU(b[ 7:0]), 
		.F1(F1), 
		.F2(F2), 
		.S1(S1), 
		.S2(S2),
		.stateCross(stateCross),
		.condition(condition), 
		.OPCODE(funct), 
		.dual(dual)
	);
	
	AdderSubtractorTopModule adderdown(F1, S1, funct, ANSL, flag1);
	AdderSubtractorTopModule adderup  (F2, S2, funct, ANSU, flag2);							 				
	MultiplierTopModule #(.updown(0)) multdown (clk, F1, S1, F2, S2, funct, dual, ANSL, flag1); 
	MultiplierTopModule #(.updown(1)) multup   (clk, F2, S2, F1, S1, funct, dual, ANSU, flag2); 
	DividerTopModule divdown(F1, S1, funct, ANSL, flag1);
	DividerTopModule divup(F2, S2, funct, ANSU, flag2);
endmodule		