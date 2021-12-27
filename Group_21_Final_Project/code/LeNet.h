#include "systemc.h"
#include "define.h"
#include "LeNet_Conv.h"
#include "LeNet_Dens.h"
#include "LeNet_Pool.h"
#include <iostream>

using namespace std;

// vvvvv put your code here vvvvv
SC_MODULE(LeNet) {
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

 // connect to Conv Submodule
 sc_in < DATA_TYPE > conv_data_out;
 sc_out < DATA_TYPE > conv_data_in;

 // connect to Pooling Submodule
 sc_in < DATA_TYPE > pool_data_out;
 sc_out < DATA_TYPE > pool_data_in;

 // connect to Dense Submodule
 sc_in < DATA_TYPE > dens_data_out;
 sc_out < DATA_TYPE > dens_data_in;

 void run();

 SC_CTOR(LeNet)
 {
  SC_METHOD(run);
  sensitive << clk.pos();
 }
};
// ^^^^^ put your code here ^^^^^
