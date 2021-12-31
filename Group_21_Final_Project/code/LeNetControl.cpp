#include "LeNetControl.h"

void Control::control_run() {
 if (rst.read()) {
  rom_rd.write(true);
  rom_addr.write(0);

  ram_wr.write(false);
  ram_addr.write(0);
  ram_data_in.write(0);

  result.write(0);
  output_valid.write(false);

  // connect to Conv Submodule 0
  conv_0_data_in.write(0);
  conv_0_data_size.write(28);
  conv_0_rst.write(true);

  // connect to Pooling Submodule 0
  pool_0_data_in.write(0);
  pool_0_data_size.write(24);
  pool_0_rst.write(true);

  // connect to Dense Submodule 0
  dens_0_data_in.write(0);
  dens_0_data_size.write(256);
  dens_0_rst.write(true);

  clock_cycle = 0;
 }
 else {
  if (clock_cycle <= 808)
   cout << "clock cycle = " << clock_cycle << endl;

  if (clock_cycle == 0) {
   rom_addr.write(1);

   conv_0_rst.write(false);
  }
  else if (clock_cycle >= 1 && clock_cycle <= 810) {

   if (clock_cycle <= 24)
    rom_addr.write(clock_cycle + 1);
   else if (clock_cycle <= 808)
    rom_addr.write(clock_cycle + 44426 - 25);

   conv_0_data_in.write(rom_data_out.read());

   cout << "transfer data = " << rom_data_out.read() << endl;
  }
  clock_cycle++;
 }
}