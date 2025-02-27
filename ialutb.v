`timescale 1ns / 1ps

module ialutb;

	// Inputs
	reg clk;
	reg rst;
	reg [31:0] a;
	reg [31:0] b;
	reg [4:0] funct;
	reg [1:0] fmt;
	reg [2:0] rm;

	// Outputs
	wire [3:0] stateCross;
	wire [31:0] result;
	wire flag1;
	wire flag2;
	wire dual;

	// Instantiate the Unit Under Test (UUT)
	IALU uut (
		.clk(clk), 
		.rst(rst), 
		.a(a), 
		.b(b), 
		.funct(funct), 
		.fmt(fmt), 
		.rm(rm), 
		.stateCross(stateCross), 
		.result(result), 
		.flag1(flag1), 
		.flag2(flag2), 
		.dual(dual)
	);


	initial begin
		clk = 0;
		forever #5 clk = ~clk;
	end

	initial begin
	
		rst = 0;
		funct = 0;
		fmt = 0;
		rm = 0;
      
		a = 32'b0100010000000000_0100100000000000;
      b = 32'b0100000001000000_0100011110100000;

		#100;
		funct = 1;
		#100;
		funct = 2;
		#100;
		funct = 3;
		#100;
		// Add stimulus here
		$stop;
	end
      
endmodule

