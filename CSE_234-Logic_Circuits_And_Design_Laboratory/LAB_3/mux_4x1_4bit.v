module mux_4x1_4bit(
	input [3:0] in1_1,
	input [3:0] in2_1,
	input [3:0] in1_2,
	input [3:0] in2_2,
	
	input select_1,
	input select_2,
		
	output [3:0] out
);

	
	wire [3:0] result_1;
	wire [3:0] result_2;
	
	mux_2x1_4bit(in1_1, in1_2, select_2, result_1);
	mux_2x1_4bit(in2_1, in2_2, select_2, result_2);

	mux_2x1_4bit(result_1, result_2 , select_1, out);
	
endmodule 
