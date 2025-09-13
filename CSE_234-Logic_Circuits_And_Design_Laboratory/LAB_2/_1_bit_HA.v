module _1_bit_HA(Sum,Carry,A,B);
input A,B;
output Carry,Sum;


xor or1(Sum,A,B);
and or2(Carry,A,B);


endmodule
