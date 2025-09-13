module FSM(
  input clk,
  input increase,
  input decrease,
  output reg odd,
  output reg n0,
  output reg n1
);

  reg [1:0] state, nextstate;
  parameter S0 = 2'b00; // number = 0
  parameter S1 = 2'b01; // number = 1
  parameter S2 = 2'b10; // number = 2
  parameter S3 = 2'b11; // number = 3

  always @(posedge clk) begin
    if (increase && !decrease) begin
      case (state)
        S0: nextstate = S1;
        S1: nextstate = S2;
        S2: nextstate = S3;
        S3: nextstate = S0;
        default: nextstate = S0;
      endcase
    end
    else if (!increase && decrease) begin
      case (state)
        S0: nextstate = S3;
        S1: nextstate = S0;
        S2: nextstate = S1;
        S3: nextstate = S2;
        default: nextstate = S0;
      endcase
    end
    else begin
      nextstate = state;
    end
  end

  always @(posedge clk) begin
    state <= nextstate;
    case (state)
      S0: begin
        odd <= 0;
        n0 <= 0;
        n1 <= 0;
      end
      S1: begin
        odd <= 1;
        n0 <= 1;
        n1 <= 0;
      end
      S2: begin
        odd <= 0;
        n0 <= 0;
        n1 <= 1;
      end
      S3: begin
        odd <= 1;
        n0 <= 1;
        n1 <= 1;
      end
      default: begin
        odd <= 0;
        n0 <= 0;
        n1 <= 0;
      end
    endcase
  end

endmodule
