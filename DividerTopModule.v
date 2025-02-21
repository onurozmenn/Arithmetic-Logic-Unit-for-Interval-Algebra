`timescale 1ns / 1ps

module DividerTopModule(input [7:0] n1,n2,
					input [4:0] OPCODE,
					output [7:0] result,
					output reg flagout);
	 wire s1,s2;
	 wire[3:0] exp1,exp2,f_exp;
	 wire[2:0] frac1,frac2,f_frac;
	 wire[4:0] div_result;
	 wire[3:0] exp_result;
	 wire flagin = 1'b0;
	 wire flag;
	 assign {s1,exp1,frac1} = n1;
	 assign {s2,exp2,frac2} = n2;
	 
	 Four_Bit_Divider div(.a({1'b1,frac1}), .b({1'b1,frac2}), .div_result(div_result));
	 Four_Bit_Substractor_Div subs(.A(exp1),.B(exp2),.Sum(exp_result));
	 Div_Normalization div_normalized(.exp_result(exp_result), .frac_result(div_result),.flagin(flagin), .final_exp(f_exp),.final_frac(f_frac), .flagout(flag));
	 always @(*)begin
		flagout = (OPCODE==5'b0011)?flag:1'bz;
	 
	 end
	 assign result = (OPCODE==5'b00011)?{s1^s2,f_exp,f_frac}:8'bz;
	 
endmodule