#include "TORICA_SD.h"
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

bool TORICA_SD::begin()
{
  SERIAL_USB.print("Initializing SD card...");
#if defined(SEEED_XIAO_RP2040)
  SPI.setRX(SD_SPI_MISO);
  SPI.setCS(SD_SPI_CSn);
  SPI.setSCK(SD_SPI_SCK);
  SPI.setTX(SD_SPI_MOSI);
  if (!SD.begin(cs_SD, SPI))
#else
  if (!SD.begin(cs_SD))
#endif
  {
    SERIAL_USB.println("Card failed, or not present");
    SDisActive = false;
    return false;
  }
  new_file();
  dataFile = SD.open(fileName, FILE_WRITE);

  SERIAL_USB.println("card initialized.");

  SDisActive = true;
  return true;
}

void TORICA_SD::add_str(char str[])
{
  if (SDisActive)
  {
    dataFile.write(str, strlen(str));
  }
}

void TORICA_SD::new_file()
{
  String s;
  int fileNum = 0;
  while (1)
  {
    s = "LOG";
    if (fileNum < 10)
    {
      s += "000";
    }
    else if (fileNum < 100)
    {
      s += "00";
    }
    else if (fileNum < 1000)
    {
      s += "0";
    }
    s += fileNum;
    s += ".CSV";
    s.toCharArray(fileName, 16);
    if (!SD.exists(fileName))
      break;
    fileNum++;
  }
  file_time = millis();
}

void TORICA_SD::flash()
{
  uint32_t SD_time = millis();

  if (SDisActive)
  {
    if (millis() - file_time > 10 * 60 * 1000)
    {
      dataFile.close();
      new_file();
      dataFile = SD.open(fileName, FILE_WRITE);
    }
    if (dataFile.size() >= TORICA_SD_MAX_FILE_SIZE)
    {
      SERIAL_USB.println("TORICA_SD_MAX_FILE_SIZE");
      dataFile.close();
      new_file();
      dataFile = SD.open(fileName, FILE_WRITE);
    }

    if (dataFile)
    {
      dataFile.flush();
      // SERIAL_USB.println("SD_buf_count,SD_total");
      // SERIAL_USB.print(",");
      uint32_t SD_total = millis() - SD_time;
      // SERIAL_USB.println(SD_total);
    }
  }

  if (retry && (!dataFile || !SDisActive))
  {
    SERIAL_USB.println("error opening file");
    end();
    SDisActive = begin();
  }
}

void TORICA_SD::end()
{
  SDisActive = false;
  SD.end();
}
