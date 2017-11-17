
//***************** Configuration****************************************
#define tagSize 12

#define rPin D1
#define gPin D2
#define bPin D5


//***********************************************************************


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include "PubSubClient.h"

unsigned int codeLen;
String buffr;
char tagCode[tagSize];

uint8_t redPin = rPin;
uint8_t greenPin = gPin;
uint8_t bluePin = bPin;


void readrfid() {

  buffr = Serial.readString();
  buffr.toCharArray(tagCode, codeLen);
}

void rgbCycle() {


  for (int r = 0; r < 1023; r += 5)
    for (int g = 0; g < 1023; g += 5)
      for (int b = 0; b < 1023; b += 5) {

        analogWrite(redPin, r);
        analogWrite(bluePin, b);
        analogWrite(greenPin, g);
        delayMicroseconds(1);
      }
      
  for (int r = 1023; r >= 0; r -= 5)
    for (int g = 1023; g >= 0; g -= 5)
      for (int b = 1023; b >= 0; b -= 5) {

        analogWrite(redPin, r);
        analogWrite(bluePin, b);
        analogWrite(greenPin, g);
        delayMicroseconds(1);
      }
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {

 rgbCycle();
}
