#include "LeNetConv.h"

void Conv::run() {
 if (rst.read()) {
  data_out.write(0);

  clock_cycle = 0;
  size = 0;
  temp_sum = 0;
  bias = 0;

  for (int i = 0; i < 25; i++)
   kernel[i] = 0;

  for (int i = 0; i < 140; i++)
   data[i] = 0;
 }
 else {
  if (clock_cycle >= 1 && clock_cycle <= 810) {
   if (clock_cycle < 26)
    kernel[clock_cycle - 1] = data_in.read();
   else if (clock_cycle == 26)
    bias = data_in.read();
  }
  else if (clock_cycle >= 27 && clock_cycle <= 810) {
   data[(clock_cycle - 27) % 140] = data_in.read();

   if (clock_cycle >= 143 && clock_cycle <= 810) {
    if ((clock_cycle - 143) % 28 <= 23) {
     for (int j = 0; j < 5; j++)
      for (int i = 0; i < 5; i++)
       temp_sum += data[(clock_cycle - 143 + i + 28 * j) % 140] * kernel[i + 5 * j];

     temp_sum += bias;

     temp_sum >= 0 ? temp_sum : temp_sum = 0;

     data_out.write(temp_sum);
    }
    else
     data_out.write(-1);
   }
  }
  clock_cycle++;
 }
}
