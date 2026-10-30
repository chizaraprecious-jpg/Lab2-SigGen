#include "Vsigdelay.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "sigdelay_tb_header.hpp"

#define MAX_SIM_CYC 1000000
#define ADDRESS_WIDTH 9
#define RAM_SIZE pow(2, ADDRESS_WIDTH) //number of addresses

int main(int argc, char **argv, char **env) {

    int cycle;
    int plot_en;

    Verilated::commandArgs(argc, argv);
    Vsigdelay* top = new Vsigdelay;
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("sigdelay.vcd");

    init_vbd();
    //set_mode1();
    init_vbd_mic(RAM_SIZE);

    top->clk = 1;
    top->rst = 0;
    top->w_en = 1;
    top->r_en = 1;

    for (cycle = 0; cycle < MAX_SIM_CYC; ++cycle) {

        top->offset = vbdValue();
        plot_en = vbdFlag();
        top->mic_sig = vbdMicValue();

        toggle_clk(top, tfp, cycle);
        vbd_plot(top, plot_en);

        if (Verilated::gotFinish() || vbdGetkey() == 'q') exit(0);
    }

    tfp->close();
    close_vbd();
    exit(0);
}