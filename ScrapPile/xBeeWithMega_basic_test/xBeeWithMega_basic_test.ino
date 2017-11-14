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
    if (0 < Serial1.available()){//Read xBee signal and print
      temp = Serial1.read();
      Serial.println(temp, HEX);
    }
}
