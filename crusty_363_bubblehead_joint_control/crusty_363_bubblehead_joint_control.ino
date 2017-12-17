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
#define OPEN 'o'
#define CLOSE 'c'

SoftwareSerial mySerial(10, 11);    // RX, TX

void setup() {
  Serial1.begin(115200);
  mySerial.begin(SERVO_SET_Baudrate);                   // We now need to set Ardiuno to the new Baudrate speed 115200
  Serial.begin(SERVO_SET_Baudrate);                                  // Start serial communication on baudrate 57600
  Dynamixel.begin(mySerial);                            // Calling mySerial function which sets 10 pin as the 2nd RX serial pin, and sets pin 11 as the 2nd TX serial pin
  Dynamixel.setDirectionPin(SERVO_ControlPin);          // Optional. Set direction control pin which controls if the program writes or reads
  Serial.flush();                                       // Clear the serial buffer of garbage data before running the code.

  //Turn on hold for the servos, so they stay in place
  Dynamixel.setHoldingTorque(0x01, true);               //Set on hold turque for each servo
  Dynamixel.setHoldingTorque(0x02, true);
  Dynamixel.setHoldingTorque(0x03, true);
  Dynamixel.setHoldingTorque(0x04, true);
  Dynamixel.setHoldingTorque(0x05, true);

  //Set profile acceleration
  Dynamixel.setProfileAcceleration(0x01, 7);           //Set profile acc for each servo
  Dynamixel.setProfileAcceleration(0x02, 7);
  Dynamixel.setProfileAcceleration(0x03, 7);
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
unsigned int i = 2540; //Starting positions
unsigned int j = 2050;
unsigned int k = 2042;
int joint = 4;
int infoPk[24];
void actualName(){
  xBee.readPacket(infoPk);

  if(xBee.checkPacket(infoPk)){
    Serial.println("package passed");
    Serial.println(infoPk[0]);
    Serial.println(infoPk[1]);
    Serial.println(infoPk[2]);
    Serial.println(infoPk[23]);
    }
    else{Serial.println("package failed");
    }
/*
  if(Serial1.available() >= 24){
    if (Serial1.read() == 0x7E){
          for (int i = 0; i < 24 ; i++){
            byte temp = Serial1.read();
            infoPk[i] = temp;
          }

  int sum = 0;
  for(int i = 3; i < 23; i++){       //Generate sum from index 3-to-22 (until, not incl. the checksum itself)
    sum += infoPk[i];
  }

  sum = sum % 256;


  Serial.println(sum);
  Serial.println(infoPk[23]);
  if((255 - sum) == infoPk[23]){         //Check with the checksum of the package
      Serial.println("package passed");  //ok, good package
  }
  else{
      Serial.println("package failed");  //error
  }
*/

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
  if(z >= 400 && z <= 470){                         //Sets it back to the original position and the counter to 0
    jointexcess_prevention=0;
    }
while(joint == 1 && y > 650 && z > 300 && z < 700){                        //Tilting forward moves joint 1 down
  i = i + 10;
  if(i > 3200){
    i = 3200;
  }
  Dynamixel.setGoalPosition(1, i);
  break;
}
while(joint == 1 && y < 400 && z > 300 && z < 700){                        //Tilting backward moves joint 1 up
  i = i - 10;
  if(i < 800){
  i = 800;
  }  
  Dynamixel.setGoalPosition(1, i);
  break;
}
while(joint == 2 && y > 650 && z > 300 && z < 700){                        //Tilting forward moves joint 2 down
  j = j + 10;
  if(j > 3200){
  j = 3200;
  }
  Dynamixel.setGoalPosition(2, j);
  break;
}
while(joint == 2 && y < 400 && z > 300 && z < 700){                        //Tilting backward moves joint 2 up
  j = j - 10;
  if(j < 800){
  j = 800;
  }
  Dynamixel.setGoalPosition(2, j);
  break;
}
while(joint == 3 && y > 650 && z > 300 && z < 700){                        //Tilting forward moves joint 3 down
  k = k + 10;
  if(k > 3200){
  k = 3200;
  }
  Dynamixel.setGoalPosition(3, k);
  break;
}
while(joint == 3 && y < 400 && z > 300 && z < 700){                        //Tilting backward moves joint 3 up
  k = k - 10;
  if(k < 800){
  k = 800;
  }
  Dynamixel.setGoalPosition(3, k);
  break;
}
while(joint == 4 && y > 650 && z > 300 && z < 700){                        //Tilting forward opens the gripper
   Dynamixel.gripper(OPEN);
   break;
}
while(joint == 4 && y < 400 && z > 300 && z < 700){                        //Tilting backward closes the gripper
   Dynamixel.gripper(CLOSE);
   break;
}

  z = infoPk[14] + (infoPk[13] << 8);
  y = infoPk[16] + (infoPk[15] << 8);
  x = infoPk[18] + (infoPk[17] << 8);
  
  //Serial.print(" X = ") && Serial.print(x);
  Serial.print(" Y = ") && Serial.print(y);
  Serial.print(" Z = ") && Serial.print(z);
  Serial.print(" joint number = ") && Serial.print(joint);
  Serial.println();
}
// }
//}

void loop() {
  actualName();
}
