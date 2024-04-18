#include "connection_controller.h"
#include "dht11.h"
#include "display.h"
#include "pc_comm.h"
#include "wifi.h"
#include <stdio.h>
#include <util/delay.h>



int main() {
  pc_comm_init(9600, NULL);
  connection_controller_init();
  connection_controller_transmit("Hello World!", 13);
  return 0;
  
}
