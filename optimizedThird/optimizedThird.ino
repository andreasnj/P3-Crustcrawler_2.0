#include <Dynamixel_Serial.h>
#include <readxBee.h>
#include <SoftwareSerial.h>

#define SERVO_ControlPin 0x02       // Control pin of buffer chip, NOTE: this does not matter becasue we are not using a half to full control buffer.
#define SERVO_SET_Baudrate 57600    // Baud rate speed which the Dynamixel will be set too (57600)
#define xBEE_SET_Baudrate 115200
#define OPEN 'o'
#define CLOSE 'c'

SoftwareSerial mySerial(10, 11);

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
