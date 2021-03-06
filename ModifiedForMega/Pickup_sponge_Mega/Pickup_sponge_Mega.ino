//This program should be run to set the servos to some standard initial positions.
//USE ONLY WITH MEGA
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// How to run it: upload to arduino with the dynamixel_serial library installed in your arduino libraries folder.             //
//                After upload, disconnect usb from arduino and add power to CrustCrawler and the arduino board.              //
//                The program should start by it self. :)
//                                                                                                                            //
//                PIN Setup:  Green wire to PIN 10,                                                                           //
//                            Yellow wire to PIN 11,                                                                          //
//                            Black wire to ground,                                                                           //
//                            Red wire to 5v,                                                                                 //
//                            Blue wire to PIN2                                                                               //
//                                                                                                                            //
//                This code was developed in collaboration with several groups, to enable all the groups a good               //
//                base code to start programming the CrustCrawler from. ;)                                                    //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include "Dynamixel_Serial.h"
//#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full contorl buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define LED13 0x0D
#define CW_LIMIT_ANGLE 0x001        // lowest clockwise angle is 1, as when set to 0 it set servo to wheel mode
#define CCW_LIMIT_ANGLE 0xFFF       // Highest anit-clockwise angle is 0XFFF, as when set to 0 it set servo to wheel mode
#define OPEN 'o'
#define CLOSE 'c'

//SoftwareSerial mySerial(10, 11);    // RX, TX

void setup() {
  Serial1.begin(SERVO_SET_Baudrate);                   // Set Ardiuno to the new Baudrate speed 1152
  Serial.begin(SERVO_SET_Baudrate);                    // Start serial communication on baudrate 57600
  Serial.flush();                                      // Clear the serial buffer of garbage data.
  Serial1.flush();
  Dynamixel.begin(Serial1);                            // Calling mySerial function which sets 10 pin as the 2nd RX serial pin, and sets pin 11 as the 2nd TX serial pin
  Dynamixel.setDirectionPin(SERVO_ControlPin);         // Optional. Set direction control pin which controls if the program writes or reads

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

void loop() {

/*// If the robot is mounted with the 2nd joint tuned 180deg
  Dynamixel.performMovement(2148, 2048, 2048, CLOSE);   //"Initial" position
  delay(3000);
  Dynamixel.performMovement(2148, 2300, 800, OPEN);     //Ready position
  delay(3000);
*/

  Dynamixel.performMovement(2148, 2048, 2048, CLOSE);   //"Initial" position
  delay(1500);
  Dynamixel.performMovement(2148, 1850, 3250, OPEN);     //Ready position
  delay(2000);

  Dynamixel.performMovement(1600, 2800, 3200, OPEN);      //Move to sponge
  Dynamixel.gripper(CLOSE);                               //Grab
  Dynamixel.performMovement(2148, 1850, 3250, CLOSE);     //Detour
  Dynamixel.performMovement(2650, 2800, 3200, CLOSE);     //Move to destination
  delay(500);
  Dynamixel.gripper(OPEN);                                //Release
delay(500);
}
