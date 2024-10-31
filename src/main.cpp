#include <Arduino.h>
#include <DFRobot_SIM808.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "credentials.h"
#define TINY_GSM_MODEM_SIM808

HardwareSerial serial(2);
DFRobot_SIM808 sim808(&serial);
WiFiServer server(80);
// 09852319638
void setup() {
  Serial.begin(115200);
  serial.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("Connecting...");
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());
  while (!sim808.init()) {
    Serial.println("[ERROR] Sim init!");
  }

  Serial.println("Init Complete");
  
  server.begin();
}

uint8_t numberBuffer[10];


void loop() {


  WiFiClient client = server.available();

  if (client) {
    while (client.connected()) {
      if (client.available()) {
        JsonDocument doc;
        String buffer = client.readString();
        deserializeJson(doc, buffer);
        String number = doc[String("number")];
        String msg = doc[String("msg")];
        Serial.println(number);
        Serial.println(msg);
        // Serial.println(String("+63") + String((char*)numberBuffer));
        // String number = String("+63") + String((char*)numberBuffer);
        if (!sim808.sendSMS((char*)number.c_str(), (char*)msg.c_str())) {
          Serial.println("Error Sending Message!");
        }
      }
    }
    
  }
}

