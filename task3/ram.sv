//dual port 512 x8 RAM

module ram # (
    parameter   ADDRESS_WIDTH = 9,
                DATA_WIDTH = 8
)(
    input logic                         clk,
    input logic                         w_en,
    input logic                         r_en,
    input logic     [ADDRESS_WIDTH-1:0] w_addr,
    input logic     [ADDRESS_WIDTH-1:0] r_addr,
    input logic     [DATA_WIDTH-1:0]    din,
    output logic    [DATA_WIDTH-1:0]    dout
);

logic [DATA_WIDTH-1:0] ram_array [2**ADDRESS_WIDTH-1:0];

always_ff @(posedge clk) begin
    if (w_en) ram_array[w_addr] <= din;
    if (r_en) dout <= ram_array[r_addr];
end
    
endmodule
