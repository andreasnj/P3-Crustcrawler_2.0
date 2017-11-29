/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
///      For this function, the xBee transmitter has to   ///
///          be placed on the back of the head.           ///
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

#include <Dynamixel_Serial.h>
#include <readxBee.h>
#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full control buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define OPEN 'o'
#define CLOSE 'c'

SoftwareSerial mySerial(10, 11);    // RX, TX

void setup() {

  Serial.flush();                                       // Clear the serial buffer of garbage data before running the code.
  Serial1.begin(115200);
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

 int x, y, z, emg1, emg2, emgsignal_counter, jointexcess_prevention, jointcounter, grippercounter ;
 int emgcounter = 0;
 int i = 2148;
 int j = 2048;
 int k = 2048;
 int joint = 2;
 int infoPk[24];
 void actualName(){
   if(Serial1.available() >= 24){
     if (Serial1.read() == 0x7E){
           for (int i = 0; i < 24 ; i++){
             byte jelly = Serial1.read();
             infoPk[i] = jelly;
           }

while(y > 700){                                                       //Tilting the head to the right moves joint 1 to the right
  i = i + 10;
  Dynamixel.setNGoalPositions(i, -1, -1, -1, -1);
  break;
}
while(y < 300){                                                       //Tilting the head to the left moves joint 1 to the left
  i = i - 10;
  Dynamixel.setNGoalPositions(i, -1, -1, -1, -1);
  break;
}

while(emg1 > 500 && emg1 < 1024 && emgsignal_counter==0 && jointcounter==0){    //Set the emg1 to move the joints up in a cycle from 2 to 3
  joint++;
  //jointexcess_prevention++;
  jointcounter++;
  emgsignal_counter++;
  break;
  }
while(emg1 > 500 && emg1 < 1024 && emgsignal_counter==0 && jointcounter==1){    //Set the emg1 to move the joints up in a cycle from 2 to 3
  joint--;
  //jointexcess_prevention--;
  jointcounter--;
  emgsignal_counter++;
  break;
  }

while(joint == 2 && z > 700){                                           //Tilting forward moves joint 2 down
  j = j + 10;
  Dynamixel.setNGoalPositions(-1, j, -1, -1, -1);
  break;
}
while(joint == 2 && z < 300){                                          //Tilting backward moves joint 2 up
  j = j - 10;
  Dynamixel.setNGoalPositions(-1, j, -1, -1, -1);
  break;
}
while(joint == 3 && z > 700){                                          //Tilting forward moves joint 3 down
  k = k + 10;
  Dynamixel.setNGoalPositions(-1, -1, k, -1, -1);
  break;
}
while(joint == 3 && z  < 300){                                          //Tilting backward moves joint 3 up
  k = k - 10;
  Dynamixel.setNGoalPositions(-1, -1, k, -1, -1);
  break;
}

while(emg2 > 500 && emg2 < 1024 && emgsignal_counter==0 && emgcounter==0 && grippercounter==0){
Dynamixel.gripper(OPEN);
emgsignal_counter++;
emgcounter++;
grippercounter++;
break;
}
while(emg2 > 500 && emg2 < 1024 && emgsignal_counter==0 && emgcounter==1 && grippercounter==1){
Dynamixel.gripper(CLOSE);
emgsignal_counter++;
emgcounter--;
grippercounter--;
break;
}
if(emg1 < 100 && emg2 < 100){                                         //Set the emg2 to open and close the gripper
  emgsignal_counter=0;
}


for(int a = 13; a < 24; a++) {
  z = infoPk[13] + (infoPk[12] << 8);
  y = infoPk[15] + (infoPk[14] << 8);
  x = infoPk[17] + (infoPk[16] << 8);
  emg1 = infoPk[19] + (infoPk[18] << 8);
  emg2 = infoPk[21] + (infoPk[20] << 8);

 }
  Serial.print(" X = ") && Serial.print(x);
  Serial.print(" Y = ") && Serial.print(y);
  Serial.print(" Z = ") && Serial.print(z);
  Serial.print(" EMG Ch.1 = ") && Serial.print(emg1);
  Serial.print(" EMG Ch.2 = ") && Serial.print(emg2);
  Serial.print(" joint number= ") && Serial.print(joint);
  Serial.println();
}
}
}

void loop() {
actualName();
}
