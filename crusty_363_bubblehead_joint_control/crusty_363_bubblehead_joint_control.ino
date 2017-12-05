/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
///   For this function, the xBee transmitter has to be   ///
/// placed on the side of the head with the batery facing /// 
///      outward and the EMG outputs facing forward.      ///
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
  Dynamixel.setHoldingTorque(0x01, false);               //Set on hold turque for each servo
  Dynamixel.setHoldingTorque(0x02, false);
  Dynamixel.setHoldingTorque(0x03, false);
  Dynamixel.setHoldingTorque(0x04, false);
  Dynamixel.setHoldingTorque(0x05, true);

  //Set profile acceleration
  Dynamixel.setProfileAcceleration(0x01, 50);           //Set profile acc for each servo
  Dynamixel.setProfileAcceleration(0x02, 50);
  Dynamixel.setProfileAcceleration(0x03, 50);
  Dynamixel.setProfileAcceleration(0x04, 100);
  Dynamixel.setProfileAcceleration(0x05, 100);

  //Set profile velocity
  Dynamixel.setProfileVelocity(0x01, 50);              //Set profile vel for each servo
  Dynamixel.setProfileVelocity(0x02, 50);
  Dynamixel.setProfileVelocity(0x03, 50);
  Dynamixel.setProfileVelocity(0x04, 100);
  Dynamixel.setProfileVelocity(0x05, 100);
 }

int x, y, z, jointexcess_prevention;
int i = 2148;
int j = 2048;
int k = 2048;
int joint = 1;
int infoPk[24];
void actualName(){
  if(Serial1.available() >= 24){
    if (Serial1.read() == 0x7E){
          for (int i = 0; i < 24 ; i++){
            byte jelly = Serial1.read();
            infoPk[i] = jelly;
          }

while(z < 300 && z > 200 && jointexcess_prevention==0 && x > 0 && x < 1000 && y > 0 && y < 1000){                              //Tilting the head to the right moves on to the next joint && h prevents from excessive joint counting.
    joint++;
    jointexcess_prevention++;
    if(joint > 4){
      joint = 4;
    }
    break;
}
while(z > 600 && z < 700 && jointexcess_prevention==0 && x > 0 && x < 1000 && y > 0 && y < 1000){                              //Tilting the head to the left moves on to the previous joint
   joint--;
   jointexcess_prevention++;
   if(joint < 1){
    joint = 1;
   }
   break;
}
  if(z >= 420 && z <= 470){                         //Sets it back to the original position and the counter to 0
    jointexcess_prevention=0;
    }
while(joint == 1 && y > 650 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting forward moves joint 1 down
  i = i + 10;
  Dynamixel.setNGoalPositions(i, -1, -1, -1, -1);
  break;
}
while(joint == 1 && y < 400 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting backward moves joint 1 up
  i = i - 10;
  Dynamixel.setNGoalPositions(i, -1, -1, -1, -1);
  break;
}
while(joint == 2 && y > 650 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting forward moves joint 2 down
  j = j + 10;
  Dynamixel.setNGoalPositions(-1, j, -1, -1, -1);
  break;
}
while(joint == 2 && y < 400 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting backward moves joint 2 up
  j = j - 10;
  Dynamixel.setNGoalPositions(-1, j, -1, -1, -1);
  break;
}
while(joint == 3 && y > 650 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting forward moves joint 3 down
  k = k + 10;
  Dynamixel.setNGoalPositions(-1, -1, k, -1, -1);
  break;
}
while(joint == 3 && y < 400 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting backward moves joint 3 up
  k = k - 10;
  Dynamixel.setNGoalPositions(-1, -1, k, -1, -1);
  break;
}
while(joint == 4 && y > 650 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting forward opens the gripper
   Dynamixel.gripper(OPEN);
   break;
}
while(joint == 4 && y < 400 && z > 300 && z < 700 && x > 0 && x < 1000){                        //Tilting backward closes the gripper
   Dynamixel.gripper(CLOSE);
   break;
}

for(int a = 13; a < 24; a++) {
  z = infoPk[13] + (infoPk[12] << 8);
  y = infoPk[15] + (infoPk[14] << 8);
  x = infoPk[17] + (infoPk[16] << 8);
}
  //Serial.print(" X = ") && Serial.print(x);
  Serial.print(" Y = ") && Serial.print(y);
  Serial.print(" Z = ") && Serial.print(z);
  Serial.print(" joint number= ") && Serial.print(joint);
  Serial.println();
  }
 }
}

void loop() {
  actualName();
}
