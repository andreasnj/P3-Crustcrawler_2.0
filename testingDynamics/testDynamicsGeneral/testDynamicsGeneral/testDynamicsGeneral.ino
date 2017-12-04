#include <Dynamixel_Serial.h>
#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)

SoftwareSerial w(10, 11);

void setup() {
  Serial.begin(SERVO_SET_Baudrate);
  w.begin(SERVO_SET_Baudrate);
  Dynamixel.begin(w);
  Dynamixel.setDirectionPin(SERVO_ControlPin);

//*
  Dynamixel.setHoldingTorque(0x01, false);            //Set on hold turque for each servo
  Dynamixel.setHoldingTorque(0x02, false);
  Dynamixel.setHoldingTorque(0x03, false);
  Dynamixel.setHoldingTorque(0x04, false);
  Dynamixel.setHoldingTorque(0x05, false);

  //Set profile acceleration
  Dynamixel.setProfileAcceleration(0x01, 10);           //Set profile acc for each servo
  Dynamixel.setProfileAcceleration(0x02, 10);
  Dynamixel.setProfileAcceleration(0x03, 10);
  Dynamixel.setProfileAcceleration(0x04, 300);
  Dynamixel.setProfileAcceleration(0x05, 300);

  //Set profile velocity
  Dynamixel.setProfileVelocity(0x01, 70);              //Set profile vel for each servo
  Dynamixel.setProfileVelocity(0x02, 70);
  Dynamixel.setProfileVelocity(0x03, 70);
  Dynamixel.setProfileVelocity(0x04, 200);
  Dynamixel.setProfileVelocity(0x05, 200);

  Dynamixel.setHoldingTorque(0x01, true);            //Set on hold turque for each servo
  Dynamixel.setHoldingTorque(0x02, true);
  Dynamixel.setHoldingTorque(0x03, true);
  Dynamixel.setHoldingTorque(0x04, true);
  Dynamixel.setHoldingTorque(0x05, true);
//  */
}

int out=0, counter=0, cycles=45, wait=10;
float fout=0;


void doMvmt(){
  Dynamixel.setNGoalPositions(-1, 1000, 2000, -1, -1);
  delay(3500);
  Dynamixel.setNGoalPositions(-1, 2000, 1000, -1, -1);
}

void Read(int servo, char var){
  while (counter < cycles){
    switch(var){
      case 'p':
        out = Dynamixel.getPosition(servo);
        break;
      case 'v':
        fout = Dynamixel.getVelocity(servo);
        break;
      case 'a':
        fout = Dynamixel.getAcceleration(servo);
        break;
    }
  counter++;
  delay(wait);
  }
  counter=0;
}

void loop() {
  Serial.println("SERVO 2, POSITION");
  doMvmt();
  Read(2, p);

  Serial.println("SERVO 2, VELOCITY");
  doMvmt();
  Read(2, v);

  Serial.println("SERVO 2, LOAD");
  doMvmt();
  Read(2, a);

  /////// SERVO 3
  Serial.println("SERVO 3, POSITION");
  doMvmt();
  Read(3, p);

  Serial.println("SERVO 3, VELOCITY");
  doMvmt();
  Read(3, v);

  Serial.println("SERVO 3, LOAD");
  doMvmt();
  Read(3, a);
  delay(9000000);
}
