#include <SPI.h>
#include <LoRa.h>

#define LORA_CS 10
#define LORA_RST 9
#define LORA_IRQ 2


const int MODULE_ID = 1;

void setup() {
  pinMode(LORA_RST, OUTPUT);
  digitalWrite(LORA_RST, HIGH);

  Serial.begin(9600);
  while (!Serial);


  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  String  x = "";
  x = Serial.readStringUntil("\0");
  if (x==NULL){
    String message =String(MODULE_ID) +"| ,"+String(MODULE_ID) + ": " +"-1 -1" +",";
    Serial.println("Sending: " + message);
    LoRa.beginPacket();
    LoRa.print(message);
    LoRa.endPacket();
    delay(5000);
  }
  else {
  String message =String(MODULE_ID) +"| ,"+String(MODULE_ID) + ": " +x +",";
  Serial.println("Sending: " + message);
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  delay(5000);
  }
}
