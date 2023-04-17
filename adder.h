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
        _y_index = y_n_port.read();

        _i_a = i_n_port.read();
        _i_b = i_n_port.read();
        _i_c = i_n_port.read();
        // wait();
        _o_sum = _i_a*(1.0/6.0) + _i_b*(1.0/3.0) + _i_c*(1.0/2.0);
        o_result.write(_o_sum);
        // cout << _y_index << " " << _i_a << " " << _i_b << " " << _i_c << " " << _o_sum << endl;
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
  int _y_index;
  float _i_a;
  float _i_b;
  float _i_c;
  float _o_sum;

 
};

#endif
