#ifndef _STIM_H_
#define _STIM_H_

#include <iomanip>
using std::setw;
#include "adder.h"
using namespace std;
// WIDTH is defined in adder.h
const int DEPTH = (1 << WIDTH);

const float x_input_signal[] = {0.500,   0.525,   0.549,   0.574,   0.598,   0.622,   0.646,   0.670,
                            0.693,   0.715,   0.737,   0.759,   0.780,   0.800,   0.819,   0.838,
                            0.856,   0.873,   0.889,   0.904,   0.918,   0.931,   0.943,   0.954,
                            0.964,   0.972,   0.980,   0.986,   0.991,   0.995,   0.998,   1.000,
                            1.000,   0.999,   0.997,   0.994,   0.989,   0.983,   0.976,   0.968,
                            0.959,   0.949,   0.937,   0.925,   0.911,   0.896,   0.881,   0.864,
                            0.847,   0.829,   0.810,   0.790,   0.769,   0.748,   0.726,   0.704,
                            0.681,   0.658,   0.634,   0.610,   0.586,   0.562,   0.537,   0.512,
                            0.488,   0.463,   0.438,   0.414,   0.390,   0.366,   0.342,   0.319,
                            0.296,   0.274,   0.252,   0.231,   0.210,   0.190,   0.171,   0.153,
                            0.136,   0.119,   0.104,   0.089,   0.075,   0.063,   0.051,   0.041,
                            0.032,   0.024,   0.017,   0.011,   0.006,   0.003,   0.001,   0.000,
                            0.000,   0.002,   0.005,   0.009,   0.014,   0.020,   0.028,   0.036,
                            0.046,   0.057,   0.069,   0.082,   0.096,   0.111,   0.127,   0.144,
                            0.162,   0.181,   0.200,   0.220,   0.241,   0.263,   0.285,   0.307,
                            0.330,   0.354,   0.378,   0.402,   0.426,   0.451,   0.475,   0.500};

SC_MODULE(stim) {

  sc_in_clk i_clk;
  sc_out<bool> o_rst;
  sc_fifo_out<float> x; //output of x signal
  sc_fifo_out<float> y; //output of y index
  sc_fifo_in<float> i_result; //input of sampled result
  float t_sum;

  int index = 0;
  void stim_gen() {
    
    for (int a = 0; a < 64; a++) {
      y.write(a);
        for (int k = 0; k < 3; k++) {
          index = a*2-k+1;
          if (index < 0) {
            x.write(0);
          } else {
            x.write(x_input_signal[index]);
            // cout << x_input_signal[index] << endl;
          }
      }
      wait();
      }
      
    }
  

  void sink() {

    
    while (true) {
      t_sum=i_result.read();
      cout << setw(12) << sc_time_stamp();
      cout << setw(12) <<  std::to_string(t_sum) << endl;
      wait();
    }
  }



  SC_CTOR(stim) {
    SC_THREAD(stim_gen);
    sensitive << i_clk.pos();
    dont_initialize();

    SC_THREAD(sink);
    sensitive << i_clk.pos();

 
  }
};

#endif
