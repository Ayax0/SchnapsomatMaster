#ifndef Controller_h
#define Controller_h

#include <Arduino.h>
#include <ArduinoJson.h>

#define PACKET_ACK 0x00
#define PACKET_NACK 0x01
#define PACKET_OK 0x10
#define PACKET_NOK 0x11
#define PACKET_CMD 0x20
#define PACKET_DATA 0x21

class Controller {
    private:
        HardwareSerial* SerialPort;
        bool ready = false;
        void (*pipeline)(StaticJsonDocument<300> packet);
        int getParameterAmount(String src, char delimiter = ' ');
        void proccessCommand(String src, char delimiter, String *parameters);
    public:
        Controller(int rx, int tx);
        void listen(void (*pipeline)(StaticJsonDocument<300> packet));
        void loop();
};

#endif