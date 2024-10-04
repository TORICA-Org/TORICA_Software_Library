#include <TORICA_UART.h>

TORICA_UART my_torica_uart(&Serial1);

void setup() {
  SerialUSB.begin(115200);
  Serial1.begin(115200);
}

void loop() {
  int readnum = my_torica_uart.readUART();
  for (int j = 0; j < readnum; j++) {
    SerialUSB.println(my_torica_uart.UART_data[j]);
  }
}