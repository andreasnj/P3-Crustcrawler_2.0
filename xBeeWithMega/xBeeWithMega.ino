int temp = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  delay(100);
  Serial1.flush();
  Serial.flush();
  Serial.println("reset");
}

void loop(){
    if (0 < Serial1.available()){
      temp = Serial1.read();
      Serial.println(temp, HEX);
    }
//    else {
//Serial.println("*");
//        delay(500);
//        }
}
