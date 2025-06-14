
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
	output reg flag,
	output reg [2:0] error,	
	output dual
);
	wire [2:0] err_w, err_wal, err_wau, err_wml, err_wmu, err_wdl, err_wdu;
	wire [  3:0] condition;
	wire [`W-1:0] ANSUDIV, ANSLDIV;
	wire [`W-1:0] ANSUMUL, ANSLMUL;
	wire [`W-1:0] ANSLADD, ANSUADD;
	wire flagadd1, flagadd2, flagmul1, flagmul2, flagdiv1, flagdiv2;
	reg flagadd1_reg, flagadd2_reg, flagdiv1_reg, flagdiv2_reg, flagmul1_reg, flagmul2_reg;
	always @(*) begin
		 if(|err_w)begin
			 error <= err_w;
		 end else begin
			 case (funct)
				  5'b00000, 5'b00001: begin // Toplama/karma
						error <= (|err_wau != 1'b0) ? err_wau :
									(|err_wal != 1'b0) ? err_wal : 3'b000;
				  end
				  5'b00010: begin // arpma
						error <= (|err_wmu != 1'b0) ? err_wmu :
									(|err_wml != 1'b0) ? err_wml : 3'b000;
				  end
				  5'b00011: begin // Blme
						error <= (|err_wdu != 1'b0) ? err_wdu :
									(|err_wdl != 1'b0) ? err_wdl : 3'b000;
				  end
				  default: begin
						error <= 3'b000; // lem yok  Error sfr
				  end
			endcase
		end
	end

	reg [1:0] fdual = 0;
	wire [`W-1:0] F1, F2, S1, S2;
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
		.dual(dual),
		.error(err_w)
	);
	AdderSubtractorTopModule adderdown(F1, S1, funct, ANSLADD, flagadd1, err_wal);
	AdderSubtractorTopModule adderup  (F2, S2, funct, ANSUADD, flagadd2, err_wau);							 				
	MultiplierTopModule #(.updown(0)) multdown (clk, F1, S1, F2, S2, funct, dual, ANSLMUL, flagmul1, err_wml); 
	MultiplierTopModule #(.updown(1)) multup   (clk, F2, S2, F1, S1, funct, dual, ANSUMUL, flagmul2, err_wmu); 
	DividerTopModule divdown(F1, S1, funct, ANSLDIV, flagdiv1, err_wdl);
	DividerTopModule divup(F2, S2, funct, ANSUDIV, flagdiv2, err_wdu);
	// Register flags to handle asynchronous setting
	
	always @(posedge clk or posedge rst) begin
	
		if (rst) begin
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
			// Register flags when they become 1
			if (flagadd1) flagadd1_reg <= 1'b1;
			if (flagadd2) flagadd2_reg <= 1'b1;
			if (flagdiv1) flagdiv1_reg <= 1'b1;
			if (flagdiv2) flagdiv2_reg <= 1'b1;
			if (flagmul1) flagmul1_reg <= 1'b1;
			if (flagmul2) flagmul2_reg <= 1'b1;
			
			// Handle add operations
			if (flagadd1_reg && flagadd2_reg) begin
				if (funct == 5'b00001 || funct == 5'b00000) begin
					result <= {ANSLADD, ANSUADD};
					flag <= 1'b1;
					// Reset flags after capturing result
					flagadd1_reg <= 1'b0;
					flagadd2_reg <= 1'b0;
				end
				
				if (funct == 5'b01001 || funct == 5'b01000 || funct == 5'b01010) begin
					result <= {{16{1'b0}}, ANSUADD};
					flag <= 1'b1;
					// Reset flags after capturing result
					flagadd1_reg <= 1'b0;
					flagadd2_reg <= 1'b0;
				end
			end
			
			if (funct == 5'b01011 ) begin
				result <= {{16{1'b0}}, a[`TOTALW-1:`W]};
				flag <= 1'b1;
				// Reset flags after capturing result
			end
			if (funct == 5'b01100) begin
				result <= {{16{1'b0}}, a[ 	    `W-1:0]};
				flag <= 1'b1;
				// Reset flags after capturing result
			end
			// Handle multiply operations
			if (flagmul1_reg && flagmul2_reg) begin
				if (funct == 5'b00010) begin
					result <= {ANSLMUL, ANSUMUL};
					flag <= 1'b1;
					// Reset flags after capturing result
					flagmul1_reg <= 1'b0;
					flagmul2_reg <= 1'b0;
				end
			end
			// Handle divide operations
			if (flagdiv1_reg && flagdiv2_reg) begin
				if (funct == 5'b00011) begin
					result <= {ANSLDIV, ANSUDIV};
					if (dual == 1'b1 && fdual == 2'b00) begin
						fdual <= 2'b01;
					end else if (dual == 1'b1 && fdual == 2'b01) begin
						fdual <= 2'b10;
					end else if (dual == 1'b1 && fdual == 2'b10) begin
						fdual <= 2'b11;
					end else begin					
						flag <= 1'b1;
					end
					// Reset flags after capturing result
					flagdiv1_reg <= 1'b0;
					flagdiv2_reg <= 1'b0;
				end
			end
			// Handle other operation results
			if (funct[4:3] == 2'b10) begin
				if(funct == 5'b10000)begin
					result <= {{28{1'b0}},stateCross};
					flag <= 1'b1;
				end else begin
					result <= {{31{1'b0}},((stateCross[2:0] == funct[2:0]) && (stateCross[3] == 1'b0)?1'b1:1'b0)};
					flag <= 1'b1;
				end
			end
			if (flag) begin
				flag <= 1'b0;
				result <= dual?{ANSLMUL, ANSUMUL}: 32'bz;
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
		output reg dual,
		output reg [2:0] error
		);
		wire [2:0] errore;
		reg flag = 0;
		wire G_AU_0;
		wire G_BU_0;
		wire L_AL_0;
		wire L_BL_0;
		wire ready;
		ZeroComparatorG cmp_AU_0(.A(AU), .G(G_AU_0));
		ZeroComparatorL cmp_AL_0(.A(AL), .L(L_AL_0));
		ZeroComparatorG cmp_BU_0(.A(BU), .G(G_BU_0));
		ZeroComparatorL cmp_BL_0(.A(BL), .L(L_BL_0));
		CrossComparator cross_comp(.AU(AU), .AL(AL), .BU(BU), .BL(BL), .state(stateCross));
		ErrorDetector errdet(.AU(AU[`W-2:0]), .AL(AL[`W-2:0]), .BU(BU[`W-2:0]), .BL(BL[`W-2:0]), .error(errore));
		reg errordiv = 1'b0;
		always @(*) begin
			errordiv = 1'b0;
			dual = 1'b0;
			condition = 4'b0000;
			flag = 0;
			F1 = `W'b0;
			S1 = `W'b0;
			F2 = `W'b0;
			S2 = `W'b0;
			if(|errore) begin
				error = errore;
			end else if(errordiv) begin
				error = {3'b110};
			end
			if(OPCODE[4:2] == 3'b000) begin
				if(OPCODE[1:0] == 2'b10 || OPCODE[1:0] == 2'b11) begin
					// Durum 1: AL >= 0 && BL >= 0 // 
					if (!L_AL_0 && !L_BL_0) begin
						condition = (OPCODE == 4'b0010) ? 4'b0011 : 4'b0110;
					end
					// Durum 2: AL >= 0 && BL < 0 < BU
					else if (!L_AL_0 && L_BL_0 && G_BU_0) begin
						condition = (OPCODE == 5'b00010) ? 4'b1011 : 4'b1111;
						errordiv = (OPCODE == 5'b00010) ? 1'b0 : 1'b1;
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
						errordiv = (OPCODE == 5'b00010) ? 1'b0 : 1'b1;
					end
					// Durum 8: AU <= 0 && BU <= 0
					else if (!G_AU_0 && !G_BU_0 ) begin
						condition = (OPCODE == 5'b00010) ? 4'b1100 : 4'b1001;
					end
					// Durum 9: AL < 0 < AU && BL < 0 < BU
					else if (L_AL_0 && G_AU_0 && L_BL_0 && G_BU_0) begin
						condition = (OPCODE == 5'b00010) ? 4'b1110 : 4'b1111;
						errordiv = (OPCODE == 5'b00010) ? 1'b0 : 1'b1;
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
				flag = 1'b1;
			end else if (OPCODE[4:3] == 2'b01)begin
				if(OPCODE[2:0] == 3'b000 || OPCODE[2:0] == 3'b001 || OPCODE[2:0] == 3'b010) begin
					F1 = 16'b0;
					S1 = 16'b0;
					F2 = AU;
					S2 = AL;
				end
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
    output reg [2:0] error
    );
	 
	 always @(*)begin
		error = 3'b000;
		if(AU[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(AU[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 3'b001;
			else //INF CHECK
				error = 3'b010;
				
		if(AL[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(AL[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 3'b001;
			else //INF CHECK
				error = 3'b010;
				
		if(BU[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(BU[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 3'b001;
			else //INF CHECK
				error = 3'b010;
				
		if(BL[`W-2:`MANTISSA] == {`EXP{1'b1}}) //NaN CHECK
			if(BL[`MANTISSA-1:0] != {`MANTISSA{1'b0}})
				error = 3'b001;
			else //INF CHECK
				error = 3'b010;
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
								output flagout,
								output reg [2:0] error
								);
	wire s1,s2;
	wire[`EXP-1:0] exp1,exp2,f_exp;
	wire[`MANTISSA-1:0] frac1,frac2,f_frac;
	wire[`MANTISSA+1:0] div_result;
	wire[`EXP-1:0] exp_result;
	wire flagin = 1'b0;
	wire flag;
	assign {s1,exp1,frac1} = n1;
	assign {s2,exp2,frac2} = n2;
	wire [1:0] out_of_range;
	always@(*) begin
		if(|out_of_range)begin
				if(out_of_range == 2'b01)begin
					$display("diffa %d",out_of_range);
				
					error = 3'b100;
				end else if(out_of_range == 2'b10)begin
					$display("diffb %d",out_of_range);
					error = 3'b010;
				end
		end else begin
			error = 3'b000;
		end
	end
		
	Four_Bit_Divider div(.a({1'b1,frac1}), .b({1'b1,frac2}), .div_result(div_result));
	Four_Bit_Substractor_Div subs(.A(exp1),.B(exp2),.Sum(exp_result),.out_of_range(out_of_range));
	Div_Normalization div_normalized(.exp_result(exp_result), .frac_result(div_result),.flagin(flagin), .final_exp(f_exp),.final_frac(f_frac), .flagout(flag));
	assign flagout = flag;
	assign result = {s1^s2,f_exp,f_frac}; 
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
			tmp = tmp+1'b1;
		end
		
		final_frac = tmp[`MANTISSA:1];
		if(~tmp[`MANTISSA+1])begin
			final_exp = final_exp-1'b1;		
			final_frac = 0;
		end	
		flagout = flagin? 0:1'b1;
	end
endmodule

module AdderSignFunction(
    input [`MANTISSA+4:0] fract1,
    input [`MANTISSA+4:0] fract2,
    input s1,
    input s2,
    input operator,
    output reg s=0,
	 output reg [2:0] error
    );
always @ (fract1,fract2,s1,s2,operator)begin
	error = 3'b0;
	//Toplama
	if(~operator)begin
		if(~(s1^s2))begin
			s=s1;
		end else if(s1^s2) begin
			if(fract1>fract2)begin
				s=s1;
			end else if(fract1<fract2) begin
				s=s2;
			end else begin//Zero
				error = {3'b001};
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
			end else begin//Zero
				error = {3'b001};
				//$display("Sonu 0 iaret yok");
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

module Four_Bit_Substractor_Div(
    input  [`EXP-1:0] A, B,
    output [`EXP-1:0] Sum, 
    output cout, 
    output [1:0] out_of_range  // bonus: wrap/underflow detect!
);

    wire [`EXP-2:0] carry;
	 wire [`EXP-1:0] t_sum;
    // FullAdder zinciri  5-bit A ve B iin
    FullAdder fad0 (.a(A[0]), .b(~B[0]), .cin(1'b1), .sum(t_sum[0]), .cout(carry[0]));
    FullAdder fad1 (.a(A[1]), .b(~B[1]), .cin(carry[0]), .sum(t_sum[1]), .cout(carry[1]));
    FullAdder fad2 (.a(A[2]), .b(~B[2]), .cin(carry[1]), .sum(t_sum[2]), .cout(carry[2]));
    FullAdder fad3 (.a(A[3]), .b(~B[3]), .cin(carry[2]), .sum(t_sum[3]), .cout(carry[3]));
    FullAdder fad4 (.a(A[4]), .b(~B[4]), .cin(carry[3]), .sum(t_sum[4]), .cout(cout));

    // Eski mantn koruyorum (Sum iin)
    assign Sum = {cout, t_sum} + (`W-1);
	 wire [`EXP:0] Sum2;
    // Gerek signed sonucu kartyoruz:
    wire signed [5:0] real_result;
    assign real_result = $signed({1'b0, A}) - $signed({1'b0, B});

    // Biasl sonucu  Sum2'ye yazyoruz:
    assign Sum2 = real_result + 6'd15;

    // Wrap / Out of range detect (senin istediin aralk: 00001..11110  dec 1..30)
    assign out_of_range = 
        (Sum2 < 6'd1)  ? 2'b10 :    // underflow  "10"
        (Sum2 > 6'd30) ? 2'b01 :    // overflow  "01"
                        2'b00;      // normal aralkta  "00"

endmodule


//11110010
module MultiplierTopModule #(parameter updown = 0)(
	   input clk,
		input [`W-1:0] A, //F2 S2 F1 S1 ///// AU
		input [`W-1:0] B,	// BL
		input [`W-1:0] C, // AL
		input [`W-1:0] D, // BU
		input [4:0] OPCODE,
		input dual,
		output reg [`W-1:0] E,
		output reg flag,
		output reg [2:0] error);
		
		reg s1,s2,s3,s4;
		wire c_controlo1, c_controlo2;
		wire c_controlu1, c_controlu2;
		reg [`EXP-1:0] exp1,exp2,exp3,exp4;
		reg [`MANTISSA-1:0] fract1, fract2, fract3, fract4;
		
		wire c_sumexp,c_sumexp2, temp0gtemp1;
		wire [((`MANTISSA+1)*2)-1:0] mult_fract, mult_fract2;
		wire [`EXP-1:0] mult_sumexp, mult_sumexp3, norm_exp, norm_exp2;
		reg  [`EXP-1:0] mult_sumexp2, mult_sumexp4;
		wire [((`MANTISSA+1)*2)-1:0] norm_res, norm_res2; 
		wire [`W-1:0] temp0, temp1, temp2;
		reg ch = 0;
		reg [(`W*4)-1:0] tABCD=0;
		wire [2:0] error_wna,error_wnb,error_wra,error_wrb;
		wire [2:0] error_wc;
		always@(*)begin
			flag = 1'b0;
			case(dual)
				1'b0:begin
					s1 = A[`W-1];
					s2 = B[`W-1];
					exp1 = A[`W-2:`MANTISSA];
					exp2 = B[`W-2:`MANTISSA];
					fract1 = A[`MANTISSA-1:0];
					fract2 = B[`MANTISSA-1:0];
					E = temp0;
					flag = 1'b1;
				end
				1'b1:begin
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
					E = ((temp0gtemp1 && dual)?temp0:temp1);
					flag = 1'b1;	
				end
				default:begin
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
			
		// Signed exp toplam
		wire signed [5:0] real_exp_sum1;
		wire signed [5:0] real_exp_sum2;

		assign real_exp_sum1 = $signed({1'b0, exp1}) + $signed({1'b0, exp2});
		assign real_exp_sum2 = $signed({1'b0, exp3}) + $signed({1'b0, exp4});

		// Biasl signed sonu
		wire signed [5:0] biased_exp1;
		wire signed [5:0] biased_exp2;

		assign biased_exp1 = real_exp_sum1 - 6'd15;
		assign biased_exp2 = real_exp_sum2 - 6'd15;

		// Overflow / Underflow kontrol
		assign c_controlo1 = (biased_exp1 >= 6'd30); // +Overflow threshold
		assign c_controlu1 = (biased_exp1 <= 6'd1);  // Underflow threshold
		
		assign c_controlo2 = (biased_exp2 >= 6'd30);
		assign c_controlu2 = (biased_exp2 <= 6'd1);

		// Error karar mant (combinational)
		always @(*) begin
			 if (|error_wna) begin
				  error = error_wna;
			 end else if (|error_wnb) begin
				  error = error_wnb;
			 end else if (|error_wra) begin
				  error = error_wra;
			 end else if (|error_wrb) begin
				  error = error_wrb;
			 end else if (c_controlo1 || (c_controlo2 && dual) || c_controlu1 || (c_controlu2 && dual)) begin
				  case ({(c_controlo1 || (c_controlo2 && dual)), (c_controlu1 || (c_controlu2 && dual))})
						2'b00: error = 3'b000; // No error
						2'b01: error = 3'b100; // Underflow
						2'b10: error = 3'b010; // +Infinity Overflow
						2'b11: error = 3'b010; // Conflict: Treat as Overflow
				  endcase
			 end else begin
				  error = 3'b000; // Default: No error
			 end
		end

		assign {c_sumexp,mult_sumexp} = exp1+exp2;
		//TODOSAL
		always@(mult_sumexp)begin
			 mult_sumexp2 = {c_sumexp,mult_sumexp}-(`W-1);
		end
		
		assign {c_sumexp2,mult_sumexp3} = exp3+exp4;
		always@(mult_sumexp3)begin
			 mult_sumexp4 = {c_sumexp2,mult_sumexp3}-(`W-1);
		end
		assign mult_fract = {1'b1,fract1}*{1'b1,fract2};
		assign mult_fract2 = {1'b1,fract3}*{1'b1,fract4};
		NormalizeMul normmul(mult_fract, mult_sumexp2, s1^s2, norm_res, norm_exp, dual, error_wna);
		NormalizeMul #(.duality(1))normmul2 (mult_fract2, mult_sumexp4, s3^s4, norm_res2, norm_exp2, dual, error_wnb);
		RoundingMul roundmul(norm_res, norm_exp, s1^s2, temp0, dual, error_wra);
		RoundingMul #(.duality(1))roundmul2(norm_res2, norm_exp2, s3^s4, temp1, dual, error_wrb);
		Comparator #(.ws(0))comp(.A(temp0), .B(temp1), .G(temp0gtemp1));
endmodule

module NormalizeMul #(parameter duality = 0)(
		input [((`MANTISSA+1)*2)-1:0] m_result,
		input [`EXP-1:0] s_exp,
		input sign,
		output reg [((`MANTISSA+1)*2)-1:0] s_result,
		output reg [`EXP-1:0] n_exp,
		input dual,
		output reg [2:0] error
	);
	always@(*)begin
		if (duality == 1'b0 || dual == 1'b1)begin
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
							//$display("Overflow error normalize");
					end
			endcase
		end else begin 
			s_result = 0;
			n_exp = 0;
		end
	end
endmodule

module RoundingMul#(parameter duality = 0)(
		input [((`MANTISSA+1)*2)-1:0] s_result,		
		input [`EXP-1:0] r_exp,		
		input sign,
		output reg [`W-1:0] temp1,
		input dual,
		output reg [2:0] error
	);
	reg [`MANTISSA+1:0] tmp;
	
	reg [`EXP-1:0] f_exp;
	reg [`MANTISSA-1:0] f_result;

	always@(*)begin
	
		if (duality == 1'b0 || dual == 1'b1)begin
			f_exp = r_exp;//21--9
			tmp = s_result[((`MANTISSA+1)*2)-1:(((`MANTISSA+1)*2)-1)-(`MANTISSA+1)];
			
			if(s_result[9])begin
				tmp = s_result[((`MANTISSA+1)*2)-1:(((`MANTISSA+1)*2)-1)-(`MANTISSA+1)] + 'b1;				
				if ( tmp[`MANTISSA+1] == 1'b1)
				begin
				
					tmp =  tmp >> 1;
					f_exp = r_exp + 1'b1;
					
					if(r_exp == 5'b11110)
						error = {2'b01,sign};
						//$display("Overflow error rounding %b",tmp[`MANTISSA+1]);
				end
			end
			f_result = tmp[`MANTISSA-1:0];
			
			temp1 = {sign, f_exp, f_result};
		end
		else begin
			temp1 = {16'b0};
		end
	end
		
endmodule

module AdderSubtractorTopModule(
		input [`W-1:0] A,
		input [`W-1:0] B,
		input [4:0] OPCODE,
		output [`W-1:0] C,
		output reg flag,
		output reg [2:0] error);
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
	reg [2:0] errora, errorb;
	wire abigeqb,cout;
	wire [`EXP-1:0] diff;
	wire [`MANTISSA+4:0] bigfract, lowfract;
	wire [`MANTISSA+4:0] rightshifted;
	wire [`MANTISSA+4:0] a2,b2,sum;
	wire [`EXP-1:0] bigexp;
	wire [2:0] errorw;
	assign Operator = OPCODE[0] || (OPCODE == 5'b01010);
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
	
	always @(*)begin
		if(|errora)begin
			error = errora;
		end else if (|errorb)begin
			error = errorb;
		end else	if (|errorw)begin
			error = errorw;
		end else begin
			error = 3'b000;
		end
	end
	
	assign {cout, sum} = ~(~sign_a& (Operator^sign_b) | sign_a&~(Operator^sign_b))?(a2+b2):(Operator^sign_b?(a2-b2):(b2-a2));
	AdderSignFunction signFunc(.fract1(a2), .fract2(b2), .s1(sign_a), .s2(sign_b), .operator(Operator), .s(finalsign), .error(errorw));
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
				errora = {2'b01,finalsign};
				//011 -infinit
				//010 +infinit			
				//$display("error infinit %b",tempexp);
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
				//$display("error 0 %b %b",bigexp, normleftshift);
			end
			//eer exp saysndan shift says karldnda exp limitini ayorsa hata vermeli! 
			//0001 den kk 1110 dan byk olmamal
		end
	end
	
	
	//rounding
	always @(*)begin 
		flag = 1'b0;
		normexp = tempexp;
		if(tempsum[`MANTISSA+4:`MANTISSA+3] == 2'b00)begin
			//$display("there is no hidden bit");
		end 
		if(tempsum[2] == 1'b1)begin
			//Rounding
			normexp = tempexp;// 1011
			normsum = tempsum[`MANTISSA+4:3] + 1'b1;
			//Renormalize
			if (normsum[`MANTISSA+1] == 1'b1)
			begin
				normsum = normsum >> 1;
				normexp = tempexp + 1'b1;
				if(normexp == {`EXP{1'b1}})begin//Overflow check
					errorb = {2'b01,finalsign};
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
					//$display("error infinit %b",normexp);
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
	wire [4:0] chexpe;
	assign chexpe = ress[14:10] - 5'b00001;
	wire [4:0] chexp;
	assign chexp	= ress[14:10];
	wire [15:0] ressg;
	assign ressg = (OPCODE == 5'b01000 || OPCODE == 5'b01010)?{ress[15], chexpe, ress[9:0]}:{ress[15], chexp, ress[9:0]};
	assign C = ressg;
endmodule
