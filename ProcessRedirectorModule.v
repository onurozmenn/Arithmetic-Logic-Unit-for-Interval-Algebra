`timescale 1ns / 1ps

module ProcessRedirectorModule( 
		input [7:0] AU,
		input [7:0] AL,
		input [7:0] BU,
		input [7:0] BL,
		input [4:0] OPCODE,
		output [3:0] stateCross,
		output reg [3:0] condition = 4'b1111,
		output reg [7:0] F1, S1, F2, S2,
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
		ErrorDetector errdet(.AU(AU[6:0]), .AL(AL[6:0]), .BU(BU[6:0]), .BL(BL[6:0]), .error(error), .ready(ready));
		
		always @(*) begin
			dual = 1'b0;
			condition = 4'b1111;
			flag = 0;
			F1 = 8'b0;
			S1 = 8'b0;
			F2 = 8'b0;
			S2 = 8'b0;
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
							condition = (OPCODE == 5'b00010) ? 4'b1101 : 4'b1001;
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
