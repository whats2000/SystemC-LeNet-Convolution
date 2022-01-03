#include "systemc.h"
#include "define.h"
#include <iostream>

using namespace std;

SC_MODULE(Dens) {
 sc_in_clk clk;
 sc_in < bool > rst;

 sc_out < DATA_TYPE > data_out;
 sc_in < DATA_TYPE > data_in;
 sc_in < int > data_size;

 int kernel_count = 0;
 int clock_dens = 0;
 int stage = 0;

 DATA_TYPE temp_sum = 0;
 DATA_TYPE data[256] = {};

 void dens_run();

 SC_CTOR(Dens)
 {
  SC_METHOD(dens_run);
  sensitive << clk.pos();

  dont_initialize();
 }
};
