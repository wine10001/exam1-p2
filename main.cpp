#include "stim.h"
#define CLOCK_PERIOD 1.0

int sc_main(int argc, char *argv[]) {
  
  //Create modules and signals
  stim testbench("testbench");
  adder dut("dut", 1);
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");

  //Create FIFO channels
  sc_fifo<float> fifo_x_s;
  sc_fifo<float> fifo_y_i;
  sc_fifo<float> fifo_result;

  //Connect FIFO channels with modules
  testbench.i_clk(clk);
  testbench.o_rst(rst);
  dut.i_clk(clk);
  dut.i_rst(rst);
  testbench.o_n(fifo_x_s);
  testbench.y_n(fifo_y_i);
  testbench.i_result(fifo_result);
  dut.i_n_port(fifo_x_s);
  dut.y_n_port(fifo_y_i);
  dut.o_result(fifo_result);

  sc_start(64, SC_NS);
  return 0;
}
