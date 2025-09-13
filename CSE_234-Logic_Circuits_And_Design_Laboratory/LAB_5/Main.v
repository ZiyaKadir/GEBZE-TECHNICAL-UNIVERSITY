module MUX (
  input [4:0] input1,
  input [4:0] input2,
  input [4:0] input3,
  input [4:0] input4,
  input [1:0] select,
  output reg [4:0] output
);
  always @* begin
    case (select)
      2'b00: output = input1;
      2'b01: output = input2;
      2'b10: output = input3;
      2'b11: output = input4;
    endcase
  end
endmodule

module XOR_Gates (
  input [4:0] input1,
  input [4:0] input2,
  output reg [4:0] output
);
  always @* begin
    output = input1 ^ input2;
  end
endmodule

module Adder (
  input [4:0] input1,
  input [4:0] input2,
  output reg [4:0] sum
);
  always @* begin
    sum = input1 + input2;
  end
endmodule

module Main (
  input [4:0] sum,
  input sw1,
  input sw2,
  input load,
  output reg [4:0] led_output
);
  wire [4:0] xor_output;
  wire [4:0] adder_output;
  wire [1:0] select;

  MUX mux (
    .input1(sum),
    .input2(xor_output),
    .input3(adder_output),
    .input4(sum),
    .select({sw2, sw1}),
    .output(led_output)
  );

  XOR_Gates xor_gates (
    .input1(sum),
    .input2(led_output), 
    .output(xor_output)
  );

  Adder adder (
    .input1(led_output),  
    .input2(sum),
    .sum(adder_output)
  );

  reg [4:0] register_out; 
  always @(posedge load) begin
    if (load)
      register_out <= led_output;
  end


endmodule
