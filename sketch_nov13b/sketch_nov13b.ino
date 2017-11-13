#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
int temp = 0;

void setup() {
  mySerial.begin(115200);
  Serial.begin(115200);
  Serial.flush():
  Serial.println("reset");
}

void loop() {
  if (mySerial.available() > 0){
    temp = mySerial.read();
    Serial.println(temp, HEX);
  }
  else {Serial.println("*");
      delay(1000);}
}
