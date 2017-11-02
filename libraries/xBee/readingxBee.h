#ifndef readingxBee_h
#define readingxBee_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

#define START                       0x7E
#define MSB                         0x00
#define LSB                         0x14
#define API_FRAME_ID                0x83
#define SENERS_ADDRESS_H            0x56
#define SENDERS_ADDRESS_L           0x78
#define RSI                         0x43
#define OPTION_BYTE                 0x00
#define SAMPLES_NUMBER              0x01
#define CHANNEL_INDICATOR_H         0x3E //channel indicator mask n/a A5 A4 A3 A2 A1 A0 D8
#define CHANNEL_INDICATOR_L         0xE0 //channel indicatot mask  D7 D6 D5 D4 D3 D2 D1 D0
#define DIGITAL_SAMPLE_H            0x00
#define DIGITAL_SAMPLE_L            0x40

#define ACCZ_H                      0x02
#define ACCZ_L                      0x9B

#define ACCY_H                      0x02
#define ACCY_L                      0x1A

#define ACCX_H                      0x02
#define ACCX_L                      0x05

#define EMGCH1_H                    0x00
#define EMGCH1_L                    0x00

#define EMGCH2_H                    0x00
#define EMGCH2_L                    0x05

#define CHECKSUM                    0x47

class xBeeClass {
public:
    //constructor
    xBeeClass(): {} //not sure what should go here

private:
    void readPacket();
    void printReturn();

    unsigned char packet_array[24];
};

extern xBeeClass xBee;

#endif

}
