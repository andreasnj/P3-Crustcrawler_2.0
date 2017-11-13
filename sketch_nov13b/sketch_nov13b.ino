#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
<<<<<<< HEAD
int temp;
=======

int temp = 0;
>>>>>>> 15a40f7f12c08bc748d2d14b0f8a63dfa239efb5

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(115200);
<<<<<<< HEAD
  Serial.begin(9600);
  Serial.println("reset");
=======
  Serial.begin(115200);
  Serial.flush();
  Serial.println("reset was performed");
>>>>>>> 15a40f7f12c08bc748d2d14b0f8a63dfa239efb5
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available() > 0){
    temp = mySerial.read();
    Serial.println(temp, HEX);
  }
  else {Serial.println("*");
      delay(1000);}
}
