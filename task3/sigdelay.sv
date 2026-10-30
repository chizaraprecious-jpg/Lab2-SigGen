module sigdelay #(
    parameter   ADDRESS_WIDTH = 9,
                DATA_WIDTH = 8
)(
    input logic                         clk,
    input logic                         rst,
    input logic                         w_en,
    input logic                         r_en,
    input logic     [ADDRESS_WIDTH-1:0] offset,
    input logic     [DATA_WIDTH-1:0]    mic_sig,
    output logic    [DATA_WIDTH-1:0]    delayed_sig
);

logic     [ADDRESS_WIDTH-1:0] w_addr;
logic     [ADDRESS_WIDTH-1:0] r_addr;

counter addrCounter (
    .clk    (clk),
    .rst    (rst),
    .w_en   (w_en),
    .offset (offset),
    .count1 (w_addr),
    .count2 (r_addr)
);

ram audioRAM (
    .clk    (clk),
    .w_en   (w_en),
    .r_en   (r_en),
    .w_addr (w_addr),
    .r_addr (r_addr),
    .din    (mic_sig),
    .dout   (delayed_sig)
);

endmodule
