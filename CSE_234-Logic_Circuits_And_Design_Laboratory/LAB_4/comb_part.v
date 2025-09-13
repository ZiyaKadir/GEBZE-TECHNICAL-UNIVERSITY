module comb_part(
	input [2:0] IN,
	output [2:0] OUT
);

	assign OUT[0] = ( ~IN[0] & IN[1] & IN [2]);
	assign OUT[1] = (IN[0] ^ IN[1]);
	assign OUT[2] = ( IN[0] | (IN[1] & IN[2]));

endmodule
