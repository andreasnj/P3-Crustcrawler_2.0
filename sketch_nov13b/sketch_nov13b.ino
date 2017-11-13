#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

int temp = 0;

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  Serial.begin(115200);
  Serial.flush();
  Serial.println("reset was performed");
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available() > 0){
    temp = mySerial.read();
    //Serial.println(temp, HEX);
    //Serial.println(mySerial.read());
}
else {Serial.println("*");
      delay(100);}
}
