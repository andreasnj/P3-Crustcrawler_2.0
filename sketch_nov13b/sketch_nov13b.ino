#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
int temp = 0;

void setup() {
  mySerial.begin(115200);
  Serial.begin(115200);
<<<<<<< HEAD
  Serial.flush();
  Serial.println("reset was performed");
  delay(100);
=======
  Serial.flush():
  Serial.println("reset");
>>>>>>> e6bfcef94fab01e4b4fe9d8bb370c9b07bcb13d0
}

void loop() {
  if (mySerial.available() > 0){
    temp = mySerial.read();
<<<<<<< HEAD
    //Serial.println(temp, HEX);
    //Serial.println(mySerial.read());
}
else {Serial.println("*");
      delay(100);}
=======
    Serial.println(temp, HEX);
  }
  else {Serial.println("*");
      delay(1000);}
>>>>>>> e6bfcef94fab01e4b4fe9d8bb370c9b07bcb13d0
}
