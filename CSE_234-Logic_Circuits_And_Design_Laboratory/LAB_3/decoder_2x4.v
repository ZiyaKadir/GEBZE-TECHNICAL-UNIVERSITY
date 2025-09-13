module decoder_2x4(input a,input b,input e,output[3:0]out);

	wire not_a;
	wire not_b;
	not(not_a,a);
	not(not_b,b);
	and(out[0],not_a,not_b,e);
	and(out[1],not_a,b,e);
	and(out[2],a,not_b,e);
	and(out[3],a,b,e);

endmodule 