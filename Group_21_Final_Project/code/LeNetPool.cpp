#include "LeNetPool.h"

void Pool::pool_run() {
 if (rst.read()) {
  data_out.write(-1);
  temp_max = 0;
  clock_pool = 0;

  for (int i = 0; i < 48; i++)
   data[i] = 0;
 }
 else if (data_in.read() >= 0 && data_size > 0) {
  if (clock_pool < data_size * data_size)
   cout << ">> pool clock = " << clock_pool << endl;

  if (clock_pool < data_size * data_size) {
   data[clock_pool % (data_size * 2)] = data_in.read();

   cout << "data[ " << clock_pool << " ] = " << data[clock_pool % (data_size * 2)] << endl;

   if (clock_pool >= data_size + 2 - 1) {
    if ((clock_pool - (data_size + 2 - 1)) % data_size <= data_size - 2 /* 首次抓取不做運算 */
     && (clock_pool - (data_size + 2 - 1)) % 2 == 0 /* 每抓取2次運算 */
     && (clock_pool / data_size) % 2 != 0 /* 每2行運算一次 */
     ) {
     temp_max = data[clock_pool % (data_size * 2)];

     if (temp_max < data[clock_pool % (data_size * 2) - 1])
      temp_max = data[clock_pool % (data_size * 2) - 1];

     if (temp_max < data[clock_pool % (data_size * 2) - data_size])
      temp_max = data[clock_pool % (data_size * 2) - data_size];

     if (temp_max < data[clock_pool % (data_size * 2) - data_size - 1])
      temp_max = data[clock_pool % (data_size * 2) - data_size - 1];

     cout << "max = " << temp_max << endl;

     data_out.write(temp_max);
    }
    else
     data_out.write(-1);
   }
   clock_pool++;
  }
 }
 else
  data_out.write(-1);
};
