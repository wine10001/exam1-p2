#include "stim.h"
#define CLOCK_PERIOD 1.0

int sc_main(int argc, char *argv[]) {
  
  //Create modules and signals
  stim testbench("testbench");
  adder dut("dut", 1);
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");

  //Create FIFO channels
  sc_fifo<float> x;
  sc_fifo<float> y;
  sc_fifo<float> result;

  //Connect FIFO channels with modules
  testbench.i_clk(clk);
  testbench.o_rst(rst);
  dut.i_clk(clk);
  dut.i_rst(rst);
  testbench.x(x);
  testbench.y(y);
  testbench.i_result(result);
  dut.i_n_port(x);
  dut.y_n_port(y);
  dut.o_result(result);

  sc_start(64, SC_NS);
  return 0;
}
