`timescale 1ns / 1ps

module Comparator(
		input [7:0] A,
		input [7:0] B,
		output reg G, // a > b ise 1
		output reg E,   // a == b ise 1
		output reg flag
		);
		
		wire A_S = A[7];
		wire [4:0] A_EXP = A[6:3];
		wire [3:0] A_FRACT = A[2:0];
		
		wire B_S = B[7];
		wire [4:0] B_EXP = B[6:3];
		wire [3:0] B_FRACT = B[2:0];
		reg L;
		always @(*) begin
			G = 0;
			E = 0;
			L = 0;
			flag = 0;
			if (A == B) begin
				E = 1;
			end else if (A_S != B_S) begin
				// İşaret farklıysa
				if (A_S) L = 1; // a negatif, b pozitif
				else G = 1;    // a pozitif, b negatif
			end else begin
				// İşaretler aynıysa
				if (A_EXP > B_EXP) begin
					 // Üs karşılaştırması
					 if (!A_S) G = 1;
					 else L = 1;
				end else if (A_EXP < B_EXP) begin
					 if (!A_S) L = 1;
					 else G = 1;
				end else begin
					 // Üsler aynıysa, fract karşılaştırması
					 if (A_FRACT > B_FRACT) begin
						  if (!A_S) G = 1;
						  else L = 1;
					 end else begin
						  if (!A_S) L = 1;
						  else G = 1;
					 end
				end
			end
			flag = 1;
		end
endmodule
