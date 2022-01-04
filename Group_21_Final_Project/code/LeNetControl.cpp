#include "LeNetControl.h"

void Control::control_run() {
 if (rst.read()) {
  rom_rd.write(true);
  rom_addr.write(0);

  ram_wr.write(1);
  ram_addr.write(0);
  ram_data_in.write(0);

  result.write(0);
  output_valid.write(false);

  // connect to Conv Submodule 0
  conv_0_data_in.write(-1);
  conv_0_data_size.write(28);
  conv_0_rst.write(true);

  // connect to Pooling Submodule 0
  pool_0_data_in.write(-1);
  pool_0_data_size.write(24);
  pool_0_rst.write(true);

  // connect to Dense Submodule 0
  dens_0_data_in.write(-1);
  dens_0_data_size.write(256);
  dens_0_rst.write(true);

  // connect to Conv Submodule 1
  conv_1_data_in.write(-1);
  conv_1_data_size.write(12);
  conv_1_rst.write(true);

  clock_cycle = 0;
  stage = 0;
 }
 else {
  if (clock_cycle <= 4889)
   cout << "\nclock cycle = " << clock_cycle << endl;

  /* =============== 1st Conv =============== */
  if (clock_cycle <= 4889) {
   if (clock_cycle == (0 + 815 * stage)) {
    rom_addr.write(1);

    conv_0_rst.write(false);
   }
   else if ((clock_cycle >= (1 + 815 * stage)) && (clock_cycle <= (814 + 815 * stage))) {
    if (clock_cycle <= (24 + 815 * stage))
     rom_addr.write(clock_cycle + 1 - 815 * stage + 26 * stage);
    else if (clock_cycle <= (808 + 815 * stage))
     rom_addr.write(clock_cycle + 44426 - 25 - 815 * stage);

    if (clock_cycle <= (810 + 815 * stage)) {
     conv_0_data_in.write(rom_data_out.read());

     cout << "transfer data to Conv = " << rom_data_out.read() << endl;
    }

    if (clock_cycle == (143 + 815 * stage))
     pool_0_rst.write(false);
    else if (clock_cycle >= (144 + 815 * stage)) {
     if (clock_cycle <= (812 + 815 * stage)) {
      cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

      if (conv_0_data_out.read() >= 0) {
       pool_0_data_in.write(conv_0_data_out.read());

       cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
      }
      else
       pool_0_data_in.write(-1);
     }
     else if (clock_cycle == (813 + 815 * stage)) {
      conv_0_rst.write(true);
      conv_0_data_in.write(-1);

      cout << "reset conv unit" << endl;
     }
    }

    if (clock_cycle == (173 + 815 * stage)) {
     ram_wr.write(0);
     if (stage == 0)
      ram_addr.write(0);
    }
    if (clock_cycle >= (174 + 815 * stage)) {
     if (pool_0_data_out.read() >= 0) {
      cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

      cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

      ram_data_in.write(pool_0_data_out.read());

      ram_addr.write(ram_addr.read() + 1);

      if (clock_cycle == (814 + 815 * stage)) {
       ram_wr.write(1);

       pool_0_rst.write(true);
       pool_0_data_in.write(-1);

       cout << "reset pool unit" << endl;

       stage++;
      }
     }
    }
   }
   clock_cycle++;
  }
  /* =============== 2st Conv =============== */
  if (stage_outside <= 15) {
   if (stage_inside <= 5) {
    if (stage_inside == 0)
     ram_wr.write(true);

    if (clock_cycle >= (1000 + stage_inside * 1169) && clock_cycle <= (1168 + stage * 1169)) {
     if (clock_cycle == (1000 + stage_inside * 1169))
      ram_addr.write(0);
     else if (clock_cycle >= (1001 + stage_inside * 1169) && clock_cycle <= (1143 + stage * 1169)) {
      ram_addr.write(clock_cycle - 1000 - stage_outside * 2014);
      conv_1_data_in.write(ram_data_out.read());
     }
     else if (clock_cycle >= (1144 + stage_inside * 1169) && clock_cycle <= (1168 + stage_inside * 1169))
      if (clock_cycle == 1144 + stage_inside * 1169)
       rom_addr.write(clock_cycle - stage_inside * 1169 - 988 + stage_inside * 25);
      else if (clock_cycle >= (1145 + stage_inside * 1169) && clock_cycle <= (1168 + stage_inside * 1169)) {
       rom_addr.write(clock_cycle - stage_inside * 1169 - 988 + stage_inside * 25);
       conv_1_data_in.write(rom_data_out.read());
      }
     stage_inside++;

    }
    if (clock_cycle == (2013 + stage_outside * 2014))
     rom_addr.write(clock_cycle - stage_outside * 2014 + 2013 * stage_outside);
    else if (clock_cycle == (2014 + stage_outside * 2014))
     conv_1_data_in.write(rom_data_out.read());

    stage_outside++;



   }


  }
 }
}