
//***************** Configuration****************************************

#define tagSize 12

#define rPin D1
#define gPin D2
#define bPin D5

#define f1Pin D0
#define f2Pin D3
#define f3Pin D4
#define lPin D6

#define RFID_BAUDRATE 9600

const char* ssid = "Trojan Horse";
const char* password = "temppass";
const char* mqtt_server = "192.168.43.143"; //Brokers' ip address

//***********************************************************************


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiClient.h>
#include <EEPROM.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

uint8_t redPin = rPin;
uint8_t greenPin = gPin;
uint8_t bluePin = bPin;

const int F1_addr = 0;
const int F2_addr = 1;
const int F3_addr = 2;
const int L_addr = 3;

const int F1_pin = f1Pin;
const int F2_pin = f2Pin;
const int F3_pin = f3Pin;
const int L_pin = lPin;

int F1_stat = 0;
int F2_stat = 0;
int F3_stat = 0;
int L_stat = 0;


unsigned int codeLen;
String buffr;
char tagCode[tagSize];
String s ;


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

void redFlash() {

  for (int r = 0; r < 1023; r += 1) {
    analogWrite(redPin, r);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
    delay(10);
  }

  for (int r = 1023; r >= 0; b -= 1) {

    analogWrite(redPin, r);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
    delay(10);
  }
}

void blinkGreen(){

    analogWrite(redPin, 0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 1023);
    delay(1000);

    analogWrite(redPin, 0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
    delay(1000);    
      
}

void writeRelay() {

  digitalWrite(F1_pin, EEPROM.read(F1_addr));
  digitalWrite(F2_pin, EEPROM.read(F2_addr));
  digitalWrite(F3_pin, EEPROM.read(F3_addr));
  digitalWrite(L_pin, EEPROM.read(L_addr));

}

void setup() {

  pinMode(F1_pin, OUTPUT);
  pinMode(F2_pin, OUTPUT);
  pinMode(F3_pin, OUTPUT);
  pinMode(L_pin, OUTPUT);

  EEPROM.begin(512); // Allocating 512 bytes of EEPROM

  Serial.begin(RFID_BAUDRATE);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    redFlash();
  }

  blinkGreen();
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(MQTT_callback);
  
}

void loop() {

  rgbCycle();
}
