////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   CrustCrawler PIN Setup:  Green wire to PIN 10,                                                                           //
//                            Yellow wire to PIN 11,                                                                          //
//                            Black wire to ground,                                                                           //
//                            Red wire to 3.3v,                                                                               //
//                            Blue wire to PIN2                                                                               //
//                                                                                                                            //
//          Xbee PIN Setup:   Green wire -> Rx to PIN 19,                                                                     //
//                            White1 wire -> GND to GND,                                                                      //
//                            Blue wire -> 5v to 5v,                                                                          //
//                            White2 -> RST to RST,                                                                           //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

int x, y, z, emg1, emg2, g, h;
int emgcounter = 0;
int i = 2148;
int j = 2048;
int k = 2048;
int green = 0;
int infoPk[24];
void actualName(){
  if(Serial1.available() >= 24){
    if (Serial1.read() == 0x7E){
          for (int i = 0; i < 24 ; i++){
            byte jelly = Serial1.read();
            infoPk[i] = jelly;
          }
          
while(z < 300 && h==0){
    green++;
    h++;
    break;
  }

  if(z > 460 && z < 470){
    h=0;
    
  }
  /*
  while(green = 1 && y > 700){
    i = i + 20;
    Dynamixel.setNGoalPositions(i, -1, -1, -1, -1);
    break;
  }
  while(green = 1 && y < 300){
    i = i - 20;
    Dynamixel.setNGoalPositions(i, -1, -1, -1, -1);
    break;
  }
  while(green = 2 && y > 700){
    j = j + 20;
    Dynamixel.setNGoalPositions(-1, j, -1, -1, -1);
    break;
  }
  while(green = 2 && y < 300){
    j = j - 20;
    Dynamixel.setNGoalPositions(-1, j, -1, -1, -1);
    break;
  }
  while(green = 3 && y > 700){
    k = k + 20;
    Dynamixel.setNGoalPositions(-1, -1, k, -1, -1);
    break;
  }
  while(green = 3 && y < 300){
    k = k - 20;
    Dynamixel.setNGoalPositions(-1, -1, k, -1, -1);
    break;
  }
  */

      
  while(emg1 > 500 && emg1 < 1024 && g==0 && emgcounter==0){
    Dynamixel.performMovement(2148, 2048, 2048, OPEN);   //"Initial" position
    //delay(1000);
    Dynamixel.performMovement(1142, 3250, 775, OPEN);     //Ready position
    //delay(1000);
    Dynamixel.performMovement(1128, 3250, 1846, OPEN);      //Move to sponge. 
    //delay(1000);
    //Dynamixel.gripper(CLOSE);                               //Grab
    Dynamixel.performMovement(1128, 3250, 1846, CLOSE);     //Detour
    //delay(500);
    Dynamixel.performMovement(1608, 2639, 2467, CLOSE);     //Move to destination
    //delay(500);
    //Dynamixel.gripper(OPEN);                                //Release
    //delay(500);
    Dynamixel.performMovement(2108, 3088, 2018, CLOSE);
    g++;
    emgcounter++;
    break;
    }
    while(emg2 > 500 && emg2 < 1024 && g==0 && emgcounter==1){
    Dynamixel.performMovement(1608, 2639, 2467, CLOSE);     //Move to destination
    //delay(500);
    Dynamixel.performMovement(1128, 3250, 1846, CLOSE);     //Detour
    //delay(500);
    Dynamixel.performMovement(1128, 3250, 1846, OPEN);      //Move to sponge. 
    //delay(1000);
    Dynamixel.performMovement(1142, 3250, 775, OPEN);     //Ready position
    //delay(1000);
    Dynamixel.performMovement(2148, 2048, 2048, CLOSE);   //"Initial" position
    //delay(1000);
    g++;
    emgcounter--;
    break;
    }
  if(emg1 < 100 && emg2 < 100){
    g=0;
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
    Serial.print(" green = ") && Serial.print(green);
    Serial.println();
 }
  }
 }

void loop() {
  actualName();
}
