module LAB1_210104004228_1(

input [3:0] A,
input [3:0] B,
output F
);

// comparison 4 bit

wire [3:0]cable;

xnor (cable[0], A[0],B[0]);
xnor (cable[1], A[1],B[1]);
xnor (cable[2], A[2],B[2]);
xnor (cable[3], A[3],B[3]);


and (F, cable[0],cable[1],cable[2],cable[3]);






endmodule 