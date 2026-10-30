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

void send_vbd_addr(Vsinegen* top, int cycle) {
    //++++ send addr value to Vbuddy (convert to hex)
    vbdHex(4, (int((top->dout) >> 12) & 0xF)); 
    vbdHex(3, (int((top->dout) >> 8) & 0xF));

    //shifts 8-bit addr right by 4 so 4 MSBs become the LSBs
    //ANDing with 0xF (1111) selects the 4 LSBs
    //This gets assigned as the 2nd hex digit (leftmost)
    vbdHex(2, (int((top->dout) >> 4) & 0xF));
    vbdHex(1, (int((top->dout)) & 0xF));

    vbdCycle(cycle + 1); //increments Vbuddy cycle 
}

void vbd_plot(Vsinegen* top, int en) {
    //++++ plot count value on Vbuddy TFT (y, min, max)
    if (en == 1) {
        vbdPlot(int(top->dout), 0, 255);
    }
}

void close_vbd() {
    vbdClose();
}