module LAB0_210104004228 (
	input A,B,C,
	output Q
);

wire [5:0] Cable;


and and1(Cable[0], A,B,C);

not not1(Cable[1],B);
not not2(Cable[2],C);

or or1(Cable[3],Cable[1],Cable[2]);

and and2(Cable[4],Cable[3],A);

or or2(Q,Cable[4],Cable[0]);


endmodule 