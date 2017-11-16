#include <readxBee.h>
#include <Dynamixel_Serial.h>

#define xBee_Baudrate 115200
#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_BAUDRATE 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
//#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
//#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define OPEN 'o'
#define CLOSE 'c'

char testPk[24] = {0x7e, 0x00, 0x14, 0x83, 0x56, 0x78, 0x43, 0x00, 0x01, 0x3e,
                    0xe0, 0x00, 0x40, 0x02, 0x9b, 0x02, 0x1a, 0x02, 0x05, 0x00,
                    0x00, 0x00, 0x05, 0x47};  // from datasheet

int tempPk[24] = {};
char charPk[24] = {};

/*void performMovement(int goal1, int goal2, int goal3, char forGripper){
  Dynamixel.setNGoalPositions(goal1, goal2, goal3, -1, -1);
  while(!((goal2 >= pos2-11) && (goal2 <= pos2+11)) && ((goal3 >= pos3-11) && (goal3 <= pos3+11)) && ((goal1 >= pos1-11) && (goal1 <= pos1+11))){ //error for +- 1 degree due to an inaccuracy of the motors
    pos1 =  Dynamixel.getPosition(0x01);
    pos2 =  Dynamixel.getPosition(0x02);
    pos3 =  Dynamixel.getPosition(0x03); 
  }

    Dynamixel.setProfileVelocity(0x01, 0);  //Set the Profile Velocity for each servo. (max. is 1023)
    Dynamixel.setProfileVelocity(0x02, 0);
    Dynamixel.setProfileVelocity(0x03, 0);
    Dynamixel.gripper(forGripper);
    delay(500);
    Dynamixel.setProfileVelocity(0x01, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
    Dynamixel.setProfileVelocity(0x02, 100);
    Dynamixel.setProfileVelocity(0x03, 100);
    delay(1000);
}*/

void setup() {
  Serial2.begin(SERVO_BAUDRATE);
  Serial1.begin(xBee_Baudrate);
  Serial.begin(SERVO_BAUDRATE);
  Dynamixel.begin(Serial2);
  Dynamixel.setDirectionPin(SERVO_ControlPin);
  xBee.begin(Serial1);
  Serial.flush();
  Serial1.flush();
  Serial2.flush();
  while(! Serial1){ }
  Serial.println("reset");
  delay(500);

   // Turn on hold on the servos:
  Dynamixel.setHoldingTorque(0x01, true);  //Turn on hold torque on servo 1
  Dynamixel.setHoldingTorque(0x02, true);
  Dynamixel.setHoldingTorque(0x03, true);
  Dynamixel.setHoldingTorque(0x04, true);
  Dynamixel.setHoldingTorque(0x05, true);

  // Set the Profile acceleration.
  Dynamixel.setProfileAcceleration(0x01, 10);  //Set the Profile Acceleration for each servo. (max. is 32767)
  Dynamixel.setProfileAcceleration(0x02, 10);
  Dynamixel.setProfileAcceleration(0x03, 10);
  Dynamixel.setProfileAcceleration(0x04, 300);
  Dynamixel.setProfileAcceleration(0x05, 300);

  // Set the Profile velocity.
  Dynamixel.setProfileVelocity(0x01, 100);  //Set the Profile Velocity for each servo. (max. is 1023)
  Dynamixel.setProfileVelocity(0x02, 100);
  Dynamixel.setProfileVelocity(0x03, 100);
  Dynamixel.setProfileVelocity(0x04, 200);
  Dynamixel.setProfileVelocity(0x05, 200);
}

void loop() {
  /*xBee.readPacket(tempPk); //Trying reading and checking with int packages
  for(int i = 0; i < 24; i++){
    Serial.println(tempPk[i], HEX);
  }
  if(xBee.checkPacket(tempPk)){
    Serial.println("INT package passed checksum");
  }else{Serial.println("INT package did not pass");};*/

  xBee.readPacket(charPk); //Trying reading and checking with char packages
  for(int i = 0; i < 24; i++){
    Serial.println(charPk[i], HEX);
  }
  if(xBee.checkPacket(charPk)){
    Serial.println("CHAR package passed checksum");
    }else{Serial.println("CHAR package did not pass");};

  xBee.reducePacket(charPk);
  Serial.println("Reduced package:");
  for(int i = 0; i < 24; i++){
    Serial.println(charPk[i], HEX);
  }
  if(xBee.checkPacket(charPk)){
    Serial.println("REDUCED CHAR package passed checksum");
    }else{Serial.println("REDUCED CHAR package did not pass");};
    
  delay(10000);
}
