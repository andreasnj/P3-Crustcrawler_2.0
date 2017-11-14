void setup(){
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  
}

void loop() {
  Serial.println("Hello Serial 0");
  Serial1.println("Hello Serial 1");
  Serial2.println("Hello Serial 2");
  delay(2000);}
