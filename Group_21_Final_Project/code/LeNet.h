#include "systemc.h"
#include "define.h"
#include "LeNet_Control.h"
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

 Control* Control_0;

 void run();

 SC_CTOR(LeNet)
 {
  Control_0 = new Control("Control_0");
  Control_0->clk(clk);
  Control_0->rst(rst);

  Control_0->rom_rd(rom_rd);
  Control_0->rom_addr(rom_addr);
  Control_0->rom_data_out(rom_data_out);

  Control_0->ram_wr(ram_wr);
  Control_0->ram_addr(ram_addr);
  Control_0->ram_data_out(ram_data_out);
  Control_0->ram_data_in(ram_data_in);

  Control_0->result(result);
  Control_0->output_valid(output_valid);

  SC_METHOD(run);
  sensitive << clk.pos();
 }
};
// ^^^^^ put your code here ^^^^^
