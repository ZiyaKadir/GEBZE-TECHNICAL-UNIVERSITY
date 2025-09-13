module _1_bit_FA(A,B,Cin,Sum,Cout);
input A,B,Cin;
output Cout, Sum;
wire w1,w2,w3;


_1_bit_HA HA1(.A(A), .B(B), .Sum(w1), . Carry(w2));
_1_bit_HA HA2(.Sum(Sum), .Carry(w3), .B(Cin), .A(w1));


or or3(Cout,w2,w3);

endmodule
