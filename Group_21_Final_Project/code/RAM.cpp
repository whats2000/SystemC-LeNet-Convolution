#include "RAM.h"

void RAM::read_data() {
	if ( wr.read() )
		data_out = mem[addr.read()];
}

void RAM::write_data() {
	if ( !wr.read() )
		mem[addr.read()] = data_in;
}



