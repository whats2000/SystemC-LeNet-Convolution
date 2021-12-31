#include "LeNetPool.h"

void Pool::pool_run() {
 if (rst.read()) {
  data_out.write(0);
  clock_cycle = 0;
  temp_max = 0;

  for (int i = 0; i < 576; i++)
   data[i / 24][i % 24] = 0;
 }

 else {
  if (clock_cycle >= 1 && clock_cycle <= (data_size * data_size) + 1) {
   data[(clock_cycle - 1) / data_size][(clock_cycle - 1) % data_size] = data_in.read();
  }

  else
   data_out.write(0);
  if (clock_cycle > (((data_size / 4)*3)+1) && clock_cycle <= (data_size * data_size) + 1) {
   for (int i = 0; i <= data_size * data_size; i++) {
    if (((i / data_size) > 0) && ((i % data_size) == 0)) {
     i = i + data_size;//switch two rows
     if (data[i / data_size][i % data_size] >= data[i / data_size][(i + 1) % data_size])
      temp_max = data[i / data_size][i % data_size];
     else
      temp_max = data[i / data_size][(i + 1) % data_size];

     if (data[(i / data_size) + 1][i % data_size] >= temp_max)
      temp_max = data[(i / data_size) + 1][i % data_size];

     if (data[(i / data_size) + 1][(i % data_size) + 1] >= temp_max)
      temp_max = data[(i / data_size) + 1][(i % data_size) + 1];

     data_out.write(temp_max);

     i++;//switch total two columns

    }
    else {
     if (data[i / data_size][i % data_size] >= data[i / data_size][(i + 1) % data_size])
      temp_max = data[i / data_size][i % data_size];
     else
      temp_max = data[i / data_size][(i + 1) % data_size];

     if (data[(i / data_size) + 1][i % data_size] >= temp_max)
      temp_max = data[(i / data_size) + 1][i % data_size];

     if (data[(i / data_size) + 1][(i % data_size) + 1] >= temp_max)
      temp_max = data[(i / data_size) + 1][(i % data_size) + 1];

     data_out.write(temp_max);

     i++;

    }
   }


  }
 }
};
