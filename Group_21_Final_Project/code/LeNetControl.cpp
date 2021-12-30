#include "LeNetControl.h"

void Control::control_run() {
 if (rst.read()) {
  conv_0_rst.write(true);
  pool_0_rst.write(true);
  dens_0_rst.write(true);
 }
 else {

 }
}