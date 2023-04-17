#ifndef _ADDER_H_
#define _ADDER_H_

#include <iostream>
using namespace std;

#include <systemc>
using namespace sc_dt;
using namespace sc_core;


class adder : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<float> i_signal;
  sc_fifo_out<float> o_result;

  void do_add() { //decimation filter
    while (true) {
        //index = y_signal.read();

        a = i_signal.read();
        b = i_signal.read();
        c = i_signal.read();
        // wait();
        sum = c*(1.0/2.0) + b*(1.0/3.0) + a*(1.0/6.0);
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
  float a;
  float b;
  float c;
  float sum;

 
};

#endif
