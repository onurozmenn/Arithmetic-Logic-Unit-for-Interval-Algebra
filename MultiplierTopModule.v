`timescale 1ns / 1ps

module MultiplierTopModule #(parameter updown = 0)(input clk,
		input [7:0] A,
		input [7:0] B,
		input [7:0] C,
		input [7:0] D,
		input [4:0] OPCODE,
		input dual,
		output reg [7:0] E,
		output reg flag);
		
		reg s1,s2;
		reg [3:0] exp1,exp2;
		reg [2:0] fract1, fract2;
		
		
		reg [1:0] state = 2'b00;
		wire [1:0] normstate, roundstate;
		wire c_sumexp, temp1gtemp2;
		wire [7:0] mult_fract;
		wire [3:0] mult_sumexp, norm_exp, f_exp;
		reg  [3:0] mult_sumexp2;
		wire [7:0] norm_res; 
		wire [2:0] f_res;
		wire [7:0] temp0, temp1, temp2;
		reg ch = 0;
		reg [31:0] tABCD=0;

		always@(*)begin
			
			flag <= (OPCODE==5'b00010)?1'b0:1'bz;

			case({dual,state})
				3'b100:begin
						flag <= (OPCODE==5'b00010)?1'b0:1'bz;
						E <= 0;
						s1 <= (~updown[0])?A[7]:C[7];
						s2 <= B[7];
						exp1 <= (~updown[0])?A[6:3]:C[6:3];
						exp2 <= B[6:3];
						fract1 <= (~updown[0])?A[2:0]:C[2:0];
						fract2 <= B[2:0];
				end
				3'b101:begin
						s1 <= (~updown[0])?C[7]:A[7];
						s2 <= D[7];
						exp1 <= (~updown[0])?C[6:3]:A[6:3];
						exp2 <= D[6:3];
						fract1 <= (~updown[0])?C[2:0]:A[2:0];
						fract2 <= D[2:0];
				end
				3'b110:begin
					flag <= (OPCODE==5'b00010)?1'b1:1'bz;
					E <= (OPCODE==5'b00010)?(temp1gtemp2?temp1:temp2):8'bzzzzzzzz;
				end
				default:begin
					s1 <= A[7];
					s2 <= B[7];
					exp1 <= A[6:3];
					exp2 <= B[6:3];
					fract1 <= A[2:0];
					fract2 <= B[2:0];
					E <= (OPCODE==5'b00010)?(temp0):8'bzzzzzzzz;
					flag <= (OPCODE==5'b00010)?1'b1:1'bz;
				end
			endcase
		end	
		always @(posedge clk)begin
			if(tABCD != {A,B,C,D})begin
				ch = 1'b1;
				state <= 2'b00;
				tABCD <= {A,B,C,D};
			end else begin
				ch = 1'b0;
				state <= roundstate; 
			end
		end
		
		assign {c_sumexp,mult_sumexp} = exp1+exp2;
		
		always@(mult_sumexp)begin
			 /*if({c_sumexp,mult_sumexp} <= 5'b00111)begin
				$display("Underflow error A:%b B:%b",A,B);
			 end else if({c_sumexp,mult_sumexp} >= 5'b10110)begin
				$display("Overflow error A:%b B:%b",A,B);
			 end*/
			 mult_sumexp2 = {c_sumexp,mult_sumexp}-5'b00111;
		end
		
		assign mult_fract = {1'b1,fract1}*{1'b1,fract2};
		NormalizeMul normmul(mult_fract, mult_sumexp2, s1^s2, norm_res, norm_exp, dual, state, normstate, ch);
		RoundingMul roundmul(norm_res, norm_exp, s1^s2, temp0, temp1, temp2, dual, normstate, roundstate, ch);
		Comparator comp(.A({1'b0,temp1[6:0]}), .B({1'b0,temp2[6:0]}), .G(temp1gtemp2));
endmodule

module NormalizeMul(
		input [7:0] m_result,
		input [3:0] s_exp,
		input sign,
		output reg [7:0] s_result,
		output reg [3:0] n_exp,
		input dual,
		input [1:0] state,
		output reg [1:0] normstate, input ch
	);
	reg [2:0] error;
	always@(*)begin
		case(m_result[7])
			0: begin
					s_result = m_result;
					n_exp = s_exp;
				end
			1: begin
					s_result = m_result>>1;
					n_exp = s_exp + 4'b0001;
					if(s_exp == 4'b1110)
						error = {2'b01,sign};
						$display("Overflow error normalize");
				end
		endcase
		if(dual)begin
			case (state)
				2'b00:normstate <= 2'b01;
				2'b01:normstate <= 2'b10;
				2'b10:normstate <= ch?(2'b00):(normstate);
				2'b11:normstate <= 2'b00;
			endcase
		end else begin
			normstate <= 2'b00; 
		end
	end
endmodule

module RoundingMul(
		input [7:0] s_result,		
		input [3:0] r_exp,		
		input sign,
		output reg [7:0] temp0,
		output reg [7:0] temp1,
		output reg [7:0] temp2,
		input dual,
		input [1:0] normstate,
		output reg [1:0] roundstate,
		input ch
	);
	reg [4:0] tmp;
	reg [2:0] error;
	reg [3:0] f_exp;
	reg [2:0] f_result;

	always@(*)begin
		f_exp = r_exp;
		tmp = s_result[7:3];
		if(s_result[2])begin
			tmp = s_result[7:3] + 1'b1;
			//Renormalize
			if ( tmp[4] == 1'b1)
			begin
				tmp =  tmp >> 1;
				f_exp = r_exp + 1'b1;
				if(r_exp == 4'b1110)
					error = {2'b01,sign};
					$display("Overflow error rounding");
			end
		end
		f_result = tmp[2:0];
		if(dual)begin
			roundstate <= normstate; 
		end else begin
			roundstate <= 2'b00; 
		end
		
		case({dual,roundstate})
			3'b100: begin
							temp1 = {sign, f_exp, f_result};
							
					  end
			3'b101: begin
							temp2 = {sign, f_exp, f_result};
							temp0 = 0;
					  end
			3'b110: begin
							temp0 = 0;
					  end
			default:begin
							temp0 = {sign, f_exp, f_result};
							temp2 = 0;
							temp1 = 0;
					  end
		endcase
	end

endmodule
