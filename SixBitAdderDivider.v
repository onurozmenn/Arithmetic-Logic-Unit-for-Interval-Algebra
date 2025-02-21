`timescale 1ns / 1ps


module FullAdder( input a, b, cin, 
						output sum, cout);
		
		assign sum = a ^ b ^ cin;
		assign cout = (a & b) | ( b & cin) | ( a & cin);
endmodule

module Four_Bit_Substractor_Div(input [3:0] A,B,
										  output [3:0] Sum, 
										  output cout);
		wire [2:0] carry;
		wire [3:0] t_sum;
		FullAdder fad0 (.a(A[0]), .b(~B[0]), .cin(1'b1), .sum(t_sum[0]), .cout(carry[0]));
		FullAdder fad1 (.a(A[1]), .b(~B[1]), .cin(carry[0]), .sum(t_sum[1]), .cout(carry[1]));
		FullAdder fad2 (.a(A[2]), .b(~B[2]), .cin(carry[1]), .sum(t_sum[2]), .cout(carry[2]));
		FullAdder fad3 (.a(A[3]), .b(~B[3]), .cin(carry[2]), .sum(t_sum[3]), .cout(cout));

	   assign Sum = {cout,t_sum} + 5'b00111;
endmodule

