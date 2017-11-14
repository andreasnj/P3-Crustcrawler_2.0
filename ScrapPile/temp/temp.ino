#include <SoftwareSerial.h>;
SoftwareSerial mySerial(10, 11); // RX, TX

int rssi;

void serialFlush()
{
while(mySerial.available() > 0)
char t = mySerial.read();
}

void setup()
{
Serial.begin(9600);
mySerial.begin(9600);
}

void loop()
{
rssi=0;
if(mySerial.available())
{
serialFlush();
mySerial.print("+++");
while(!mySerial.available());
serialFlush();
mySerial.println("ATDB");

while(mySerial.available())
{
rssi = mySerial.read();
Serial.print(rssi);
Serial.print(" ");
}
Serial.println("");

mySerial.print("ATCN");
}
delay(1000);
}
