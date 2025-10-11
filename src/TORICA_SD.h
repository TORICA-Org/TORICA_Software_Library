#pragma once // インクルードガード

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
#elif defined(RASPBERRY_PI_PICO)
//#define TORICA_SD_BUF_SIZE 4096
#define SERIAL_USB Serial
#define TORICA_Pico_SD_MAX_FILE_SIZE 1048576
// https://files.seeedstudio.com/wiki/XIAO-RP2040/res/Seeed-Studio-XIAO-RP2040-v1.3.pdf
// setCSはハードウェアCSピンじゃないとpanicするので一旦25ピン(LED)で設定
#define SD_SPI_SCK (18)
#define SD_SPI_MOSI (19)
#define SD_SPI_MISO (16)
#define SD_SPI_CSn (17)
#else
// other board
//#define TORICA_SD_BUF_SIZE 1024
#define SERIAL_USB Serial
#define TORICA_SD_MAX_FILE_SIZE 1048576
#endif

#include <Arduino.h>
#include <SPI.h>
#include <SD.h> // グローバルの`SD`オブジェクトが自動生成される

enum mode {
  LEGACY, // 25代まで使用していた動作
  CORE // SPI関連の設定を外部で行う動作に変更
};

class TORICA_SD
{
public:
  TORICA_SD(bool _retry = true);
  TORICA_SD(int _cs_SD, bool _retry = true);

  bool begin();
  bool begin(int _cs_SD);
  void add_str(char str[]);
  void flash();
  volatile bool SDisActive = false;

private:
  void new_file();
  void end();
  volatile uint32_t file_time = 0;

  volatile int cs_SD = 1;
  char fileName[16];
  int mainNum = 0;
  int subNum = 0;
  File dataFile;
  volatile bool retry = true;
  //volatile uint32_t file_size = 0;
  //volatile char SD_buf[2][TORICA_SD_BUF_SIZE];
  //volatile int SD_buf_index = 0;
  //volatile uint32_t SD_buf_count[2] = {0, 0};

  mode MODE = CORE;
};
