module sinegen #(
    parameter   ADDRESS_WIDTH = 8,
                DATA_WIDTH = 8
)(
    input logic                     clk,
    input logic                     rst,
    input logic                     en,
    input logic [ADDRESS_WIDTH-1:0] incr,
    input logic [ADDRESS_WIDTH-1:0] offset,
    output logic [DATA_WIDTH-1:0]   dout1,
    output logic [DATA_WIDTH-1:0]   dout2
);

logic [ADDRESS_WIDTH-1:0] addr1;
logic [ADDRESS_WIDTH-1:0] addr2;

counter addrCounter (
    .clk    (clk),
    .rst    (rst),
    .en     (en),
    .incr   (incr),
    .offset (offset),
    .count1  (addr1),
    .count2  (addr2)
);

rom sineROM (
    .clk    (clk),
    .addr1   (addr1),
    .addr2   (addr2),
    .dout1   (dout1),
    .dout2   (dout2)
);

endmodule
