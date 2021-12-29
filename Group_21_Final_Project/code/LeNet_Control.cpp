#include "LeNet_Control.h"

void Control::run() {
 if (rst.read()) {
  conv_0_rst.write(true);
  pool_0_rst.write(true);
  dens_0_rst.write(true);
 }
 else {

 }
}