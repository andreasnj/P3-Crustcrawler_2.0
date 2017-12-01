#include <Dynamixel_Serial.h>
#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)

int out=0, counter=0;

SoftwareSerial w(10, 11);

void setup() {
  Serial.begin(SERVO_SET_Baudrate);
  w.begin(SERVO_SET_Baudrate);
  Dynamixel.begin(w);
  Dynamixel.setDirectionPin(SERVO_ControlPin);

  Dynamixel.setHoldingTorque(0x01, true);               //Set on hold turque for each servo
  Dynamixel.setHoldingTorque(0x02, true);
  Dynamixel.setHoldingTorque(0x03, true);
  Dynamixel.setHoldingTorque(0x04, true);
  Dynamixel.setHoldingTorque(0x05, true);

  //Set profile acceleration
  Dynamixel.setProfileAcceleration(0x01, 10);           //Set profile acc for each servo
  Dynamixel.setProfileAcceleration(0x02, 10);
  Dynamixel.setProfileAcceleration(0x03, 10);
  Dynamixel.setProfileAcceleration(0x04, 300);
  Dynamixel.setProfileAcceleration(0x05, 300);

  //Set profile velocity
  Dynamixel.setProfileVelocity(0x01, 100);              //Set profile vel for each servo
  Dynamixel.setProfileVelocity(0x02, 100);
  Dynamixel.setProfileVelocity(0x03, 100);
  Dynamixel.setProfileVelocity(0x04, 200);
  Dynamixel.setProfileVelocity(0x05, 200);
}

void doMvmt(){
  Dynamixel.setNGoalPositions(-1, 1000, 2000, -1, -1);
  delay(3000);
  Dynamixel.setNGoalPositions(-1, 2000, 1000, -1, -1);
}

void loop() {
  counter=0;
  Serial.println("SERVO 2, POSITION");
  doMvmt();
  while (counter <= 45){
  out = Dynamixel.getPosition(2);
  counter++;
  delay(10);
  }
  
  counter=0;
  Serial.println("SERVO 2, VELOCITY");
  doMvmt();
  while (counter <= 45){
  out = Dynamixel.getVelocity(2);
  counter++;
  delay(10);
  }
  
  counter=0;
  Serial.println("SERVO 2, LOAD");
  doMvmt();
  while (counter <= 45){
  out = Dynamixel.getLoad(2);
  counter++;
  delay(10);
  }

  /////// SERVO 3 \\\\\\\
  counter=0;
  Serial.println("SERVO 3, POSITION");
  doMvmt();
  while (counter <= 45){
  out = Dynamixel.getPosition(3);
  counter++;
  delay(10);
  }
  
  counter=0;
  Serial.println("SERVO 3, VELOCITY");
  doMvmt();
  while (counter <= 45){
  out = Dynamixel.getVelocity(3);
  counter++;
  delay(10);
  }
  
  counter=0;
  Serial.println("SERVO 3, LOAD");
  doMvmt();
  while (counter <= 45){
  out = Dynamixel.getLoad(3);
  counter++;
  delay(10);
  }
  delay(1000000);
}
