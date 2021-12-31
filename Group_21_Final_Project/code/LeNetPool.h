#include "systemc.h"
#include "define.h"
#include <iostream>

using namespace std;

SC_MODULE(Pool) {
 sc_in_clk clk;
 sc_in < bool > rst;

 sc_out < DATA_TYPE > data_out;
 sc_in < DATA_TYPE > data_in;
 sc_in < int > data_size;

 int clock_cycle = 0;
 DATA_TYPE temp_max = 0;

 DATA_TYPE data[24][24] = {};

 void pool_run();

 SC_CTOR(Pool)
 {
  SC_METHOD(pool_run);
  sensitive << clk.pos();

  dont_initialize();
 }
};
