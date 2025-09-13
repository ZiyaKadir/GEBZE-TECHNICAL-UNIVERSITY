module decoder_3x8(input a, input b, input c, output[7:0] out);

	wire notc;
	not(notc,c);
	decoder_2x4(a,b,c,out[3:0]);
	decoder_2x4(a,b,notc,out[7:4]);
	
endmodule
