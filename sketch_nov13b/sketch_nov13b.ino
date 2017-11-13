#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available() > 0){
    Serial.println(mySerial.read());

}
/*else {Serial.println("*");
      delay(100);}*/
}
