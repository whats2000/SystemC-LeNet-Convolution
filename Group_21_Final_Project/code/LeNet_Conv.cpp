#include "LeNet_Conv.h"

void Conv::run() {
 if (rst.read()) {
  data_out.write(0);

  clock_cycle = 0;
  size = 0;
  sum = 0;
  count = 0;

  for(int i = 0; i < 25; i++)
   kernel[i] = 0;
 }
 else {


  clock_cycle++;
 }
}
