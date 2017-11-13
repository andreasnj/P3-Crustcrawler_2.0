#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); // RX, TX

int temp;

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available() > 0){
    temp = mySerial.read();
    Serial.println(temp, HEX);
}
/*else {Serial.println("*");
      delay(100);}*/
}
