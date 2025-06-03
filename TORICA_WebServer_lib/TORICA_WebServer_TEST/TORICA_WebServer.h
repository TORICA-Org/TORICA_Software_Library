//Webサーバーに関するクラスの定義

#ifndef TORICA_WEBSERVER_H
#define TORICA_WEBSERVER_H

#define WIFI_SSID "TORICA WebServer"
#define WIFI_PASSWORD "toricadensou"

#include <Arduino.h>

#ifdef ARDUINO_ARCH_RP2040 //RP2040及びRP2350のチェックに対応
#include <FreeRTOS.h>
#include <task.h>
#endif

#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>

class TORICA_WebServer {
  public:
    TORICA_WebServer(char* p);
    void begin();

  private:
    static char* _p;
    static void handleRoot();
    static void getData();
    static void handlePing();
    static void loop(void* param);
};

#endif // TORICA_WEBSERVER_H
