#include <SPI.h>
#include <LoRa.h>


const int MODULE_ID = 4;

void setup() {

  Serial.begin(9600);
  while (!Serial);

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
     if (receivedMessage.startsWith("3-")) {
      String  str = "";
      str = Serial.readStringUntil("\0");
      if (str == NULL){
        Serial.println("Received: " + receivedMessage);
        String message = "|4-"+receivedMessage + " " + String(MODULE_ID) + ": " +"-1 -1"+",";
        Serial.println("Processed: " +message);
     }
     else{
      Serial.println("Received: " + receivedMessage);
      String message = "|4-"+receivedMessage + " " + String(MODULE_ID) + ": " +str+",";
      Serial.println("Processed: " +message);
     }
    }
  }
}

