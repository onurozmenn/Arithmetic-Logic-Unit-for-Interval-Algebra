`timescale 1ns / 1ps
module ErrorDetector(
    input [6:0] AU,
    input [6:0] AL,
    input [6:0] BU,
    input [6:0] BL,
    output reg [3:0] error,
	 output ready
    );
	
	 assign ready = (error == 4'b0000) ? 1'b1 : 1'b0;
	 
	 always @(*)begin
		error = 4'b0000;
		if(AU[6:3] == 4'b1111) //NaN CHECK
			if(AU[2:0] != 3'b000)
				error = 4'b0001;
			else //INF CHECK
				error = 4'b1001;
				
		if(AL[6:3] == 4'b1111) //NaN CHECK
			if(AL[2:0] != 3'b000)
				error = 4'b0010;
			else //INF CHECK
				error = 4'b1010;
				
		if(BU[6:3] == 4'b1111) //NaN CHECK
			if(BU[2:0] != 3'b000)
				error = 4'b0011;
			else //INF CHECK
				error = 4'b1011;
				
		if(BL[6:3] == 4'b1111) //NaN CHECK
			if(BL[2:0] != 3'b000)
				error = 4'b0100;
			else //INF CHECK
				error = 4'b1100;
	 end
endmodule
