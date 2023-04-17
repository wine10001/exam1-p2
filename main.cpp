#include "stim.h"
#define CLOCK_PERIOD 1.0

int sc_main(int argc, char *argv[]) {
  
  //Create modules and signals
  stim testbench("testbench");
  adder filter("filter", 1);
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");

  //Create FIFO channels
  sc_fifo<float> signal;
  sc_fifo<float> result;

  //Connect FIFO channels with modules
  testbench.i_clk(clk);
  testbench.o_rst(rst);
  filter.i_clk(clk);
  filter.i_rst(rst);

  testbench.o_signal(signal);
  testbench.i_result(result);
  filter.i_signal(signal);
  filter.o_result(result);

  sc_start(64, SC_NS);
  return 0;
}
