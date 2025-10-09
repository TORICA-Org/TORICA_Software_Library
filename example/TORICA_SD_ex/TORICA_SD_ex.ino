#include <TORICA_SD.h>

int cs_SD = 28; // XIAO RP2040ならRP2040のGPIO番号で指定
TORICA_SD my_torica_sd(cs_SD);

char SD_BUF[256];

void setup()
{
  my_torica_sd.begin();
}

void loop()
{
  for (int i = 0; i < 100; i++)
  {
    sprintf(SD_BUF, "TEST,%d,%.2f,%.2f\n", millis(), 12.34, 334);
    // my_torica_sd内のバッファに保存
    my_torica_sd.add_str(SD_BUF);
  }
  // SDに書き込み
  my_torica_sd.flash();
  delay(1000);
}