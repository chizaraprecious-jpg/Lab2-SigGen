module sinegen #(
    parameter   ADDRESS_WIDTH = 8,
                DATA_WIDTH = 8
)(
    input logic                     clk,
    input logic [ADDRESS_WIDTH-1:0] incr,
    input logic                     rst,
    input logic                     en,
    output logic [DATA_WIDTH-1:0]   dout
);

logic [ADDRESS_WIDTH-1:0] addr;

counter addrCounter (
    .clk    (clk),
    .rst    (rst),
    .en     (en),
    .incr   (incr),
    .count  (addr)   //counter output assigned as the address accessed by the rom
);

rom sineROM (
    .clk    (clk),
    .addr   (addr),
    .dout   (dout)
);

endmodule
