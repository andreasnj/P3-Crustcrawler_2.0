#include <Dynamixel_Serial.h>
#include <readxBee.h>
#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full control buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define xBEE_SET_Baudrate 115200
#define OPEN 'o'
#define CLOSE 'c'

SoftwareSerial mySerial(10, 11);

int x, y, z, emg1, emg2, emgsignal_counter, jointcounter;
int i = 2148;
int j = 2048;
int k = 2048;
int joint = 2;
bool gripperState = false; // false = closed

void checkSum(){
  int infoPk[24];
  }

void movements(){
  checkSum();

  while (emg1 < 150 && emg2 < 150 && z > 300 && z < 700){
    if (y > 600){
      i = i + 10;}
    else if (y < 400){
      i = i - 10;}
    else break;
    Dynamixel.setGoalPosition(1, i);  
  };

  while(emg1 > 150 && emg1 < 600 && y < 700 && y > 300 && z > 300 && z < 700){    //Set the emg1 to move the joints up in a cycle from 2 to 3
    if (emgsignal_counter == 0 && jointcounter == 0){
      joint++;
      jointcounter++;}
    else if (emgsignal_counter == 0 && jointcounter == 1){
      joint--;
      jointcounter--;}
    else break;
    emgsignal_counter++;
    };

  while(z > 550 && y < 700 && y > 300 && emg1 < 100 && emg2 < 100){
    if (joint == 2){
      j = j + 10;
      Dynamixel.setGoalPosition(joint, j);}
    else if (joint == 3){
      k = k + 10;
      Dynamixel.setGoalPosition(joint, k);}
    else break;
    };

  while(z < 300 && y < 700 && y > 300 && emg1 < 100 && emg2 < 100){
    if (joint == 2){
      j = j - 10;
      Dynamixel.setGoalPosition(joint, j);}
    else if (joint == 3){
      k = k - 10;
      Dynamixel.setGoalPosition(joint, k);}
    else break;
    };

  while (emg2 > 0 && emg2 < 600 && emgsignal_counter==0 && y < 700 && y > 300 && emg1 < 100 && z > 300 && z < 700){   //Opens the gripper using the Emg2
    if (!gripperState){
      Dynamixel.gripper(OPEN);
      gripperState = true;}  
    else if (gripperState){
      Dynamixel.gripper(CLOSE);
      gripperState = false;}
    else break;
    };  

  if(emg1 < 100 && emg2 == 0){                                         //Set the emg2 to open and close the gripper
    emgsignal_counter=0;
}
}

void setup(){
  Serial1.begin(xBEE_SET_Baudrate);
  mySerial.begin(SERVO_SET_Baudrate);                   // We now need to set Ardiuno to the new Baudrate speed 115200
  Serial.begin(SERVO_SET_Baudrate);                                  // Start serial communication on baudrate 57600
  Dynamixel.begin(mySerial);                            // Calling mySerial function which sets 10 pin as the 2nd RX serial pin, and sets pin 11 as the 2nd TX serial pin
  Dynamixel.setDirectionPin(SERVO_ControlPin);          // Optional. Set direction control pin which controls if the program writes or reads

  //Turn on hold for the servos, so they stay in place
  Dynamixel.setHoldingTorque(0x01, true);               //Set on hold turque for each servo
  Dynamixel.setHoldingTorque(0x02, true);
  Dynamixel.setHoldingTorque(0x03, true);
  Dynamixel.setHoldingTorque(0x04, true);
  Dynamixel.setHoldingTorque(0x05, true);

  //Set profile acceleration
  Dynamixel.setProfileAcceleration(0x01, 0);           //Set profile acc for each servo
  Dynamixel.setProfileAcceleration(0x02, 0);
  Dynamixel.setProfileAcceleration(0x03, 0);
  Dynamixel.setProfileAcceleration(0x04, 100);
  Dynamixel.setProfileAcceleration(0x05, 100);

  //Set profile velocity
  Dynamixel.setProfileVelocity(0x01, 50);              //Set profile vel for each servo
  Dynamixel.setProfileVelocity(0x02, 50);
  Dynamixel.setProfileVelocity(0x03, 50);
  Dynamixel.setProfileVelocity(0x04, 100);
  Dynamixel.setProfileVelocity(0x05, 100);
  }

void loop(){
  movements();  
  }
