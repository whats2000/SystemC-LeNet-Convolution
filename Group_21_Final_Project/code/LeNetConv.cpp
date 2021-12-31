#include "LeNetConv.h"

void Conv::conv_run() {
 if (rst.read()) {
  data_out.write(0);

  clock_cycle = 0;
  size = 0;
  temp_sum = 0;
  bias = 0;

  for (int i = 0; i < 25; i++)
   kernel[i] = 0;

  for (int i = 0; i < data_size * 5; i++)
   data[i] = 0;
 }
 else {
  if (clock_cycle <= data_size * data_size + 26)
   cout << ">> Conv clock = " << clock_cycle << endl;

  if (clock_cycle >= 1 && clock_cycle <= 26) {
   //cout << ">> Conv data in = " << data_in.read() << endl;

   if (clock_cycle < 26) {
    kernel[clock_cycle - 1] = data_in.read();

    cout << "kernel[ " << clock_cycle - 1 << " ] = " << kernel[clock_cycle - 1] << endl;
   }
   else if (clock_cycle == 26) {
    bias = data_in.read();

    cout << "bias = " << bias << endl;
   }
  }
  else if (clock_cycle >= 27 && clock_cycle <= data_size * data_size + 26) {
   data[(clock_cycle - 27) % data_size * 5] = data_in.read();

   cout << "data[ " << clock_cycle - 27 << " ] = " << data[(clock_cycle - 27) % data_size * 5] << endl;

   /* 下方有錯誤，上方已經驗證 */
   if (clock_cycle - 27 >= (5 - 1 + data_size * 4)) {
    if ((clock_cycle - 27 - (5 - 1 + data_size * 4)) % data_size <= data_size - 5) {
     for (int j = 0; j < 5; j++)
      for (int i = 0; i < 5; i++)
       temp_sum += data[(clock_cycle - 27 + (5 - 1 + data_size * 4) + i + data_size * j) % data_size * 5]
       * kernel[i + 5 * j];

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
