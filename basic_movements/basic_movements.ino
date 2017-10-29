#include "Dynamixel_Serial.h"
#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode

SoftwareSerial mySerial(10, 11);    // RX, TX

int *data;
bool done = false;

void setup(){
  Serial.flush();                                       // Clear the serial buffer of garbage data before running the code.
  mySerial.begin(SERVO_SET_Baudrate);                   // We now need to set Ardiuno to the new Baudrate speed 115200
  Serial.begin(SERVO_SET_Baudrate);                                  // Start serial communication on baudrate 57600
  Dynamixel.begin(mySerial);                            // Calling mySerial function which sets 10 pin as the 2nd RX serial pin, and sets pin 11 as the 2nd TX serial pin
  Dynamixel.setDirectionPin(SERVO_ControlPin);          // Optional. Set direction control pin which control if the program writes or reads to and from the robot

  // Turn on hold on the servos:
  Dynamixel.setHoldingTorque(0x01, true);               //Turn on hold torque on servo 1
  Dynamixel.setHoldingTorque(0x02, true);               //Turn on hold torque on servo 2
  Dynamixel.setHoldingTorque(0x03, true);               //Turn on hold torque on servo 3
  Dynamixel.setHoldingTorque(0x04, true);               //Turn on hold torque on servo 4
  Dynamixel.setHoldingTorque(0x05, true);               //Turn on hold torque on servo 5

  // Set the Profile acceleration.
  Dynamixel.setProfileAcceleration(0x01, 10);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(0x02, 10);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(0x03, 10);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(0x04, 300);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(0x05, 300);  //Set the Profile Acceleration for each servo. (max. is 32767)

  // Set the Profile velocity.
  Dynamixel.setProfileVelocity(0x01, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(0x02, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(0x03, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(0x04, 200);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(0x05, 200);  //Set the Profile Velocity for each servo. (max. is 1023)
  
  //Get load on servos in maximum procent (The power required by the servo to hold its current position)
  Dynamixel.getLoad(0x02);  
  
  //Saving and printing positon from all servos
  data = Dynamixel.getPositionN(); 

  for(int i = 0; i < 5; i++){
    Serial.println(data[i]);
  }
}

void loop(){  
  int id1 = 2048;
  int id2 = 2048;
  int id3 = 2048;
  int id4 = 2548;
  int id5 = 1548;

  int pos1, pos2, pos3, pos4, pos5;

  Dynamixel.setNGoalPositions(id1, id2, id3, -1, -1);
  while(!done){
    pos1 =  Dynamixel.getPosition(0x01);
    pos2 =  Dynamixel.getPosition(0x02);
    pos3 =  Dynamixel.getPosition(0x03);  
    delay(1000);
    if ((id2 == pos2) || (id3 == pos3) || (id1 == pos1)){
      Dynamixel.setNGoalPositions(-1, -1, -1, id4, id5);
      break;}};

  pos4 =  Dynamixel.getPosition(0x04); 
  pos5 =  Dynamixel.getPosition(0x05); 

  if ((id4 == pos4) || (id5 == pos5)){
    id1 = 2048;
    id2 = 1000;
    id3 = 2048;
    id4 = 2117;
    id5 = 1974;}

  Dynamixel.setNGoalPositions(-1, id2, id3, -1, -1);
  while(!done){
    pos1 =  Dynamixel.getPosition(0x01);
    pos2 =  Dynamixel.getPosition(0x02);
    pos3 =  Dynamixel.getPosition(0x03);  
    delay(1000);
    if ((id2 == pos2) || (id3 == pos3) || (id1 == pos1)){
      Dynamixel.setNGoalPositions(id1, -1, -1, id4, id5);
      break;}}
}

  /*while(!done){
  Dynamixel.setNGoalPositions(id1, id2, id3, -1, -1);
  pos1 =  Dynamixel.getPosition(0x01);
  pos2 =  Dynamixel.getPosition(0x02);
  pos3 =  Dynamixel.getPosition(0x03);  
  if ((id1 == pos1) && (id2 == pos2) && (id3 == pos3)){
    done = true;}}
  
  done = false;

  while(!done){
  Dynamixel.setNGoalPositions(-1, -1, -1, id4, id5);
  pos4 =  Dynamixel.getPosition(0x04);
  pos5 =  Dynamixel.getPosition(0x05);
  if ((id4 == pos4) && (id5 == pos5)){
    done = true;}}*/
