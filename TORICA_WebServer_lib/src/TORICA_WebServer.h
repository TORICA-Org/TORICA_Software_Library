<<<<<<< HEAD:TORICA_WebServer_lib/TORICA_WebServer.h
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
=======
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

#define LENGTH 32

class TORICA_WebServer {
  public:
    TORICA_WebServer(char* p);
    void begin();

  private:
    static int index;
    static char data[LENGTH];
    static char* _p;
    static void handleRoot();
    static void getData();
    static void loop(void* param);
};

#endif // TORICA_WEBSERVER_H
>>>>>>> 52fab5a81cc0a9454ff2176d702e0a7181f3abec:TORICA_WebServer_lib/src/TORICA_WebServer.h
