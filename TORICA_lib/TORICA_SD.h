// https://qiita.com/MergeCells/items/85a860150735730faabc
#if defined(ARDUINO_SAM_DUE)
// DUE RAM 96KB
//#define TORICA_SD_BUF_SIZE 4096
#define SERIAL_USB SerialUSB
#define TORICA_SD_MAX_FILE_SIZE 1048576
#elif defined(ARDUINO_SEEED_XIAO_M0)
// XIAO RAM 32KB
//#define TORICA_SD_BUF_SIZE 4096
#define SERIAL_USB Serial
#define TORICA_SD_MAX_FILE_SIZE 1048576
// RP2040 RAM 264KB
#elif defined(SEEED_XIAO_RP2040)
//#define TORICA_SD_BUF_SIZE 4096
#define SERIAL_USB Serial
#define TORICA_SD_MAX_FILE_SIZE 1048576
// https://files.seeedstudio.com/wiki/XIAO-RP2040/res/Seeed-Studio-XIAO-RP2040-v1.3.pdf
// setCSはハードウェアCSピンじゃないとpanicするので一旦17ピン(赤LED)で設定
#define SD_SPI_SCK (2)
#define SD_SPI_MOSI (3)
#define SD_SPI_MISO (4)
#define SD_SPI_CSn (17)
#else
// other board
//#define TORICA_SD_BUF_SIZE 1024
#define SERIAL_USB Serial
#define TORICA_SD_MAX_FILE_SIZE 1048576
#endif

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

class TORICA_SD
{
public:
  TORICA_SD(int _cs_SD, bool _retry = true)
  {
    cs_SD = _cs_SD;
    retry = _retry;
  }

  bool begin();
  void add_str(char str[]);
  void flash();
  volatile bool SDisActive = false;

private:
  void new_file();
  void end();
  volatile uint32_t file_time = 0;

  volatile int cs_SD = LED_BUILTIN;
  char fileName[16];
  File dataFile;
  volatile bool retry = true;
  //volatile uint32_t file_size = 0;
  //volatile char SD_buf[2][TORICA_SD_BUF_SIZE];
  //volatile int SD_buf_index = 0;
  //volatile uint32_t SD_buf_count[2] = {0, 0};
};
