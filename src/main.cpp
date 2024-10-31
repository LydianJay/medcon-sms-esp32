#include <Arduino.h>
#include <DFRobot_SIM808.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#define TINY_GSM_MODEM_SIM808

HardwareSerial serial(2);
DFRobot_SIM808 sim808(&serial);
// 09852319638
void setup() {
  Serial.begin(115200);
  serial.begin(9600, SERIAL_8N1, 16, 17);

  while (!sim808.init()) {
    Serial.println("[ERROR] Sim init!");
  }

  Serial.println("Init Complete");
  if(!sim808.sendSMS("+639157784831", "Sample Text")){
    Serial.println("Error!");
  }
}


void loop() {
  
}

