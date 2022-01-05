#include "systemc.h"
#include "define.h"
#include "LeNetConv.h"
#include "LeNetDens.h"
#include "LeNetPool.h"
#include <iostream>

using namespace std;

SC_MODULE(Control) {
 sc_in_clk clk;
 sc_in < bool > rst;

 sc_out < bool > rom_rd;
 sc_out < sc_uint<16> > rom_addr;
 sc_in < DATA_TYPE > rom_data_out;

 sc_out < bool > ram_wr;
 sc_out < sc_uint<16> > ram_addr;
 sc_in < DATA_TYPE > ram_data_out;
 sc_out < DATA_TYPE > ram_data_in;

 sc_out < DATA_TYPE > result;
 sc_out < bool > output_valid;

 // connect to Conv Submodule 0
 sc_in < DATA_TYPE > conv_0_data_out;
 sc_out < DATA_TYPE > conv_0_data_in;
 sc_out < int > conv_0_data_size;
 sc_out < bool > conv_0_rst;

 // connect to Pooling Submodule 0
 sc_in < DATA_TYPE > pool_0_data_out;
 sc_out < DATA_TYPE > pool_0_data_in;
 sc_out < int > pool_0_data_size;
 sc_out < bool > pool_0_rst;

 // connect to Dense Submodule 0
 sc_in < DATA_TYPE > dens_0_data_out;
 sc_out < DATA_TYPE > dens_0_data_in;
 sc_out < int > dens_0_data_size;
 sc_out < bool > dens_0_rst;

 int clock_cycle = 0;
 int stage = 0;
 int stage_in = 0;
 int stage_out = 0;
 int count = 0;

 DATA_TYPE temp_bias = 0;
 DATA_TYPE temp_data[16][64] = {};
 DATA_TYPE temp_dens_data[120];

 void control_run();

 SC_CTOR(Control)
 {
  SC_METHOD(control_run);
  sensitive << clk.pos();

  dont_initialize();
 }
};
