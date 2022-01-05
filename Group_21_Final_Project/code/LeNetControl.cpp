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

  clock_cycle = 0;
  stage = 0;
  stage_in = 0;
  stage_out = 0;
  count = 0;

  for (int i = 0; i < 16; i++)
   for (int j = 0; j < 64; j++)
    temp_data[i][j] = 0;
 }
 else {
  if (clock_cycle >= 22666 && clock_cycle <= 22666)
   cout << "\nclock cycle = " << clock_cycle << endl;

  /* =============== 1st Conv and 1st Pool =============== */
  if (clock_cycle <= 4889) {
   if (clock_cycle == (0 + 815 * stage)) {
    rom_addr.write(1 + 26 * stage);

    conv_0_rst.write(false);
   }
   else if ((clock_cycle >= (1 + 815 * stage)) && (clock_cycle <= (814 + 815 * stage))) {
    if (clock_cycle <= (24 + 815 * stage))
     rom_addr.write(clock_cycle + 1 - 815 * stage + 26 * stage);
    else if (clock_cycle <= (808 + 815 * stage))
     rom_addr.write(clock_cycle + 44426 - 25 - 815 * stage);

    if (clock_cycle <= (810 + 815 * stage)) {
     conv_0_data_in.write(rom_data_out.read());

     //cout << "transfer data to Conv = " << rom_data_out.read() << endl;
    }

    if (clock_cycle == (143 + 815 * stage))
     pool_0_rst.write(false);

    else if (clock_cycle >= (144 + 815 * stage)) {
     if (clock_cycle <= (812 + 815 * stage)) {
      //cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

      if (conv_0_data_out.read() >= 0) {
       pool_0_data_in.write(conv_0_data_out.read());

       //cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
      }
      else
       pool_0_data_in.write(-1);
     }
     else if (clock_cycle == (813 + 815 * stage)) {
      conv_0_rst.write(true);
      conv_0_data_in.write(-1);

      //cout << "reset conv unit" << endl;
     }
    }

    if (clock_cycle == (173 + 815 * stage)) {
     ram_wr.write(0);
     if (stage == 0)
      ram_addr.write(0);
    }
    if (clock_cycle >= (174 + 815 * stage)) {
     if (pool_0_data_out.read() >= 0) {
      //cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

      //cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

      ram_data_in.write(pool_0_data_out.read());

      ram_addr.write(ram_addr.read() + 1);

      if (clock_cycle == (814 + 815 * stage)) {
       ram_wr.write(1);

       pool_0_rst.write(true);
       pool_0_data_in.write(-1);

       //cout << "reset pool unit" << endl;
       stage++;

       rom_addr.write(0 + 26 * stage);
      }
     }
    }
   }
  }

  /* =============== 2nd Conv =============== */
  else if (clock_cycle >= 4890 && clock_cycle <= 21592) {
   if (stage_out < 16) {
    if (stage_in < 6) {
     //cout << "\n*************************************" << endl;
     //cout << "\nCurrent stage = [ " << stage_out << ", " << stage_in << " ]" << endl;

     if (clock_cycle == (4890 + 174 * stage_in + 6 * 174 * stage_out)) {
      count = 0;

      rom_addr.write(157 + 25 * stage_in + 6 * 25 * stage_out + stage_out);
      ram_wr.write(1);

      conv_0_rst.write(false);

      if (clock_cycle == 4890 + 174 * stage_in + 6 * 174 * stage_out) {
       conv_0_data_size.write(12);
      }
     }
     else if ((clock_cycle >= (1 + 4890 + 174 * stage_in + 6 * 174 * stage_out))
      && (clock_cycle <= (814 - 640 + 4890 + 174 * stage_in + 6 * 174 * stage_out))) {
      if (clock_cycle <= (23 + 4890 + 174 * stage_in + 6 * 174 * stage_out))
       rom_addr.write(clock_cycle - 4890 - 174 * stage_in - 6 * 174 * stage_out
        + 157 + 25 * stage_in
        + 25 * 6 * stage_out + stage_out);

      else if (clock_cycle >= (25 + 4890 + 174 * stage_in + 6 * 174 * stage_out)
       && clock_cycle <= (808 - 640 + 4890 + 174 * stage_in + 6 * 174 * stage_out))
       ram_addr.write(clock_cycle - 25 - 4890 - 174 * stage_in - 6 * 174 * stage_out);

      // After calculate 6 kernel * data fetch bias
      if (stage_in == 5) {
       if (clock_cycle == (23 + 4890 + 174 * stage_in + 6 * 174 * stage_out + 1)) {
        rom_addr.write(clock_cycle - 4890 - 174 * stage_in - 6 * 174 * stage_out
         + 157 + 25 * stage_in
         + 25 * 6 * stage_out + stage_out);
       }
       else if (clock_cycle == (23 + 4890 + 174 * stage_in + 6 * 174 * stage_out + 1 + 2)) {
        temp_bias = rom_data_out.read();

        //cout << "\n==========================\nconv2 bias = " << temp_bias << endl << endl;
       }
      }

      if (clock_cycle <= (25 + 4890 + 174 * stage_in + 6 * 174 * stage_out)) {
       conv_0_data_in.write(rom_data_out.read());

       //cout << "transfer data to Conv = " << rom_data_out.read() << endl;
      }
      else if (clock_cycle == (26 + 4890 + 174 * stage_in + 6 * 174 * stage_out)) {
       conv_0_data_in.write(0);

       //cout << "transfer data to Conv = 0" << endl;
      }
      else if (clock_cycle <= (810 - 640 + 4890 + 174 * stage_in + 6 * 174 * stage_out)) {
       conv_0_data_in.write(ram_data_out.read());

       //cout << "transfer data to Conv = " << ram_data_out.read() << endl;
      }

      if (clock_cycle >= (79 + 4890 + 174 * stage_in + 6 * 174 * stage_out)) {
       if (clock_cycle <= (812 - 640 + 4890 + 174 * stage_in + 6 * 174 * stage_out)) {
        //if (conv_0_data_out.read() >= 0)
         //cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

        if (conv_0_data_out.read() >= 0) {
         temp_data[stage_out][count] += conv_0_data_out.read();

         if (stage_in == 5) {
          temp_data[stage_out][count] += temp_bias;
         }

         //cout << "bias = " << temp_bias << endl;

         //cout << "data[ " << count << " ] = " << temp_data[count] << endl;

         count++;
        }
       }
      }

      if (clock_cycle == (814 - 640 + 4890 + 174 * stage_in + 6 * 174 * stage_out - 2)) {
       conv_0_rst.write(true);

       //cout << "reset conv unit" << endl;

       rom_addr.write(rom_addr.read() + 1);

       stage_in++;
      }
     }
    }
    else {
     stage_in = 0;

     stage_out++;
    }
   }
  }

  /* =============== 2nd Pool =============== */
  else if (clock_cycle == 21593) {
   stage = 0;
   count = 0;

   pool_0_data_size.write(8);

   ram_wr.write(0);
  }
  else if (clock_cycle >= 21594 && clock_cycle <= 22665) {
   if (stage < 16) {
    if (clock_cycle == (21594 + stage * 67)) {
     count = 0;

     ram_addr.write(0 + stage);

     pool_0_rst.write(false);
    }
    else if ((clock_cycle >= 21595 + stage * 67) && (clock_cycle <= 21595 + 65 + stage * 67)) {
     if (clock_cycle <= 21595 + 63 + stage * 67)
      pool_0_data_in.write(temp_data[stage][clock_cycle - 21595 - stage * 67]);

     if (pool_0_data_out.read() >= 0) {
      //cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

      ram_data_in.write(pool_0_data_out.read());

      ram_addr.write(stage + 16 * count);

      count++;
     }

     if (clock_cycle == 21595 + 65 + stage * 67) {
      pool_0_rst.write(true);
      pool_0_data_in.write(-1);

      cout << "reset pool unit" << endl;

      stage++;
     }
    }
   }
  }

  /* =============== 1st Dense ============== */
  else if (clock_cycle == 22666) {
   dens_0_data_size.write(256);
   dens_0_rst.write(false);

   ram_wr.write(1);
   ram_addr.write(0);

   rom_rd.write(true);
   rom_addr.write(2572);

   count = 0;
  }
  else if (clock_cycle >= 22667 && clock_cycle <= 22667 + 255 + 30840 + 2) {
   if (clock_cycle <= 22667 + 254)
    ram_addr.write(ram_addr.read() + 1);
   if (clock_cycle > 22667 + 254 && clock_cycle <= 22667 + 254 + 30840) {
    rom_addr.write(rom_addr.read() + 1);
   }

   if (clock_cycle <= 22667 + 255) {
    //cout << "Recieve data from ram = " << ram_data_out.read() << endl;

    dens_0_data_in.write(ram_data_out.read());

    if (clock_cycle == 22667 + 255) {
     ram_wr.write(0);
     ram_addr.write(0);
    }
   }
   else if (clock_cycle <= 22667 + 255 + 30840) {
    //cout << "Recieve data from ram = " << rom_data_out.read() << endl;

    dens_0_data_in.write(rom_data_out.read());
   }

   if (dens_0_data_out.read() >= 0) {
    //cout << "recieve data from dense = " << dens_0_data_out.read() << endl;

    ram_data_in.write(dens_0_data_out.read());

    ram_addr.write(count);

    //cout << "data[ " << count << " ] = " << dens_0_data_out.read() << endl;

    if (count == 119) {
     dens_0_rst.write(true);

     dens_0_data_in.write(-1);
    }

    if (clock_cycle == 22667 + 255 + 30840 + 2) {
     ram_wr.write(1);
    }
    count++;
   }
  }

  /* =============== 2nd Dense ============== */
  else if (clock_cycle == 53765) {
   dens_0_data_size.write(120);
   dens_0_rst.write(false);

   ram_wr.write(1);
   ram_addr.write(0);

   rom_rd.write(true);
   rom_addr.write(33412);

   count = 0;
  }
  else if (clock_cycle >= 53766 && clock_cycle <= 53766 + 119 + 10164 + 2) {
   if (clock_cycle <= 53766 + 119)
    ram_addr.write(ram_addr.read() + 1);
   if (clock_cycle > 53766 + 118 && clock_cycle <= 53766 + 119 + 10164) {
    rom_addr.write(rom_addr.read() + 1);
   }

   if (clock_cycle <= 53766 + 119) {
    //cout << "Recieve data from ram = " << ram_data_out.read() << endl;

    dens_0_data_in.write(ram_data_out.read());

    if (clock_cycle == 53766 + 119) {
     ram_wr.write(0);
     ram_addr.write(0);
    }
   }
   else if (clock_cycle <= 53766 + 119 + 10164) {
    //cout << "Recieve data from ram = " << rom_data_out.read() << endl;

    dens_0_data_in.write(rom_data_out.read());
   }

   if (dens_0_data_out.read() >= 0) {
    cout << "recieve data from dense = " << dens_0_data_out.read() << endl;

    ram_data_in.write(dens_0_data_out.read());

    ram_addr.write(count);

    cout << "data[ " << count << " ] = " << dens_0_data_out.read() << endl;

    if (count == 83) {
     dens_0_rst.write(true);

     dens_0_data_in.write(-1);
    }

    count++;
   }
   if (clock_cycle == 53766 + 119 + 10164 + 2) {
    ram_wr.write(1);
   }
  }

  /* =============== 3rd Dense ============== */
  else if (clock_cycle == 64051) {
  dens_0_data_size.write(84);
  dens_0_rst.write(false);

  ram_wr.write(1);
  ram_addr.write(0);

  rom_rd.write(true);
  rom_addr.write(43576);

  count = 0;
  }
  else if (clock_cycle >= 64052 && clock_cycle <= 64052 + 83 + 850 + 2) {
  if (clock_cycle <= 64052 + 83)
   ram_addr.write(ram_addr.read() + 1);
  if (clock_cycle > 64052 + 83 && clock_cycle <= 64052 + 83 + 850) {
   rom_addr.write(rom_addr.read() + 1);
  }

  if (clock_cycle <= 64052 + 83) {
   //cout << "Recieve data from ram = " << ram_data_out.read() << endl;

   dens_0_data_in.write(ram_data_out.read());

   if (clock_cycle == 64052 + 83) {
    ram_wr.write(0);
    ram_addr.write(0);
   }
  }
  else if (clock_cycle <= 64052 + 83 + 850) {
   //cout << "Recieve data from ram = " << rom_data_out.read() << endl;

   dens_0_data_in.write(rom_data_out.read());
  }

  if (dens_0_data_out.read() != -1) {
   cout << "recieve data from dense = " << dens_0_data_out.read() << endl;

   //cout << "data[ " << count << " ] = " << dens_0_data_out.read() << endl;

   if (count == 9) {
    dens_0_rst.write(true);

    dens_0_data_in.write(-1);
   }

   if (clock_cycle == 64052 + 83 + 850 + 2) {
    ram_wr.write(1);
   }
   count++;
  }
  }

  clock_cycle++;
 }
}