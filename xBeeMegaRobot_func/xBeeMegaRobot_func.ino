#include <readxBee.h>
#include <Dynamixel_Serial.h>

#define xBee_Baudrate 115200
#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_BAUDRATE 115200    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
//#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
//#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define OPEN 'o'
#define CLOSE 'c'

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

void setup(){
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
}

int tempPk[24] = {};
int x=0, y=0, z=0, emg1=0, emg2=0;
/*int pass = 0;
int fail = 0;
float rate;*/

void loop() {
  for(int i = 0; i < 50; i++){
  xBee.readPacket(tempPk);
  x = tempPk[14] + (tempPk[13] << 8);
  y = tempPk[16] + (tempPk[15] << 8);
  z = tempPk[18] + (tempPk[17] << 8);
  emg1 = tempPk[20] + (tempPk[19] << 8);
  emg2 = tempPk[22] + (tempPk[21] << 8);
  Serial.print("x = "); Serial.print(x);
  Serial.print(" y = "); Serial.print(y);
  Serial.print(" z = "); Serial.print(z);
  Serial.print(" emg1 = "); Serial.print(emg1);
  Serial.print(" emg2 = "); Serial.print(emg2);  
  /*
  for(int i = 13; i <= 22; i++){
    Serial.print(tempPk[i], DEC);  // Printing the read package
    Serial.print(" ");
  }*/

  if(xBee.checkPacket(tempPk)){ //Check and print if the package passed
    Serial.println("| INT -- PASS |");
    //pass++;
    }else{Serial.println("| INT -- FAIL |");
    //fail++;};
  }
/*  Serial.println(pass); //Print the pass and fail coutns and rate
  Serial.println(fail);
  rate = (float)pass/(pass+fail);
  Serial.println(rate*100);*/
  }
}
