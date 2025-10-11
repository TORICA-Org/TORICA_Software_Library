#include <TORICA_SD.h>

TORICA_SD mySD; // 引数なしでインスタンス化

const int _CS = 1;
const int _SCK = 2;
const int _MOSI = 3;
const int _MISO = 4;

char SD_BUF[256];

void setup() {
  #ifdef ARDUINO_ARCH_RP2040 //RP2040及びRP2350のチェックに対応
  SPI.setCS(_CS);
  SPI.setSCK(_SCK);
  SPI.setTX(_MOSI);
  SPI.setRX(_MISO);
  #endif

  SPI.begin();
  mySD.begin(_CS);
}

void loop() {
  for (int i = 0; i < 100; i++) {
    sprintf(SD_BUF, "TEST,%d,%.2f,%.2f\n", millis(), 12.34, 334);
    mySD.add_str(SD_BUF); // バッファに書き込み
  }
  mySD.flash(); // SDに書き込み
  delay(1000);
}
