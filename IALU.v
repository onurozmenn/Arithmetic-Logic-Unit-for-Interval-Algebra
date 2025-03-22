
`define EXP 5
`define MANTISSA 10
`define W 16 //INTERVAL LENGTH
`define TOTALW 32 //2*W TOTAL INTERVAL LENGTH

module IALU (
	input  clk,
	input  rst,
	input  [(`TOTALW)-1:0]  a,
	input  [(`TOTALW)-1:0]  b,
	input  [ 4:0]  funct,
	input  [ 1:0]  fmt,
	input  [ 2:0]  rm, 
	output [ 3:0]  stateCross,
	output reg [`TOTALW-1:0]  result,
	output reg flag
);
	wire [  3:0] condition;
	wire [`W-1:0] ANSU, ANSL;
	wire [`W-1:0] ANSLADD, ANSUADD;
	wire flagadd1, flagadd2, flagt1, flagt2;
	reg flagadd1_reg, flagadd2_reg, flagt1_reg, flagt2_reg;
	
	wire [`W-1:0] F1, F2, S1, S2;
	reg stateCrossRes = 1'b0;
	ProcessRedirectorModule islem(
		.AL(a[`TOTALW-1:`W]),
		.AU(a[ 	  `W-1:0]),
		.BL(b[`TOTALW-1:`W]),
		.BU(b[     `W-1:0]), 
		.F1(F1), 
		.F2(F2), 
		.S1(S1), 
		.S2(S2),
		.stateCross(stateCross),
		.condition(condition), 
		.OPCODE(funct), 
		.dual(dual)
	);
	AdderSubtractorTopModule adderdown(F1, S1, funct, ANSLADD, flagadd1);
	AdderSubtractorTopModule adderup  (F2, S2, funct, ANSUADD, flagadd2);							 				
	MultiplierTopModule #(.updown(0)) multdown (clk, F1, S1, F2, S2, funct, dual, ANSL, flagt1); 
	MultiplierTopModule #(.updown(1)) multup   (clk, F2, S2, F1, S1, funct, dual, ANSU, flagt2); 
	DividerTopModule divdown(F1, S1, funct, ANSL, flagt1);
	DividerTopModule divup(F2, S2, funct, ANSU, flagt2);
	// Register flags to handle asynchronous setting
	
	always @(posedge clk or posedge rst) begin
		if (rst) begin
			flagadd1_reg <= 1'b0;
			flagadd2_reg <= 1'b0;
			flagt1_reg <= 1'b0;
			flagt2_reg <= 1'b0;
			result <= 32'b0;
			flag <= 1'b0;
		end else begin
			// Register flags when they become 1
			if (flagadd1) flagadd1_reg <= 1'b1;
			if (flagadd2) flagadd2_reg <= 1'b1;
			if (flagt1) flagt1_reg <= 1'b1;
			if (flagt2) flagt2_reg <= 1'b1;
			
			// Handle add operations
			if (flagadd1_reg && flagadd2_reg) begin
				if (funct == 5'b00001 || funct == 5'b00000) begin
					result <= {ANSLADD, ANSUADD};
					flag <= 1'b1;
					// Reset flags after capturing result
					flagadd1_reg <= 1'b0;
					flagadd2_reg <= 1'b0;
				end
			end
			
			// Handle multiply/divide operations
			if (flagt1_reg && flagt2_reg) begin
				if (funct != 5'b00001 && funct != 5'b00000) begin
					result <= {ANSL, ANSU};
					flag <= 1'b1;
					// Reset flags after capturing result
					flagt1_reg <= 1'b0;
					flagt2_reg <= 1'b0;
				end
			end
			
			// Handle other operation results
			if (funct[4:3] == 2'b10) begin
				result <= stateCrossRes;
			end
			if (flag) begin
				flag <= 1'b0;
				result <= 32'bz;
			end
		end
	end
endmodule

module ProcessRedirectorModule( 
		input [`W-1:0] AU,
		input [`W-1:0] AL,
		input [`W-1:0] BU,
		input [`W-1:0] BL,
		input [4:0] OPCODE,
		output [3:0] stateCross,
		output reg [3:0] condition = 4'b1111,
		output reg [`W-1:0] F1, S1, F2, S2,
		output reg dual
		);
		/* output */ reg flag = 0;
		wire G_AU_0;
		wire G_BU_0;
		wire L_AL_0;
		wire L_BL_0;
		wire ready;
		wire [3:0] error;
		
		ZeroComparatorG cmp_AU_0(.A(AU), .G(G_AU_0));
		ZeroComparatorL cmp_AL_0(.A(AL), .L(L_AL_0));
		ZeroComparatorG cmp_BU_0(.A(BU), .G(G_BU_0));
		ZeroComparatorL cmp_BL_0(.A(BL), .L(L_BL_0));
		CrossComparator cross_comp(.AU(AU), .AL(AL), .BU(BU), .BL(BL), .state(stateCross));
		ErrorDetector errdet(.AU(AU[`W-2:0]), .AL(AL[`W-2:0]), .BU(BU[`W-2:0]), .BL(BL[`W-2:0]), .error(error), .ready(ready));
		
		always @(*) begin
			dual = 1'b0;
			condition = 4'b1111;
			flag = 0;
			F1 = `W'b0;
			S1 = `W'b0;
			F2 = `W'b0;
			S2 = `W'b0;
			if(ready)begin
				if(OPCODE[4:2] == 3'b000) begin
					if(OPCODE[1:0] == 2'b10 || OPCODE[1:0] == 2'b11) begin
						// Durum 1: AL >= 0 && BL >= 0 // 
						if (!L_AL_0 && !L_BL_0) begin
							condition = (OPCODE == 4'b0010) ? 4'b0011 : 4'b0110;
						end
						// Durum 2: AL >= 0 && BL < 0 < BU
						else if (!L_AL_0 && L_BL_0 && G_BU_0) begin
							condition = (OPCODE == 5'b00010) ? 4'b1011 : 4'b1111;
						end
						// Durum 3: AL >= 0 && BU <= 0
						else if (!L_AL_0 && !G_BU_0) begin
							condition = (OPCODE == 5'b00010) ? 4'b1001 : 4'b1100;
						end
						// Durum 4: AL < 0 < AU && BL >= 0
						else if (L_AL_0 && G_AU_0 && !L_BL_0) begin
							condition = (OPCODE == 5'b00010) ? 4'b0111 : 4'b0010;
						end
						// Durum 5: AL < 0 < AU && BU <= 0
						else if (L_AL_0 && G_AU_0 && !G_BU_0) begin
							condition = (OPCODE == 5'b00010) ? 4'b1000 : 4'b1101;
						end
						// Durum 6: AU <= 0 && BL >= 0
						else if (!G_AU_0 && !L_BL_0) begin
							condition = (OPCODE == 5'b00010) ? 4'b0110 : 4'b0011;
						end
						// Durum 7: AU <= 0 && BL < 0 < BU
						else if (!G_AU_0 && L_BL_0 && G_BU_0) begin
							condition = (OPCODE == 5'b00010) ? 4'b0100 : 4'b1111;
						end
						// Durum 8: AU <= 0 && BU <= 0
						else if (!G_AU_0 && !G_BU_0 ) begin
							condition = (OPCODE == 5'b00010) ? 4'b1100 : 4'b1001;
						end
						// Durum 9: AL < 0 < AU && BL < 0 < BU
						else if (L_AL_0 && G_AU_0 && L_BL_0 && G_BU_0) begin
							condition = (OPCODE == 5'b00010) ? 4'b1110 : 4'b1111;
							dual = (OPCODE == 5'b00010);
						end 
						// Durumsuz
						else begin
							condition = 4'b0000;
						end
						
					end else if (OPCODE[1:0] == 2'b01) begin //cikartma
						condition = (stateCross == 4'b0111) ?  4'b0011 : 4'b0110;
					end else begin //Toplama
						condition = 4'b0011;
					end
					
					F1 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[3] ? AU : AL) : AL;
					S1 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[2] ? BU : BL) : BU;
					F2 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[1] ? AU : AL) : AU;
					S2 = (condition != 4'b1110 & condition != 4'b1111) ? (condition[0] ? BU : BL) : BL;
					flag = 1;
				end  // !! GERI KALAN OPCODE LAR
		end 
	end
endmodule

module Comparator
		#(parameter ws = 1)(
		input [`W-1:0] A,
		input [`W-1:0] B,
		output reg G, // a > b ise 1
		output reg E,   // a == b ise 1
		output reg flag
		);
		
		wire A_S = A[`W-1];
		wire [`EXP-1:0] A_EXP = A[`W-2:`W-1-`EXP];
		wire [`MANTISSA-1:0] A_FRACT = A[`MANTISSA-1:0];
		
		wire B_S = B[`W-1];
		wire [`EXP-1:0] B_EXP = B[`W-2:`W-1-`EXP];
		wire [`MANTISSA-1:0] B_FRACT = B[`MANTISSA-1:0];
		reg L;
		always @(*) begin
			G = 0;
			E = 0;
			L = 0;
			flag = 0;
			if (A == B) begin
				E = 1;
			end else if ((A_S != B_S)) begin
				// aret farklysa
				if (A_S) L = 1; // a negatif, b pozitif
				else G = 1;    // a pozitif, b negatif
			end else begin
				if(ws)begin						
					// aretler aynysa
					if (A_EXP > B_EXP) begin
						 // s karlatrmas
						 if (!A_S ) G = 1;
						 else L = 1;
					end else if (A_EXP < B_EXP) begin
						 if (!A_S) L = 1;
						 else G = 1;
					end else begin
						 // sler aynysa, fract karlatrmas
						 if (A_FRACT > B_FRACT) begin
							  if (!A_S) G = 1;
							  else L = 1;
						 end else begin
							  if (!A_S) L = 1;
							  else G = 1;
						 end
					end
				end else begin				
					// aretler aynysa
					if (A_EXP > B_EXP) begin
						 // s karlatrmas
						 G = 1;
					end else if (A_EXP < B_EXP) begin
						 L = 1;
					end else begin
						 // sler aynysa, fract karlatrmas
						 if (A_FRACT > B_FRACT) begin
							  G = 1;
						 end else begin
							  L = 1;
						 end
					end
				end
			end
			flag = 1;
		end
endmodule

module Four_Bit_Divider(input [`MANTISSA:0] a,
								input [`MANTISSA:0] b,
								output reg [`MANTISSA+1:0] div_result);
	integer i = 0;
	reg [`MANTISSA+1:0] n;
	reg [`MANTISSA+1:0] c;

	always @(*)begin
		n=0;
		c=0;
		div_result[`MANTISSA+1] = (a >= b)? 1 : 0;
		c = (a >= b)? (a-b)<<1 : a<<1;
		for(i = 1; i<`MANTISSA+2; i=i+1)begin
			n = c-{1'b1,b};
			if(n[`MANTISSA+1])begin
				div_result[`MANTISSA+1-i] = 1;
				c = c-{1'b1,b}<<1;
			end else begin
				div_result[`MANTISSA+1-i]=0;
				c = c<<1;
			end
		end
	end
endmodule

module ErrorDetector(
    input [`W-2:0] AU,
    input [`W-2:0] AL,
    input [`W-2:0] BU,
    input [`W-2:0] BL,
    output reg [3:0] error,
	 output ready
    );
	
	 assign ready = (error == 4'b0000) ? 1'b1 : 1'b0;
	 
	 always @(*)begin
		error = 4'b0000;
		if(AU[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(AU[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 4'b0001;
			else //INF CHECK
				error = 4'b1001;
				
		if(AL[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(AL[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 4'b0010;
			else //INF CHECK
				error = 4'b1010;
				
		if(BU[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(BU[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 4'b0011;
			else //INF CHECK
				error = 4'b1011;
				
		if(BL[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(BL[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 4'b0100;
			else //INF CHECK
				error = 4'b1100;
	 end
endmodule

module ZeroComparatorG(
    input [`W-1:0] A,
    output G
);
	 assign G = (~A[`W-1] && A[`W-2:0]) != {(`W-1){1'b0}};
endmodule

module ZeroComparatorL(
    input [`W-1:0] A,
    output L
);
	 assign L = (A[`W-1] && A[`W-2:0]) != {(`W-1){1'b0}};
endmodule

module CrossComparator(
		input [`W-1:0] AU,
		input [`W-1:0] AL,
		input [`W-1:0] BU,
		input [`W-1:0] BL,
		output reg [3:0] state
		);
		
		wire mama;
		wire mami;
		wire mima;
		wire mimi;
		wire maqmaq;
		wire maqmiq;
		wire miqmaq;
		wire miqmiq;
		wire flag1;
		wire flag2;
		wire flag3;
		wire flag4;
		
		Comparator cmp_mama (.A(AU), .B(BU), .G(mama), .E(maqmaq), .flag(flag1));
		Comparator cmp_mami (.A(AU), .B(BL), .G(mami), .E(maqmiq), .flag(flag2));
		Comparator cmp_mima (.A(AL), .B(BU), .G(mima), .E(miqmaq), .flag(flag3));
		Comparator cmp_mimi (.A(AL), .B(BL), .G(mimi), .E(miqmiq), .flag(flag4));
		
		always @(*) begin
			if (flag1 & flag2 & flag3 & flag4) begin
				case ({mama, mami, mima, mimi, maqmaq, maqmiq, miqmaq, miqmiq})
					8'b0000_0000: state = 4'b0001; // hepsi sfr before i,j
					8'b0000_0100: state = 4'b0010; // maqmiq = 1 meets i,j
					8'b1101_0000: state = 4'b0011; // mimi, mami, mama = 1 overlaps i,j
					8'b0101_0000: state = 4'b0100; // mami = 1 during i,j
					8'b0100_0001: state = 4'b0101; // mami, miqmiq = 1 starts i,j
					8'b0101_1000: state = 4'b0110; // mimi, mami, maqmaq = 1 finishes i,j
					8'b0000_1001: state = 4'b0111; // maqmaq, miqmiq = 1 equal i,j
					8'b1111_0000: state = 4'b1000; // mami, mimi, mama, mima = 1 before j,i
					8'b1101_0010: state = 4'b1001; // mami, mimi, mama, miqmaq = 1 meets j,i
					8'b0100_0000: state = 4'b1010; // mami = 1 overlaps j,i
					8'b1100_0000: state = 4'b1011; // mami, mama = 1 during j,i
					8'b1100_0001: state = 4'b1100; // mami, mama, miqmiq = 1 starts j,i
					8'b0100_1000: state = 4'b1101; // mami, maqmaq = 1 finishes j,i
					default:      state = 4'b0000; // Varsaylan durum
				endcase
			end else begin
					state = 4'b1110;
			end
		end
endmodule

module DividerTopModule(input [`W-1:0] n1,n2,
					input [4:0] OPCODE,
					output [`W-1:0] result,
					output reg flagout);
	 wire s1,s2;
	 wire[`EXP-1:0] exp1,exp2,f_exp;
	 wire[`MANTISSA-1:0] frac1,frac2,f_frac;
	 wire[`MANTISSA+1:0] div_result;
	 wire[`EXP-1:0] exp_result;
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
	 assign result = (OPCODE==5'b00011)?{s1^s2,f_exp,f_frac}:{`W{1'bz}}; 
endmodule

module Div_Normalization(input [`EXP-1:0] exp_result,
								 input [`MANTISSA+1:0] frac_result,
								 input flagin,
								 output reg flagout,
								 output reg [`EXP-1:0] final_exp,
								 output reg [`MANTISSA-1:0] final_frac);
	 
	integer i = 0;
	integer i2 = 0;
	reg flag;
	reg [`MANTISSA+1:0] tmp;
	always@(*)begin
		tmp = frac_result;
		flag = 1'b0;
		final_exp = exp_result;
		if(~tmp[`MANTISSA+1])begin
			for (i = `MANTISSA;i>=0;i=i-1) begin
				if ((tmp[i] == 1'b1) & ~flag)begin
					i2 = `MANTISSA+1-i;
					flag = 1'b1;
				end
			end	
			tmp = tmp << i2;
			final_exp = exp_result - i2;
		end 
		
		if(tmp[0])begin
			tmp = tmp+1;
		end
		
		final_frac = tmp[`MANTISSA:1];
		if(~tmp[`MANTISSA+1])begin
			final_exp = final_exp-1;		
			final_frac = 0;
		end	
		flagout = flagin? 0:1;
	end
endmodule

module AdderSignFunction(
    input [`MANTISSA+4:0] fract1,
    input [`MANTISSA+4:0] fract2,
    input s1,
    input s2,
    input operator,
    output reg s=0
    );
always @ (fract1,fract2,s1,s2,operator)begin
	//Toplama
	if(~operator)begin
		if(~(s1^s2))begin
			s=s1;
		end else if(s1^s2) begin
			if(fract1>fract2)begin
				s=s1;
			end else if(fract1<fract2) begin
				s=s2;
			end else begin
				//errors:
					/*
					000 >= no error
					001 >= zero case
					010 >= +infinit overflow
					011 >= -infinit overflow
					100 >= Underflow
					101 >= Div by infinit
					110 >= +Div by zero
					111 >= -Div by zero
					*/
				$display("Sonu 0 iaret yok");
			end
		end
	end
	//kartma
	else if(operator)begin
		//Saylarn iaretleri farkl
		if(s1^s2)begin
			s=s1;
		//Saylarn iaretleri ayn
		end else if(~(s1^s2)) begin
			//Ilk say ikinci saydan byk
			if(fract1>fract2)begin
				s=s1;
			//Ikinci say ilk saydan byk
			end else if(fract1<fract2) begin
				s=~s1;
			//Birbirlerine eit
			end else begin
				//errors:
					/*
					000 >= no error
					001 >= zero case
					010 >= +infinit overflow
					011 >= -infinit overflow
					100 >= Underflow
					101 >= Div by infinit
					110 >= +Div by zero
					111 >= -Div by zero
					*/
				$display("Sonu 0 iaret yok");
			end
		end
	end	
end
endmodule

module FullAdder( input a, b, cin, 
						output sum, cout);
		
		assign sum = a ^ b ^ cin;
		assign cout = (a & b) | ( b & cin) | ( a & cin);
endmodule

module Four_Bit_Substractor_Div(input [`EXP-1:0] A,B,
										  output [`EXP-1:0] Sum, 
										  output cout);
		wire [`EXP-2:0] carry;
		wire [`EXP-1:0] t_sum;
		FullAdder fad0 (.a(A[0]), .b(~B[0]), .cin(1'b1), .sum(t_sum[0]), .cout(carry[0]));
		FullAdder fad1 (.a(A[1]), .b(~B[1]), .cin(carry[0]), .sum(t_sum[1]), .cout(carry[1]));
		FullAdder fad2 (.a(A[2]), .b(~B[2]), .cin(carry[1]), .sum(t_sum[2]), .cout(carry[2]));
		FullAdder fad3 (.a(A[2]), .b(~B[2]), .cin(carry[2]), .sum(t_sum[3]), .cout(carry[3]));
		FullAdder fad4 (.a(A[3]), .b(~B[3]), .cin(carry[3]), .sum(t_sum[4]), .cout(cout));

	   assign Sum = {cout,t_sum} + (`W-1);
endmodule

module MultiplierTopModule #(parameter updown = 0)(input clk,
		input [`W-1:0] A,
		input [`W-1:0] B,
		input [`W-1:0] C,
		input [`W-1:0] D,
		input [4:0] OPCODE,
		input dual,
		output reg [`W-1:0] E,
		output reg flag);
		
		reg s1,s2;
		reg [`EXP-1:0] exp1,exp2;
		reg [`MANTISSA-1:0] fract1, fract2;
		
		
		reg [1:0] state = 2'b00;
		wire [1:0] normstate, roundstate;
		wire c_sumexp, temp1gtemp2;
		wire [((`MANTISSA+1)*2)-1:0] mult_fract;
		wire [`EXP-1:0] mult_sumexp, norm_exp;
		reg  [`EXP-1:0] mult_sumexp2;
		wire [((`MANTISSA+1)*2)-1:0] norm_res; 
		wire [`W-1:0] temp0, temp1, temp2;
		reg ch = 0;
		reg [(`W*4)-1:0] tABCD=0;

		always@(*)begin
			
			flag <= (OPCODE==5'b00010)?1'b0:1'bz;

			case({dual,state})
				3'b100:begin
						flag <= (OPCODE==5'b00010)?1'b0:1'bz;
						E <= 0;
						s1 <= (~updown[0])?A[`W-1]:C[`W-1];
						s2 <= B[`W-1];
						exp1 <= (~updown[0])?A[`W-2:`MANTISSA]:C[`W-2:`MANTISSA];
						exp2 <= B[`W-2:`MANTISSA];
						fract1 <= (~updown[0])?A[`MANTISSA-1:0]:C[`MANTISSA-1:0];
						fract2 <= B[`MANTISSA-1:0];
				end
				3'b101:begin
						s1 <= (~updown[0])?C[`W-1]:A[`W-1];
						s2 <= D[`W-1];
						exp1 <= (~updown[0])?C[`W-2:`MANTISSA]:A[`W-2:`MANTISSA];
						exp2 <= D[`W-2:`MANTISSA];
						fract1 <= (~updown[0])?C[`MANTISSA-1:0]:A[`MANTISSA-1:0];
						fract2 <= D[`MANTISSA-1:0];
				end
				3'b110:begin
					flag <= (OPCODE==5'b00010)?1'b1:1'bz;
					E <= (OPCODE==5'b00010)?(temp1gtemp2?temp1:temp2):{`W{1'bz}};
				end
				default:begin
					s1 <= A[`W-1];
					s2 <= B[`W-1];
					exp1 <= A[`W-2:`MANTISSA];
					exp2 <= B[`W-2:`MANTISSA];
					fract1 <= A[`MANTISSA-1:0];
					fract2 <= B[`MANTISSA-1:0];
					E <= (OPCODE==5'b00010)?(temp0):{`W{1'bz}};
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
			 mult_sumexp2 = {c_sumexp,mult_sumexp}-(`W-1);
		end
		
		assign mult_fract = {1'b1,fract1}*{1'b1,fract2};
		NormalizeMul normmul(mult_fract, mult_sumexp2, s1^s2, norm_res, norm_exp, dual, state, normstate, ch);
		RoundingMul roundmul(norm_res, norm_exp, s1^s2, temp0, temp1, temp2, dual, normstate, roundstate, ch);
		Comparator #(.ws(0))comp(.A(temp1[`W-1:0]), .B(temp2[`W-1:0]), .G(temp1gtemp2));
endmodule

module NormalizeMul(
		input [((`MANTISSA+1)*2)-1:0] m_result,
		input [`EXP-1:0] s_exp,
		input sign,
		output reg [((`MANTISSA+1)*2)-1:0] s_result,
		output reg [`EXP-1:0] n_exp,
		input dual,
		input [1:0] state,
		output reg [1:0] normstate, input ch
	);
	reg [2:0] error;
	always@(*)begin
		case(m_result[((`MANTISSA+1)*2)-1])
			0: begin
					s_result = m_result;
					n_exp = s_exp;
				end
			1: begin
					s_result = m_result>>1;
					n_exp = s_exp + 5'b00001;
					if(s_exp == 5'b11110)
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
		input [((`MANTISSA+1)*2)-1:0] s_result,		
		input [`EXP-1:0] r_exp,		
		input sign,
		output reg [`W-1:0] temp0,
		output reg [`W-1:0] temp1,
		output reg [`W-1:0] temp2,
		input dual,
		input [1:0] normstate,
		output reg [1:0] roundstate,
		input ch
	);
	reg [`MANTISSA+1:0] tmp;
	reg [2:0] error;
	reg [`EXP-1:0] f_exp;
	reg [`MANTISSA-1:0] f_result;

	always@(*)begin
		f_exp = r_exp;//21--9
		tmp = s_result[((`MANTISSA+1)*2)-1:(((`MANTISSA+1)*2)-1)-(`MANTISSA+1)];
		if(s_result[2])begin
			tmp = s_result[((`MANTISSA+1)*2)-1:(((`MANTISSA+1)*2)-1)-(`MANTISSA+2)] + 1'b1;
			//Renormalize
			if ( tmp[`MANTISSA+1] == 1'b1)
			begin
				tmp =  tmp >> 1;
				f_exp = r_exp + 1'b1;
				if(r_exp == 5'b11110)
					error = {2'b01,sign};
					$display("Overflow error rounding");
			end
		end
		f_result = tmp[`MANTISSA-1:0];
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

module AdderSubtractorTopModule(
		input [`W-1:0] A,
		input [`W-1:0] B,
		input [4:0] OPCODE,
		output [`W-1:0] C,
		output reg flag);
	wire Operator;
	reg [`MANTISSA+4:0] tempsum;
	reg [`W-1:0] ress;
	reg [`EXP-1:0] tempexp;
	reg [`MANTISSA-1:0] normleftshift;
	reg [`MANTISSA-1:0] roundedfract;
	wire finalsign;
	reg [`EXP-1:0] normexp;
	reg [`MANTISSA+1:0] normsum;
	wire sign_a, sign_b;
	wire [`EXP-1:0] exp_a, exp_b;
	wire [`MANTISSA:0] mant_a, mant_b;
	
	wire abigeqb,cout;
	wire [`EXP-1:0] diff;
	wire [`MANTISSA+4:0] bigfract, lowfract;
	wire [`MANTISSA+4:0] rightshifted;
	wire [`MANTISSA+4:0] a2,b2,sum;
	wire [`EXP-1:0] bigexp;
	assign Operator = OPCODE[0];
	assign sign_a = A[`W-1];
	assign exp_a = A[`W-2:`MANTISSA];
	assign mant_a = {(|exp_a)?1'b1:1'b0,A[`MANTISSA-1:0]};
	
	assign sign_b = B[`W-1];
	assign exp_b = B[`W-2:`MANTISSA];
	assign mant_b = {(|exp_b)?1'b1:1'b0,B[`MANTISSA-1:0]};
	
	assign abigeqb = (exp_a >= exp_b);
	assign diff = abigeqb?(exp_a-exp_b):(exp_b-exp_a);
	assign bigexp = abigeqb?exp_a:exp_b;
	assign bigfract = {1'b0,(abigeqb?mant_a:mant_b),3'b000};	//ph_flflfl_rgg
	assign lowfract = {1'b0,(abigeqb?mant_b:mant_a),3'b000}; //01_101_000
	assign rightshifted = lowfract>>diff;
	assign a2 = abigeqb?bigfract:rightshifted;
	assign b2 = abigeqb?rightshifted:bigfract;
	
	assign {cout, sum} = ~(~sign_a& (Operator^sign_b) | sign_a&~(Operator^sign_b))?(a2+b2):(Operator^sign_b?(a2-b2):(b2-a2));
	AdderSignFunction signFunc(.fract1(a2), .fract2(b2), .s1(sign_a), .s2(sign_b), .operator(Operator), .s(finalsign));
	//normalize
	always @(sum, bigexp, cout)begin
		tempsum = cout?-sum:sum;
		tempexp = bigexp;
		normleftshift = 1'b0;
		if(tempsum[`MANTISSA+4])begin
			tempsum = (tempsum[0] == 1'b1) ?(tempsum+ 1'b1):(tempsum);
			tempsum = tempsum >> 1;
			tempexp = bigexp + 1'b1;
			if(tempexp == {`EXP{1'b1}})begin//Overflow check
				//011 -infinit
				//010 +infinit			
				$display("error infinit %b",tempexp);
			end
		end else if (tempsum[`MANTISSA+4:`MANTISSA+3] == 2'b00) begin
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
				default:  normleftshift = 0;
			endcase
			tempsum = tempsum << normleftshift;
			tempexp = bigexp - normleftshift;
			if(bigexp <= normleftshift)begin
				$display("error 0 %b %b",bigexp, normleftshift);
			end
			//eer exp saysndan shift says karldnda exp limitini ayorsa hata vermeli! 
			//0001 den kk 1110 dan byk olmamal
		end
	end
	
	
	//rounding
	always @(*)begin //01000100 
		flag = 1'b0;
		normexp = tempexp;// 1011
		if(tempsum[`MANTISSA+4:`MANTISSA+3] == 2'b00)begin
			$display("hata hidden bit yok");
		end 
		if(tempsum[2] == 1'b1)begin
			//Rounding
			normexp = tempexp;// 1011
			normsum = tempsum[`MANTISSA+4:3] + 1'b1;//01001 
			//Renormalize
			if (normsum[`MANTISSA+1] == 1'b1)
			begin
				normsum = normsum >> 1;
				normexp = tempexp + 1'b1;
				if(normexp == {`EXP{1'b1}})begin
					//errors:
						/*
						000 >= no error
						001 >= zero case
						010 >= +infinit overflow
						011 >= -infinit overflow
						100 >= Underflow
						101 >= Div by infinit
						110 >= +Div by zero
						111 >= -Div by zero
						*/
					$display("error infinit %b",normexp);
				end
			end
		end else begin
			normsum = tempsum[`MANTISSA+4:3];
			normexp = tempexp;
		end
		roundedfract = normsum[`MANTISSA-1:0];
		flag = 1'b1;
		ress = {finalsign, normexp, roundedfract};
	end
	assign C = ress;
endmodule
