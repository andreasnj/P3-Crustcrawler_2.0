#include <SoftwareSerial.h>

// Connect pin 10 of Arduino to DOUT of Wireless Proto shield
uint8_t ssRX = 2;

// Connect pin 11 of Arduino to DIN of Wireless Proto shield
uint8_t ssTX = 3;

SoftwareSerial nss(ssRX, ssTX);

void setup() {
  Serial.begin(115200);
  nss.begin(115200);
  Serial.println("Serial works");
}

void loop() {

  if (nss.available()){
    Serial.println("received packet:");
    for(int i=0;i<25;i++){
      Serial.print(nss.read(),HEX);
      Serial.print(",");
    }
    Serial.println();
   }
}
