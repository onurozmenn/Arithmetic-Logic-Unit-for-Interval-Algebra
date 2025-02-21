`timescale 1ns / 1ps

module Div_Normalization(input [3:0] exp_result,
								 input [4:0] frac_result,
								 input flagin,
								 output reg flagout,
								 output reg [3:0] final_exp,
								 output reg [2:0] final_frac);
	 
	integer i = 0;
	integer i2 = 0;
	reg flag;
	reg [4:0] tmp;
	always@(*)begin
		tmp = frac_result;
		flag = 1'b0;
		final_exp = exp_result;
		if(~tmp[4])begin
			for (i = 3;i>=0;i=i-1) begin
				if ((tmp[i] == 1'b1) & ~flag)begin
					i2 = 4-i;
					flag = 1'b1;
				end
			end	
			tmp = tmp << i2;
			final_exp = exp_result - i2;
		end 
		
		if(tmp[0])begin
			tmp = tmp+1;
		end
		
		final_frac = tmp[3:1];
		if(~tmp[4])begin
			final_exp = final_exp-1;		
			final_frac = 0;
		end	
		flagout = flagin? 0:1;
	end
endmodule