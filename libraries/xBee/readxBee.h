#ifndef readxBee_h
#define readxBee_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

#define START                       0x7E
#define LENGTH_H                    0x00
#define LENGTH_L                    0x14
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

#define CHECKSUM                    0x47*/

class xBeeClass {
public:
    //xBeeClass(); //constructor

    //to initialize Serial communication
    void begin(long);
    void begin(HardwareSerial&, long);
    void begin(Stream&);

    Stream *_serial;
<<<<<<< HEAD
    //Used to be private members from here down
=======

    void decodePacket(char *pk, int i);
    float averageArr(int *arr);

    //Used to be private from here down
>>>>>>> 22a70389119a2e1ac98d498edee9302d7ebd8b63
    void readPacket(char *pk);
    void printReturn(char *pk);
    bool checkPacket(char *pk);
    void decodePacket(char *pk);


    //Global variables
    unsigned char pk[24]; //Packet array
    int emg1;
    int emg2;
    int accZ;
    int accY;
    int accX;

    int emg1arr[10] = {};
    int emg2arr[10] = {};
    int accZarr[10] = {};
    int accYarr[10] = {};
    int accXarr[10] = {};

};

extern xBeeClass xBee;

#endif
