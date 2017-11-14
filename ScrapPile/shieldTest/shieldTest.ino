/*****************************************************************
XBee_Serial_Passthrough.ino

Set up a software serial port to pass data between an XBee Shield
and the serial monitor.

Hardware Hookup:
  The XBee Shield makes all of the connections you'll need
  between Arduino and XBee. If you have the shield make
  sure the SWITCH IS IN THE "DLINE" POSITION. That will connect
  the XBee's DOUT and DIN pins to Arduino pins 2 and 3.

*****************************************************************/
// We'll use SoftwareSerial to communicate with the XBee:
#include <SoftwareSerial.h>
#include <readxBee.h>

// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial mySerial(2, 3); // RX, TX

char tempPk[24] = {};

void setup()
{
  // Set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  mySerial.begin(115200);
  Serial.begin(9600);
  xBee.begin(mySerial);
  while (! Serial){                 // wait until serial port is up and running
  }
  delay(500); // just to be sure
}

void loop()
{
 /* /*if (Serial.available())
  { // If data comes in from serial monitor, send it out to XBee
    XBee.write(Serial.read());
  }*/
  //if (XBee.available())
  //{ // If data comes in from XBee, send it out to serial monitor
    //Serial.println(mySerial.read());
    //mySerial.flush();
    //delay(1000);
  //}*/
   //Ready for new package
  xBee.readPacket(tempPk);

  if(xBee.checkPacket(tempPk)){
  //Do stuff
    Serial.println("The test package passed checksum"); //Needs testing
    }
    else{Serial.println("Does not work");};

    delay (2000);
}

