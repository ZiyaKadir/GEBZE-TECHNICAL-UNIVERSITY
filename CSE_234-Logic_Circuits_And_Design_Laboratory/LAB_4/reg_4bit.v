module reg_4bit(
	
	input clk, 
	input [3:0] d, 
	output reg [3:0] q
);
	always @ (posedge clk)
		q <= d;

endmodule
