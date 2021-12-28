#include "LeNet_Conv.h"

void Conv::run() {
 if (rst.read()) {
  data_out.write(0);

  clock_cycle = 0;
  size = 0;
  temp_sum = 0;
  bias = 0;
  n = 0;

  for (int i = 0; i < 25; i++)
   kernel[i] = 0;

  for (int i = 0; i < 140; i++)
   data[i] = 0;
 }
 else {
	 if (clock_cycle >= 1 + n*810 && clock_cycle <= 810 + n * 810) {
		 if ((clock_cycle ) < 26+ n * 810)
			 kernel[clock_cycle - 1 + n * 810] = data_in.read();
		 else if (clock_cycle == 26 + n * 810)
			 bias = data_in.read();
	 }
	 else if (clock_cycle >= 27 + n * 810  && clock_cycle <= 810 + n * 810) {
		 data[(clock_cycle - 27 - n * 810) % 140] = data_in.read();

		 if (clock_cycle >= 143 + n * 810 && clock_cycle <= 810 + n * 810) {
			 if ((clock_cycle - 143 - n * 810) % 28 <= 23) {
				 data_out.write(0);

				 for (int j = 0; j < 5; j++)
					 for (int i = 0; i < 5; i++)
						 temp_sum += data[(clock_cycle - n * 810 - 143 + i + 28 * j) % 140] * kernel[i + 3 * j];
				 temp_sum += bias;

				 temp_sum >= 0 ? temp_sum : temp_sum = 0;

				 data_out.write(temp_sum);
			 }
			 else
				 data_out.write(1);
		 }

	 }
		 

  clock_cycle++;
  if (clock_cycle >= 810 && clock_cycle % 811 == 0) {
	  n++;//The "n" means that the (n+1)st kernel is being operated at this time
	  n <= 5;
  }
	 

 }
}
