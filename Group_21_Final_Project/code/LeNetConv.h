#include "systemc.h"
#include "define.h"
#include <iostream>

using namespace std;

SC_MODULE(Conv) {
 sc_in_clk clk;
 sc_in < bool > rst;

 sc_out < DATA_TYPE > data_out;
 sc_in < DATA_TYPE > data_in;
 sc_in < int > data_size;

 int clock_cycle = 0;
 int size = 0;

 DATA_TYPE temp_sum = 0;
 DATA_TYPE bias = 0;
 DATA_TYPE kernel[25] = {};
 DATA_TYPE data[140] = {};

 void conv_run();

 SC_CTOR(Conv)
 {
  SC_METHOD(conv_run);
  sensitive << clk.pos();
 }
};
