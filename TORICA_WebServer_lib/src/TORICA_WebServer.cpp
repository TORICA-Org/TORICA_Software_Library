//Webサーバーに関するメンバ関数の定義

#include "TORICA_WebServer.h"
#include "index.h"

const char *softAP_ssid = WIFI_SSID;
const char *softAP_password = WIFI_PASSWORD;
const byte DNS_PORT = 53;

#define STACK_SIZE 4096
StaticTask_t xTaskBuffer;
StackType_t xStack[STACK_SIZE];

DNSServer DNSServerInstance;
WebServer WebServerInstance(80);
IPAddress apIP(192, 168, 4, 1);
IPAddress netMsk(255, 255, 255, 0);

int TORICA_WebServer::index = 0;
char TORICA_WebServer::data[LENGTH];
char* TORICA_WebServer::_p = NULL;

TORICA_WebServer::TORICA_WebServer (char* p) {
  _p = p;
}

void TORICA_WebServer::handleRoot () {
  WebServerInstance.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate");
  WebServerInstance.sendHeader("Pragma", "no-cache");
  WebServerInstance.sendHeader("Expires", "-1");
  WebServerInstance.send(200, "text/html", html);
}

void TORICA_WebServer::getData () {
  if (100 <= index) {
    index = 0;
  }
  sprintf(data, "%02d", index);
  for (int i = 0; i < LENGTH-1; i++) {
    data[2 + i] = _p[((LENGTH - 3) * index) + i];
    if (data[2 + i] == '\0') {
      index = 0;
      break;
    }
  }
  index++;
  
  Serial.print("data: [");
  Serial.print(data);
  Serial.println("]");
  WebServerInstance.send(200, "text/html", data);
}

void TORICA_WebServer::loop (void *param) {
    while (true) {
        DNSServerInstance.processNextRequest();
        WebServerInstance.handleClient();
        vTaskDelay(10/portTICK_RATE_MS);
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
  xTaskCreateStatic(
    loop, //タスク関数へのポインタ
    "WebServerLoop", //タスク名
    STACK_SIZE, //スタックサイズ
    NULL, //タスクのパラメータのポインタ
    2, //タスクの優先順位
    xStack, //タスクのスタックとして使用する配列
    &xTaskBuffer //タスクのデータ構造体へのポインタ
  );
}
