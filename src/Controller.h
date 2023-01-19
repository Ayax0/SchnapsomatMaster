#ifndef Controller_h
#define Controller_h

#include <Arduino.h>

#define PACKET_ACK 0x00
#define PACKET_NACK 0x01
#define PACKET_OK 0x10
#define PACKET_NOK 0x11
#define PACKET_CMD 0x20
#define PACKET_DATA 0x21

class Controller {
    private:
        HardwareSerial* SerialPort;
        void (*pipeline)(String *parameters, int parameter_amount);
        int getParameterAmount(String src, char delimiter = ' ');
        void proccessCommand(String src, char delimiter, String *parameters);
    public:
        Controller();
        void begin(int rx, int tx);
        void listen(void (*pipeline)(String *parameters, int parameter_amount));
        void loop();
};

#endif