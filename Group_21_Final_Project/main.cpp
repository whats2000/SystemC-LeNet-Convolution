#include <iostream>
#include <systemc.h>
#include "code/define.h"
#include "code/LeNet.h"
#include "code/ROM.h"
#include "code/RAM.h"
#include "code/Monitor.h"
#include "code/clockreset.h"

using namespace std;

int sc_main(int argc, char* argv[]) {
 sc_signal < bool > clk;
 sc_signal < bool > rst;

 sc_signal < bool > rom_rd;
 sc_signal < sc_uint<16> > rom_addr;
 sc_signal < DATA_TYPE > rom_data_out;
 
 sc_signal < bool > ram_wr;
 sc_signal < sc_uint<16> > ram_addr;
 sc_signal < DATA_TYPE > ram_data_out;
 sc_signal < DATA_TYPE > ram_data_in;

 sc_signal < bool > out_valid;
 sc_signal < DATA_TYPE > result;

 Reset m_Reset("m_Reset", 10);
 Clock m_Clock("m_Clock", 5, 1000);
 ROM m_ROM("m_ROM");
 RAM m_RAM("m_RAM");
 LeNet m_LeNet("m_LeNet");
 Monitor m_Monitor("m_Monitor");

 m_Reset(rst);
 m_Clock(clk);
 m_ROM(clk, rom_rd, rom_addr, rom_data_out);
 m_RAM(clk, ram_wr, ram_addr, ram_data_out, ram_data_in);
 m_LeNet(clk, rst,rom_rd, rom_addr, rom_data_out, ram_wr, 
         ram_addr, ram_data_out, ram_data_in, result, out_valid
        );
 m_Monitor(clk, rst, result, out_valid);

 sc_start(1000, SC_NS);

 return 0;
}
