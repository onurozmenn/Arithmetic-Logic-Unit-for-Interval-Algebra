`timescale 1ns / 1ps

module CrossComparator(
		input [7:0] AU,
		input [7:0] AL,
		input [7:0] BU,
		input [7:0] BL,
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
					8'b0000_0000: state = 4'b0001; // hepsi sıfır before i,j
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
					default:      state = 4'b0000; // Varsayılan durum
				endcase
			end else begin
					state = 4'b1110;
			end
		end
endmodule
