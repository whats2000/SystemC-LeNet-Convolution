#include "RAM.h"

void RAM::read_data() {
 if (wr.read())
  data_out = mem[addr.read()];

 //cout << "Reading data[" << addr.read() << "] = " << mem[addr.read()] << endl;
}

void RAM::write_data() {
 if (!wr.read())
  mem[addr.read()] = data_in;

 //cout << "Writing data[" << addr.read() << "] = " << mem[addr.read()] << endl;
}
