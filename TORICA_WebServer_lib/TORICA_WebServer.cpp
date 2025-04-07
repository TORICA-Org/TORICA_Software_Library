//Webサーバーに関するメンバ関数の定義

#include "TORICA_WebServer.h"
#include "index.h"

const char *softAP_ssid = WIFI_SSID;
const char *softAP_password = WIFI_PASSWORD;
const byte DNS_PORT = 53;

DNSServer DNSServerInstance;
WebServer WebServerInstance(80);
IPAddress apIP(172, 217, 28, 1);
IPAddress netMsk(255, 255, 255, 0);

TORICA_WebServer::TORICA_WebServer () {}

char TORICA_WebServer::data[256];

void TORICA_WebServer::update (char *p) {
  strncpy(data, p, 256);
}

void TORICA_WebServer::handleRoot () {
  WebServerInstance.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  WebServerInstance.sendHeader("Pragma", "no-cache");
  WebServerInstance.sendHeader("Expires", "-1");
  WebServerInstance.send(200, "text/html", html);
}

void TORICA_WebServer::getData () {
  WebServerInstance.send(200, "text/html", data);
}

void TORICA_WebServer::loop (void *param) {
    while (true) {
        DNSServerInstance.processNextRequest();
        WebServerInstance.handleClient();
        delay(10);
    }
}

void TORICA_WebServer::begin () {
  WiFi.disconnect(true);//これがないとwebServerを再起動できない
  delay(1000);//この遅延は必須（これがないとwebServerが起動しない）
  WiFi.softAPConfig(apIP, apIP, netMsk);
  WiFi.softAP(softAP_ssid, softAP_password);
  delay(500);  // Without delay I've seen the IP address blank
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  DNSServerInstance.setErrorReplyCode(DNSReplyCode::NoError);
  DNSServerInstance.start(DNS_PORT, "*", apIP);

  WebServerInstance.on("/", handleRoot);
  WebServerInstance.on("/generate_204", handleRoot);
  WebServerInstance.on("/fwlink", handleRoot);
  WebServerInstance.onNotFound(handleRoot);
  WebServerInstance.on("/get/data", getData);
  WebServerInstance.begin();

  //マルチスレッドでタスクを実行
  xTaskCreate(
    loop, //タスク関数へのポインタ
    "WebServerLoop", //タスク名
    4096, //スタックサイズ
    NULL, //タスクのパラメータのポインタ
    2, //タスクの優先順位
    NULL //タスクのHandleへのポインタ
  );
}
