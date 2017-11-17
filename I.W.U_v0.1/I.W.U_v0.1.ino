#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include "PubSubClient.h"

#define tagSize 12

unsigned int codeLen;
String buffr;
char tagCode[tagSize];

void readrfid(){

    buffr = Serial.readString();
    buffr.toCharArray(tagCode,codeLen);
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
