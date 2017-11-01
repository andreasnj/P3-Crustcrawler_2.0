#include "Dynamixel_Serial.h"
#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define OPEN 'o'
#define CLOSE 'c'

SoftwareSerial mySerial(10, 11);    // RX, TX

/*void performMovement(int goal1, int goal2, int goal3, char forGripper){
  int pos1 = 0;
  int pos2 = 0;
  int pos3 = 0;
  int pos4 = 0;
  int pos5 = 0;

  Dynamixel.setNGoalPositions(goal1, goal2, goal3, -1, -1);
  while(!((goal2 >= pos2-11) && (goal2 <= pos2+11)) && ((goal3 >= pos3-11) && (goal3 <= pos3+11)) && ((goal1 >= pos1-11) && (goal1 <= pos1+11))){ //error for +- 1 degree due to an inaccuracy of the motors
    pos1 =  Dynamixel.getPosition(0x01);
    pos2 =  Dynamixel.getPosition(0x02);
    pos3 =  Dynamixel.getPosition(0x03); 
  }

    Dynamixel.setProfileVelocity(0x01, 0);  //Set the Profile Velocity for each servo. (max. is 1023)
    Dynamixel.setProfileVelocity(0x02, 0);  //Set the Profile Velocity for each servo. (max. is 1023)
    Dynamixel.setProfileVelocity(0x03, 0);  //Set the Profile Velocity for each servo. (max. is 1023)      
    Dynamixel.gripper(forGripper);
    delay(500);
    Dynamixel.setProfileVelocity(0x01, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
    Dynamixel.setProfileVelocity(0x02, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
    Dynamixel.setProfileVelocity(0x03, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
    delay(1000);
}*/

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
}

void loop(){  
  /*
  Dynamixel.setNGoalPositions(id1, id2, id3, -1, -1);
  while(!done){
    pos1 =  Dynamixel.getPosition(0x01);
    pos2 =  Dynamixel.getPosition(0x02);
    pos3 =  Dynamixel.getPosition(0x03); 
    if (((id2 >= pos2-11) && (id2 <= pos2+11)) && ((id3 >= pos3-11) && (id3 <= pos3+11)) && ((id1 >= pos1-11) && (id1 <= pos1+11))){
      Dynamixel.setProfileVelocity(0x01, 0);  //Set the Profile Velocity for each servo. (max. is 1023)
      Dynamixel.setProfileVelocity(0x02, 0);  //Set the Profile Velocity for each servo. (max. is 1023)
      Dynamixel.setProfileVelocity(0x03, 0);  //Set the Profile Velocity for each servo. (max. is 1023) 
      delay(3000);     
      Dynamixel.gripper(CLOSE);
      Dynamixel.setProfileVelocity(0x01, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
      Dynamixel.setProfileVelocity(0x02, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
      Dynamixel.setProfileVelocity(0x03, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
      
      pos4 =  Dynamixel.getPosition(0x04); 
      pos5 =  Dynamixel.getPosition(0x05); 

      //if (((id4 >= pos4-3) && (id4 <= pos4+2)) || ((id5 >= pos5-3) && (id5 <= pos5+2))){
        //id1 = 3048;
        //id2 = 2048;
        //id3 = 1000;
        //id4 = 2548;
        //id5 = 1548;
      //}
        break;}};*/

  Dynamixel.performMovement(0, -1, -1, -1);
  //performMovement(2048, -1, -1, -1);  
  //performMovement(3048, -1, -1, -1);
}
