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

  Dynamixel.setHoldingTorque(0x01, true);            //Set on hold torque for each servo
  Dynamixel.setHoldingTorque(0x02, true);
  Dynamixel.setHoldingTorque(0x03, true);
  Dynamixel.setHoldingTorque(0x04, true);
  Dynamixel.setHoldingTorque(0x05, true);

  //Set profile acceleration
  Dynamixel.setProfileAcceleration(0x01, 5);           //Set profile acc for each servo
  Dynamixel.setProfileAcceleration(0x02, 5);
  Dynamixel.setProfileAcceleration(0x03, 5);
  Dynamixel.setProfileAcceleration(0x04, 300);
  Dynamixel.setProfileAcceleration(0x05, 300);

  //Set profile velocity
  Dynamixel.setProfileVelocity(0x01, 70);              //Set profile vel for each servo
  Dynamixel.setProfileVelocity(0x02, 70);
  Dynamixel.setProfileVelocity(0x03, 70);
  Dynamixel.setProfileVelocity(0x04, 200);
  Dynamixel.setProfileVelocity(0x05, 200);

  Serial.println("reset");
  Dynamixel.setNGoalPositions(2048, 2048, 2048, -1, -1); //Starting position
  delay(1500);
delay(500);
}

int out=0, counter=0, cycles=40, wait=10, error;
float fout=0;

void doMvmt(){
  Dynamixel.setNGoalPositions(1000, 3072, 2048, -1, -1);
  delay(3500);
  Dynamixel.setNGoalPositions(2048, 2048, 3072, -1, -1);
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
      case 'l':
        fout = Dynamixel.getLoad(servo);
        break;
      }
      //Dynamixel.readAll();
      //error = Dynamixel.getError(servo);
      //Serial.println(error);
      counter++;
      delay(wait);
    }
  counter=0;
}

void loop() {
  ////// Servo 1
  Serial.println("SERVO 1, POSITION");
  doMvmt();
  Read(1, 'p');

  Serial.println("SERVO 1, VELOCITY");
  doMvmt();
  Read(1, 'v');

  Serial.println("SERVO 1, LOAD");
  doMvmt();
  Read(1, 'l');

  ////// Servo 2
  Serial.println("SERVO 2, POSITION");
  doMvmt();
  Read(2, 'p');

  Serial.println("SERVO 2, VELOCITY");
  doMvmt();
  Read(2, 'v');

  Serial.println("SERVO 2, LOAD");
  doMvmt();
  Read(2, 'l');

  /////// SERVO 3
  Serial.println("SERVO 3, POSITION");
  doMvmt();
  Read(3, 'p');

  Serial.println("SERVO 3, VELOCITY");
  doMvmt();
  Read(3, 'v');

  Serial.println("SERVO 3, LOAD");
  doMvmt();
  Read(3, 'l');
  delay(9000000);
}
