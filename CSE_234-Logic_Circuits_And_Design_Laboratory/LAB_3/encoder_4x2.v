module encoder_4x2(input[3:0]a,output[1:0]o);

wire[3:0] w;
not(w[0],a[0]);
not(w[1],a[1]);
not(w[2],a[2]);
not(w[3],a[3]);

wire[3:0] result;
and(result[0],w[0],a[1],w[2],w[3]);
and(result[1],w[0],w[1],w[2],a[3]);
or(o[1],result[0],result[1]);


and(result[2],w[0],w[1],a[2],w[3]);
and(result[3],w[0],w[1],w[2],a[3]);
or(o[0],result[2],result[3]);

endmodule