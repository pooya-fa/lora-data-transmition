#include <SPI.h>
#include <LoRa.h>

#define LORA_CS 10
#define LORA_RST 9
#define LORA_IRQ 2

const int MODULE_ID = 3;

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

  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    
    }
     if (receivedMessage.startsWith("2-")) {
      String  str = "";
      str = Serial.readStringUntil("\0");
      if (str == NULL) {
        Serial.println("Received: " + receivedMessage);
        String message =String(MODULE_ID)+ "-" + receivedMessage + " " + String(MODULE_ID) + ": " +"-1 -1"+",";
        Serial.println("Sending: " + message);
        LoRa.beginPacket();
        LoRa.print(message);
        LoRa.endPacket();
     }
     else{
      Serial.println("Received: " + receivedMessage);
      String message =String(MODULE_ID)+ "-" + receivedMessage + " " + String(MODULE_ID) + ": " +str+",";
      Serial.println("Sending: " + message);
      LoRa.beginPacket();
      LoRa.print(message);
      LoRa.endPacket();
     }
    }
  }
  //delay(100);
}
