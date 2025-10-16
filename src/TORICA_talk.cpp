#include "TORICA_talk.h"
#include <Arduino.h>
#include <Wire.h>

//質問（このクラスオブジェクトの生成をしないとしたのCONVERT_numでtalk_strが使えないのではないか？）

#ifndef ESP_PLATFORM // ESP32C3でコンパイル不可能だった（Wire1などが存在しない）ため，プリプロセッサで回避

void TORICA_talk::talk_num(float num){

  char str[64];
  sprintf(str,"<NUM VAL=%.1f>",num);
  talk_str(str);  // メンバ関数の呼び出しのように　クラス名.関数名　でＯＫ？？
  
}


/*talk_str関数の定義づけ
TORICA＿talkと呼ばれるクラスにtalk_str（メンバ関数）は所属していなければならない*/

void TORICA_talk::talk_str(char str[]){
  
  Wire1.beginTransmission(0x2E); // スタートとスレーブアドレスを送る役割　（swの役割）
  
  Wire1.write((const uint8_t*)str,strlen(str)*sizeof(char)); 
 // Wire1.write('\r'); 

  //Wire1.endTransmission();    // stop transmitting
}

 //sprintf(x);//文字列を作る←数値を文字列に変換することで文字列のまま読むことができる


void TORICA_talk::callout_koudo(){
    talk_str("ko'udo");
    Wire1.write('\r');
    Wire1.endTransmission();
}

void TORICA_talk::callout_val(float val){
    talk_num(val);
    Wire1.write('\r');
    Wire1.endTransmission();
}

#endif