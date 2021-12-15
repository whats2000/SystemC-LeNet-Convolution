#include "systemc.h"
#include "define.h"
#include <iostream>

using namespace std;

// vvvvv put your code here vvvvv
SC_MODULE( LeNet ) {	
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
	
	void run();
	
	SC_CTOR( LeNet )
	{
		
	}
};
// ^^^^^ put your code here ^^^^^
