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
 }
 else {
  if (clock_cycle <= 4889)
   cout << "\nclock cycle = " << clock_cycle << endl;

  /* =============== Conv0_0 =============== */
  if (clock_cycle == 0) {
   rom_addr.write(1);

   conv_0_rst.write(false);
  }
  else if (clock_cycle >= 1 && clock_cycle <= 814) {

   if (clock_cycle <= 24)
    rom_addr.write(clock_cycle + 1);
   else if (clock_cycle <= 808)
    rom_addr.write(clock_cycle + 44426 - 25);

   if (clock_cycle <= 810) {
    conv_0_data_in.write(rom_data_out.read());

    cout << "transfer data to Conv = " << rom_data_out.read() << endl;
   }

   if (clock_cycle == 143)
    pool_0_rst.write(false);
   else if (clock_cycle >= 144) {
    if (clock_cycle <= 812) {
     cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

     if (conv_0_data_out.read() >= 0) {


      pool_0_data_in.write(conv_0_data_out.read());

      cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
     }
     else
      pool_0_data_in.write(-1);
    }
    else if (clock_cycle == 813) {
     conv_0_rst.write(true);
     conv_0_data_in.write(-1);

     cout << "reset conv unit" << endl;
    }
   }
   
   if (clock_cycle == 173) {
    ram_wr.write(true);
    ram_addr.write(0);
   }
   if (clock_cycle >= 174) {
    if (pool_0_data_out.read() >= 0) {
     cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

     cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

     ram_data_in.write(pool_0_data_out.read());

     ram_addr.write(ram_addr.read() + 1);

     if (clock_cycle == 814) {
      ram_wr.write(false);

      pool_0_rst.write(true);
      pool_0_data_in.write(-1);

      cout << "reset pool unit" << endl;
     }
    }
   }
  }

  /* =============== Conv0_1 =============== */
  if (clock_cycle == 815) {
   rom_addr.write(1);

   conv_0_rst.write(false);
  }
  else if (clock_cycle >= 1 + 815 && clock_cycle <= 814 + 815) {

   if (clock_cycle <= 815 + 24)
    rom_addr.write(clock_cycle - 815 + 1 + 26);
   else if (clock_cycle <= 808 + 815)
    rom_addr.write(clock_cycle + 44426 - 25 - 815);

   if (clock_cycle <= 810 + 815) {
    conv_0_data_in.write(rom_data_out.read());

    cout << "transfer data to Conv = " << rom_data_out.read() << endl;
   }

   if (clock_cycle == 143 + 815)
    pool_0_rst.write(false);
   else if (clock_cycle >= 144 + 815) {
    if (clock_cycle <= 812 + 815) {
     cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

     if (conv_0_data_out.read() >= 0) {


      pool_0_data_in.write(conv_0_data_out.read());

      cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
     }
     else
      pool_0_data_in.write(-1);
    }
    else if (clock_cycle == 813 + 815) {
     conv_0_rst.write(true);
     conv_0_data_in.write(-1);

     cout << "reset conv unit" << endl;
    }
   }

   if (clock_cycle == 173 + 815) {
    ram_wr.write(true);
   }
   if (clock_cycle >= 174 + 815) {
    if (pool_0_data_out.read() >= 0) {
     cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

     cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

     ram_data_in.write(pool_0_data_out.read());

     ram_addr.write(ram_addr.read() + 1);

     if (clock_cycle == 814 + 815) {
      ram_wr.write(false);

      pool_0_rst.write(true);
      pool_0_data_in.write(-1);

      cout << "reset pool unit" << endl;
     }
    }
   }
  }

  /* =============== Conv0_2 =============== */
  if (clock_cycle == 1630) {
   rom_addr.write(1);

   conv_0_rst.write(false);
  }
  else if (clock_cycle >= 1 + 1630 && clock_cycle <= 814 + 1630) {

   if (clock_cycle <= 1630 + 24)
    rom_addr.write(clock_cycle + 1 + 26 * 2 - 1630);
   else if (clock_cycle <= 808 + 1630)
    rom_addr.write(clock_cycle + 44426 - 25 - 1630);

   if (clock_cycle <= 810 + 1630) {
    conv_0_data_in.write(rom_data_out.read());

    cout << "transfer data to Conv = " << rom_data_out.read() << endl;
   }

   if (clock_cycle == 143 + 1630)
    pool_0_rst.write(false);
   else if (clock_cycle >= 144 + 1630) {
    if (clock_cycle <= 812 + 1630) {
     cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

     if (conv_0_data_out.read() >= 0) {


      pool_0_data_in.write(conv_0_data_out.read());

      cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
     }
     else
      pool_0_data_in.write(-1);
    }
    else if (clock_cycle == 813 + 1630) {
     conv_0_rst.write(true);
     conv_0_data_in.write(-1);

     cout << "reset conv unit" << endl;
    }
   }

   if (clock_cycle == 173 + 1630) {
    ram_wr.write(true);
   }
   if (clock_cycle >= 174 + 1630) {
    if (pool_0_data_out.read() >= 0) {
     cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

     cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

     ram_data_in.write(pool_0_data_out.read());

     ram_addr.write(ram_addr.read() + 1);

     if (clock_cycle == 814 + 1630) {
      ram_wr.write(false);

      pool_0_rst.write(true);
      pool_0_data_in.write(-1);

      cout << "reset pool unit" << endl;
     }
    }
   }
  }

  /* =============== Conv0_3 =============== */
  if (clock_cycle == 2445) {
   rom_addr.write(1);

   conv_0_rst.write(false);
  }
  else if (clock_cycle >= 1 + 2445 && clock_cycle <= 814 + 2445) {

   if (clock_cycle <= 2445 + 24)
    rom_addr.write(clock_cycle + 1 + 26 * 3 - 2445);
   else if (clock_cycle <= 808 + 2445)
    rom_addr.write(clock_cycle + 44426 - 25 - 2445);

   if (clock_cycle <= 810 + 2445) {
    conv_0_data_in.write(rom_data_out.read());

    cout << "transfer data to Conv = " << rom_data_out.read() << endl;
   }

   if (clock_cycle == 143 + 2445)
    pool_0_rst.write(false);
   else if (clock_cycle >= 144 + 2445) {
    if (clock_cycle <= 812 + 2445) {
     cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

     if (conv_0_data_out.read() >= 0) {


      pool_0_data_in.write(conv_0_data_out.read());

      cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
     }
     else
      pool_0_data_in.write(-1);
    }
    else if (clock_cycle == 813 + 2445) {
     conv_0_rst.write(true);
     conv_0_data_in.write(-1);

     cout << "reset conv unit" << endl;
    }
   }

   if (clock_cycle == 173 + 2445) {
    ram_wr.write(true);
   }
   if (clock_cycle >= 174 + 2445) {
    if (pool_0_data_out.read() >= 0) {
     cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

     cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

     ram_data_in.write(pool_0_data_out.read());

     ram_addr.write(ram_addr.read() + 1);

     if (clock_cycle == 814 + 2445) {
      ram_wr.write(false);

      pool_0_rst.write(true);
      pool_0_data_in.write(-1);

      cout << "reset pool unit" << endl;
     }
    }
   }
  }

  /* =============== Conv0_4 =============== */
  if (clock_cycle == 3260) {
   rom_addr.write(1);

   conv_0_rst.write(false);
  }
  else if (clock_cycle >= 1 + 3260 && clock_cycle <= 814 + 3260) {

   if (clock_cycle <= 3260 + 24)
    rom_addr.write(clock_cycle + 1 + 26 * 4 - 3260);
   else if (clock_cycle <= 808 + 3260)
    rom_addr.write(clock_cycle + 44426 - 25 - 3260);

   if (clock_cycle <= 810 + 3260) {
    conv_0_data_in.write(rom_data_out.read());

    cout << "transfer data to Conv = " << rom_data_out.read() << endl;
   }

   if (clock_cycle == 143 + 3260)
    pool_0_rst.write(false);
   else if (clock_cycle >= 144 + 3260) {
    if (clock_cycle <= 812 + 3260) {
     cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

     if (conv_0_data_out.read() >= 0) {


      pool_0_data_in.write(conv_0_data_out.read());

      cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
     }
     else
      pool_0_data_in.write(-1);
    }
    else if (clock_cycle == 813 + 3260) {
     conv_0_rst.write(true);
     conv_0_data_in.write(-1);

     cout << "reset conv unit" << endl;
    }
   }

   if (clock_cycle == 173 + 3260) {
    ram_wr.write(true);
   }
   if (clock_cycle >= 174 + 3260) {
    if (pool_0_data_out.read() >= 0) {
     cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

     cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

     ram_data_in.write(pool_0_data_out.read());

     ram_addr.write(ram_addr.read() + 1);

     if (clock_cycle == 814 + 3260) {
      ram_wr.write(false);

      pool_0_rst.write(true);
      pool_0_data_in.write(-1);

      cout << "reset pool unit" << endl;
     }
    }
   }
  }

  /* =============== Conv0_5 =============== */
  if (clock_cycle == 4075) {
   rom_addr.write(1);

   conv_0_rst.write(false);
  }
  else if (clock_cycle >= 1 + 4075 && clock_cycle <= 814 + 4075) {

   if (clock_cycle <= 4075 + 24)
    rom_addr.write(clock_cycle + 1 + 26 * 5 - 4075);
   else if (clock_cycle <= 808 + 3260)
    rom_addr.write(clock_cycle + 44426 - 25 - 4075);

   if (clock_cycle <= 810 + 4075) {
    conv_0_data_in.write(rom_data_out.read());

    cout << "transfer data to Conv = " << rom_data_out.read() << endl;
   }

   if (clock_cycle == 143 + 4075)
    pool_0_rst.write(false);
   else if (clock_cycle >= 144 + 4075) {
    if (clock_cycle <= 812 + 4075) {
     cout << "recieve data from Conv = " << conv_0_data_out.read() << endl;

     if (conv_0_data_out.read() >= 0) {


      pool_0_data_in.write(conv_0_data_out.read());

      cout << "transfer data to Pool = " << conv_0_data_out.read() << endl;
     }
     else
      pool_0_data_in.write(-1);
    }
    else if (clock_cycle == 813 + 4075) {
     conv_0_rst.write(true);
     conv_0_data_in.write(-1);

     cout << "reset conv unit" << endl;
    }
   }

   if (clock_cycle == 173 + 4075) {
    ram_wr.write(true);
   }
   if (clock_cycle >= 174 + 4075) {
    if (pool_0_data_out.read() >= 0) {
     cout << "recieve data from Pool = " << pool_0_data_out.read() << endl;

     cout << "transfer data to Ram[ " << ram_addr.read() << " ] = " << pool_0_data_out.read() << endl;

     ram_data_in.write(pool_0_data_out.read());

     ram_addr.write(ram_addr.read() + 1);

     if (clock_cycle == 814 + 4075) {
      ram_wr.write(false);

      pool_0_rst.write(true);
      pool_0_data_in.write(-1);

      cout << "reset pool unit" << endl;
     }
    }
   }
  }

  /* =============== Conv1_0_0 =============== */

  clock_cycle++;
 }
}