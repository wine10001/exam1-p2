#ifndef _ADDER_H_
#define _ADDER_H_

#include <iostream>
using namespace std;

#include <systemc>
using namespace sc_dt;
using namespace sc_core;

const int WIDTH = 2;

class adder : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<float> i_n_port;
  sc_fifo_in<float> y_n_port;
  sc_fifo_out<float> o_result;

  void do_add() { //decimation filter
    while (true) {
        index = y_n_port.read();

        a = i_n_port.read();
        b = i_n_port.read();
        c = i_n_port.read();
        // wait();
        sum = a*(1.0/6.0) + b*(1.0/3.0) + c*(1.0/2.0);
        o_result.write(sum);
        wait();
    }
  }

  SC_HAS_PROCESS(adder);
  adder(sc_module_name name, int i) : id(i) { 
    SC_THREAD(do_add);  
    sensitive << i_clk.pos();
    dont_initialize();
  }


private:
  const int id;
  int index;
  float a;
  float b;
  float c;
  float sum;

 
};

#endif
