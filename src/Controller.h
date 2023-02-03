#ifndef Controller_h
#define Controller_h

#include <Arduino.h>
#include "util/crc16.h"
#include "util/Buffer.h"
#include "peripherie/Dispenser.h"

#define MAX_DISPENSER_AMOUNT 32

#define MAX_HDLC_FRAME_LENGTH 32
#define FRAME_BOUNDARY_OCTET 0x7E
#define CONTROL_ESCAPE_OCTET 0x7D
#define INVERT_OCTET 0x20
#define CRC16_CCITT_INIT_VAL 0xFFFF

#define low(x)    ((x) & 0xFF)
#define high(x)   (((x)>>8) & 0xFF)

class Controller {
    private:
        HardwareSerial* SerialPort;
        Dispenser* dispenser_registry[MAX_DISPENSER_AMOUNT];

        void receiveBuffer(Buffer buffer);
        void sendBuffer(Buffer buffer);
        void charReceiver(uint8_t data);
        void charSender(uint8_t data);
        bool escape_character;
        uint8_t* receive_frame_buffer;
        uint8_t frame_position;
        uint16_t frame_checksum;
        uint16_t max_frame_length;
    public:
        Controller(int rx, int tx);
        void loop();

        void registerDispenser(uint8_t index, Dispenser *dispenser);
};

#endif