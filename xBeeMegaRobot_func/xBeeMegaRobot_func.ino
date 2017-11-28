#include <readxBee.h>
#include <Dynamixel_Serial.h>

#define xBee_Baudrate 115200
#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_BAUDRATE 115200    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define OPEN 'o'
#define CLOSE 'c'

void setup(){
  Serial2.begin(xBee_Baudrate);
  Serial1.begin(SERVO_BAUDRATE);
  Serial.begin(SERVO_BAUDRATE);
  Dynamixel.begin(SERVO_BAUDRATE);
  Dynamixel.setDirectionPin(SERVO_ControlPin);
  xBee.begin(Serial2);
  Serial.flush();
  Serial2.flush();
  while(! Serial2){ }
  Serial.println("reset");
  delay(500);
  Serial1.flush();

  //Turn off hold, so we can modify EEPROM
  Dynamixel.setHoldingTorque(0x01, false);               //Set on hold torque for each servo
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
  Dynamixel.setProfileVelocity(0x01, 100);              //Set profile vel for each servo 
  Dynamixel.setProfileVelocity(0x02, 100);
  Dynamixel.setProfileVelocity(0x03, 100);
  Dynamixel.setProfileVelocity(0x04, 200);
  Dynamixel.setProfileVelocity(0x05, 200);  
}

int tempPk[24] = {};
int x=0, y=0, z=0, emg1=0, emg2=0;
int pass = 0;
int fail = 0;
float rate;

void loop() {
  for(int i = 0; i < 100; i++){
  xBee.readPacket(tempPk);
  //xBee.decodePacket(tempPk); //This compiles, but doesn't seem to work
  x = tempPk[14] + (tempPk[13] << 8);
  y = tempPk[16] + (tempPk[15] << 8);
  z = tempPk[18] + (tempPk[17] << 8);
  emg1 = tempPk[20] + (tempPk[19] << 8);
  emg2 = tempPk[22] + (tempPk[21] << 8);
  Serial.print("x = "); Serial.print(x); //Printing the received data
  Serial.print(" y = "); Serial.print(y);
  Serial.print(" z = "); Serial.print(z);
  Serial.print(" emg1 = "); Serial.print(emg1);
  Serial.print(" emg2 = "); Serial.print(emg2);

    if(xBee.checkPacket(tempPk)){ //Check and print if the package passed
      Serial.println("| INT -- PASS |"); pass++;
      }else{Serial.println("| INT -- FAIL |"); fail++;
    }
  }
  Serial.println(pass); //Print the pass and fail counts and rate
  Serial.println(fail);
  rate = (float)pass/(pass+fail);
  Serial.println(rate*100);

  //This is the part where it moves
  Dynamixel.performMovement(2148, 2048, 2048, CLOSE);   //"Initial" position
  delay(1500);
  Dynamixel.performMovement(2148, 1850, 3250, OPEN);     //Ready position
  delay(2000);

  Dynamixel.performMovement(1600, 2800, 3200, OPEN);      //Move to sponge
  Dynamixel.gripper(CLOSE);                               //Grab
  Serial.println("DEBUG!");
  Dynamixel.performMovement(2148, 1850, 3250, CLOSE);     //Detour
  Dynamixel.performMovement(2650, 2800, 3200, CLOSE);     //Move to destination
  delay(500);
  Dynamixel.gripper(OPEN);                                //Release
delay(500);

}
