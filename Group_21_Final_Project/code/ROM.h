﻿#include "systemc.h"
#include "define.h"
#include <iostream>
#include <fstream>

using namespace std;

SC_MODULE(ROM) {
 sc_in_clk clk;
 sc_in < bool > ird;
 sc_in < sc_uint<16> > addr;
 sc_out < DATA_TYPE > data_out;

 vector < DATA_TYPE > mem;
 void read_data();

 SC_CTOR(ROM)
 {
  string t_b, t_c;
  DATA_TYPE t_d;
  ifstream win;

  mem.resize(45210);

  cout << "Loading weights and input data...\n";
  // vvvvv change the path of input file here vvvvv
  win.open("code\\LeNet_All_b.txt");
  for (int i = 0; i < 45210; i++) {
   win >> t_b >> t_c >> t_d;

#ifdef fixed_DATA_TYPE
   READ_DATA_TYPE temp;
   temp = t_b.c_str();
   mem[i] = temp.to_int();
#else
   mem[i] = t_d;
#endif

   //cout << "mem[ " << i << " ] = " << mem[i] << endl;
  }

  win.close();
  cout << "done!\n";

  //  for (int i = 0; i < 45210; i++)
  //   cout << "mem[ "<< i << " ] = " << mem[i] << endl;

  SC_METHOD(read_data);
  sensitive << clk.pos();
 }
};
