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
 sc_signal < DATA_TYPE > conv_0_data_out;
 sc_signal < DATA_TYPE > conv_0_data_in;
 sc_signal < int > conv_0_data_size;
 sc_signal < bool > conv_0_rst;

 // connect to Pooling Submodule 0
 sc_signal < DATA_TYPE > pool_0_data_out;
 sc_signal < DATA_TYPE > pool_0_data_in;
 sc_signal < int > pool_0_data_size;
 sc_signal < bool > pool_0_rst;

 // connect to Dense Submodule 0
 sc_signal < DATA_TYPE > dens_0_data_out;
 sc_signal < DATA_TYPE > dens_0_data_in;
 sc_signal < int > dens_0_data_size;
 sc_signal < bool > dens_0_rst;

 Conv* Conv0;
 Pool* Pool0;
 Dens* Dens0;

 int clock_cycle = 0;
 int stage = 0;

 void control_run();

 SC_CTOR(Control)
 {
  Conv0 = new Conv("Conv_0");
  Conv0->clk(clk);
  Conv0->rst(conv_0_rst);
  Conv0->data_out(conv_0_data_out);
  Conv0->data_in(conv_0_data_in);
  Conv0->data_size(conv_0_data_size);

  Pool0 = new Pool("Pool_0");
  Pool0->clk(clk);
  Pool0->rst(pool_0_rst);
  Pool0->data_out(pool_0_data_out);
  Pool0->data_in(pool_0_data_in);
  Pool0->data_size(pool_0_data_size);

  Dens0 = new Dens("Dens_0");
  Dens0->clk(clk);
  Dens0->rst(dens_0_rst);
  Dens0->data_out(dens_0_data_out);
  Dens0->data_in(dens_0_data_in);
  Dens0->data_size(dens_0_data_size);

  SC_METHOD(control_run);
  sensitive << clk.pos();

  dont_initialize();
 }
};
