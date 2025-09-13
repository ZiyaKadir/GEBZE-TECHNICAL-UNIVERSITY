module LAB3_210104004228(
	input in1,
	input in2,
	input in3,
	input in4,
	
	input select,
		
	output out
);

	wire cable1;
	wire cable2;
	
	_4nand (.out(cable1), .a(in1), .b(in2), .c(in3), .d(in4));
	_4or(.out(cable2), .a(in1), .b(in2) , .c(in3) , .d(in4));
	
	
	_2to1_mux(.out(out), .in1(cable1), .in2(cable2), .select(select));
	
	

endmodule 