#include "Vsinegen.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "dual_tb_header.hpp"

int main(int argc, char **argv, char **en) {
    int i; //counts the number of clock cycles

    Verilated::commandArgs(argc, argv);

    //init sinegen verilog instance
    Vsinegen* top = new Vsinegen;

    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC; //trace file pointer (for the trace dump)
    top->trace(tfp, 99);
    tfp->open("sinegen.vcd");

    //init Vbuddy
    if (init_vbd() == -1) return (-1);

    //init simulation inputs
    top->clk = 1;
    top->incr = 4;
    top->rst = 0;

    //run simulation for 300 clock cycles
    for (i=0; i<1000000; ++i) {
        //inputs change BEFORE clock is toggled and i starts at 0
        //so i=n indicates the start of the (n+1)th cycle 

        top->en = vbdFlag();
        top->offset = vbdValue();

        toggle_clk(top, tfp, i);    //function that dumps variables into VSC file and toggles clock
        vbd_plot(top, top->en);

        if(Verilated::gotFinish() || vbdGetkey() == 'q') exit(0);
    }

    tfp->close();
    close_vbd();
    exit(0);
}