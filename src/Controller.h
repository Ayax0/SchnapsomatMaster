#ifndef Controller_h
#define Controller_h

#include <Arduino.h>

#define CONTROLLER_DELIMITER ' '
#define CONTROLLER_ENDOFCMD '$'

class Controller {
    private:
        HardwareSerial* SerialPort;
        void (*pipeline)(String *parameters, int parameter_amount);
        int getParameterAmount(String src, char delimiter = ' ');
        void proccessCommand(String src, char delimiter, String *parameters);
    public:
        Controller(int rx, int tx);
        void listen(void (*pipeline)(String *parameters, int parameter_amount));
        void loop();
};

#endif