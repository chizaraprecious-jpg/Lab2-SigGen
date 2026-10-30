#include "Vsinegen.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int init_vbd() {
    //init Vbuddy
    if (vbdOpen() != 1) return (-1);
    
    vbdHeader("Lab 2: SigGen");
    vbdSetMode(0);
    return 0;
}

void set_mode1() {
	vbdSetMode(1);
}

void toggle_clk(Vsinegen* top, VerilatedVcdC* tfp, int cycle) {
    //clk is the module's clock signal
    for (int clk=0; clk<2; ++clk) { //executes twice for each i, dividing into half cycles
        tfp->dump(2*cycle+clk);     //records trace at time in parameter (unit = ps)
        top->clk = !top->clk;   //switches from pos to neg edge
        top->eval ();           //evaluate hardware model with current inputs
    }
}

void vbd_plot(Vsinegen* top, int en) {
    //++++ plot count value on Vbuddy TFT (y, min, max)
    if (en == 1) {
        vbdPlot(int(top->dout1), 0, 255);
        vbdPlot(int(top->dout2), 0, 255);
    }
}

int close_vbd() {
    vbdClose();
}