module LAB1_210104004228(

input [3:0] IN,
output F
);

wire [7:0] not_cable;

wire [7:0] cable;


not not0(not_cable[0],IN[0]);

not not1(not_cable[1],IN[1]);

not not2(not_cable[2],IN[2]);

not not3(not_cable[3],IN[3]);



and and1 (cable[0],IN[0], IN[1] , IN [2] , not_cable[3]);

and and2 (cable[1],IN[0], IN[1] , not_cable[2], IN[3]);

and and3 (cable[2],IN[0], not_cable[1] , IN [2] , IN[3]);

and and4 (cable[3],not_cable[0] , IN[1] , IN [2] , IN[3]);

and and5 (cable[4],IN[0],not_cable[1],not_cable[2],not_cable[3]);

and and6 (cable[5],not_cable[0], IN[1] , not_cable[2], not_cable[3]);

and and7 (cable[6],not_cable[0],not_cable[1] , IN [2] , not_cable[3]);

and and8 (cable[7],not_cable[0], not_cable[1] , not_cable[2], not_cable[3]);




or total(F, cable[0],cable[1],cable[2],cable[3],cable[4],cable[5],cable[6],cable[7]);

endmodule 