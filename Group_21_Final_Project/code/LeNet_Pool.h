#include "systemc.h"
#include "define.h"
#include <iostream>

using namespace std;

SC_MODULE(Pool) {
 sc_in_clk clk;
 sc_in < bool > rst;

 sc_out < DATA_TYPE > data_out;
 sc_in < DATA_TYPE > data_in;

 void run();

 SC_CTOR(Pool)
 {
  SC_METHOD(run);
  sensitive << clk.pos();
 }
};
