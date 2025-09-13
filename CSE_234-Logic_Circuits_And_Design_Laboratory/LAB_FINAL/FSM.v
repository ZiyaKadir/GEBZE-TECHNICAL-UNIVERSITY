module FSM (
  input clk,
  input next,
  input reset,
  output reg n0,
  output reg n1,
  output reg n2
);

  reg [1:0] state, nextstate;
  parameter S0 = 2'b00;
  parameter S1 = 2'b01; 
  parameter S2 = 2'b10; 
  parameter S3 = 2'b11; 

  always @(posedge clk) begin
    if (reset) begin
      state <= S0;
    end
    else if (next) begin
      state <= nextstate;
    end
  end

  always @* begin
    case (state)
      S0: begin
        nextstate = S1;
        n0 = 0;
        n1 = 0;
        n2 = 1;
      end
      S1: begin
        nextstate = S2;
        n0 = 1;
        n1 = 0;
        n2 = 1;
      end
      S2: begin
        nextstate = S3;
        n0 = 1;
        n1 = 1;
        n2 = 1;
      end
      S3: begin
        nextstate = S0;
        n0 = 0;
        n1 = 1;
        n2 = 1;
      end
      default: begin
        nextstate = S0;
        n0 = 0;
        n1 = 0;
        n2 = 0;
      end
    endcase
  end

endmodule
