//TORICA_WebServer

//WiFiを利用したスマートフォンやPCでデバッグ用モニターです．

//「ログインが必要です」などと表示される画面（キャプティブポータル）で
//任意の文字列（改行コードを含む）をモニターできます．

//WiFiのSSIDは TORICA WebServer
//WiFiのPASSWORDは toricadensou です．

//2025.04.07時点で以下のマイコンでコンパイルが可能です．
//Raspberry Pi Pico W
//Raspberry Pi Pico 2W

//ESP32では不能
//TORICA_libにある他のライブラリが対応していない

#include <TORICA_WebServer.h>

TORICA_WebServer webserver;

void setup() {
  webserver.begin();
}

void loop() {
  uint32_t now = millis();
  char str[128];
  sprintf(str, "改行コードが使用可能です．\n\n以下は実行を開始してからの時間をミリ秒で表示しています．\n%d", now);
  webserver.update(str);
  delay(100);
}
