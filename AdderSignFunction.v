`timescale 1ns / 1ps
module AdderSignFunction(
    input [7:0] fract1,
    input [7:0] fract2,
    input s1,
    input s2,
    input operator,
    output reg s=0
    );
always@(fract1,fract2,s1,s2,operator)
begin
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
				$display("Sonuç 0 işaret yok");
			end
		end
	end
	//Çıkartma
	else if(operator)begin
		//Sayıların işaretleri farklı
		if(s1^s2)begin
			s=s1;
		//Sayıların işaretleri aynı
		end else if(~(s1^s2)) begin
			//Ilk sayı ikinci sayıdan büyük
			if(fract1>fract2)begin
				s=s1;
			//Ikinci sayı ilk sayıdan büyük
			end else if(fract1<fract2) begin
				s=~s1;
			//Birbirlerine eşit
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
				$display("Sonuç 0 işaret yok");
			end
		end
	end
		
	
end
endmodule