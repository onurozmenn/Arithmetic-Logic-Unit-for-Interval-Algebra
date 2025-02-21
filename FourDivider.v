`timescale 1ns / 1ps

module Four_Bit_Divider(input [3:0] a,
								input [3:0] b,
								output reg [4:0] div_result);
	integer i = 0;
	reg [4:0] n;
	reg [4:0] c;

	always @(*)begin
		n=0;
		c=0;
		div_result[4] = (a >= b)? 1 : 0;
		c = (a >= b)? (a-b)<<1 : a<<1;
		for(i = 1; i<5; i=i+1)begin
			n = c-{1'b1,b};
			if(n[4])begin
				div_result[4-i] = 1;
				c = c-{1'b1,b}<<1;
			end else begin
				div_result[4-i]=0;
				c = c<<1;
			end
		end
	end
endmodule