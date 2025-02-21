`timescale 1ns / 1ps
module AdderSubtractorTopModule(
		input [7:0] A,
		input [7:0] B,
		input [4:0] OPCODE,
		output [7:0] C,
		output reg flag);
		wire Operator;
		reg [7:0] tempsum,ress;
		reg [3:0] tempexp;
		reg [2:0] normleftshift;
		reg [2:0] roundedfract;
	wire finalsign;
	reg [3:0] normexp;
	reg [4:0] normsum;
	wire sign_a, sign_b;
	wire [3:0] exp_a, exp_b;
	wire [3:0] mant_a, mant_b;
	
	wire abigeqb,cout;
	wire [3:0] diff;
	wire [7:0] bigfract, lowfract;
	wire [7:0] rightshifted;
	wire [7:0] a2,b2,sum;
	wire [3:0] bigexp;
	assign Operator = OPCODE[0];
	assign sign_a = A[7];
	assign exp_a = A[6:3];
	assign mant_a = {(|exp_a)?1'b1:1'b0,A[2:0]};
	
	assign sign_b = B[7];
	assign exp_b = B[6:3];
	assign mant_b = {(|exp_b)?1'b1:1'b0,B[2:0]};
	
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
		if(tempsum[7])begin
			tempsum = (tempsum[0] == 1'b1) ?(tempsum+ 1'b1):(tempsum);
			tempsum = tempsum >> 1;
			tempexp = bigexp + 1'b1;
			if(tempexp == 4'b1111)begin//Overflow check
				//011 -infinit
				//010 +infinit			
				$display("error infinit %b",tempexp);
			end
		end else if (tempsum[7:6] == 2'b00) begin
			casez (tempsum[5:0])
				6'b1?????:normleftshift = 1;
				6'b01????:normleftshift = 2;
				6'b001???:normleftshift = 3;
				6'b0001??:normleftshift = 4;
				6'b00001?:normleftshift = 5;
				6'b000001:normleftshift = 6;
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
		flag = (OPCODE==5'b00001 || OPCODE == 5'b00000)?1'b0:1'bz;
		normexp = tempexp;// 1011
		if(tempsum[7:6] == 2'b00)begin
			$display("hata hidden bit yok");
		end 
		if(tempsum[2] == 1'b1)begin
			//Rounding
			normexp = tempexp;// 1011
			normsum = tempsum[7:3] + 1'b1;//01001 
			//Renormalize
			if (normsum[4] == 1'b1)
			begin
				normsum = normsum >> 1;
				normexp = tempexp + 1'b1;
				if(normexp == 4'b1111)begin
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
			normsum = tempsum[7:3];
			normexp = tempexp;
		end
		roundedfract = normsum[2:0];
		flag = (OPCODE==5'b00001 || OPCODE == 5'b00000)?1'b1:1'bz;
		ress = {finalsign, normexp, roundedfract};
	end
	assign C = (OPCODE==5'b00000 ||OPCODE==5'b00001)?ress:8'bzzzzzzzz;
	
endmodule
