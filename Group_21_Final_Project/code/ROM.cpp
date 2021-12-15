#include "ROM.h"

void ROM::read_data() {	
	if ( ird.read() )
		data_out = mem[addr.read()];
}



