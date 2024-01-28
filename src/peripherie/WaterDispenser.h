#ifndef WaterDispenser_h
#define WaterDispenser_h

#include <SCServo.h>
#include "Dispenser.h"

#define SERVO_CLOSE 25
#define SERVO_OPEN 400

class WaterDispenser: public Dispenser {
    private:
        int pin_pump;
        int pin_vent;

        bool pump_status;
        bool vent_status;

        int dispense_amount = 0;
        int dispense_position = 0;
        unsigned long sleep = 0;

        HardwareSerial* SerialPort;
        SCSCL servo;

        void openServo();
        void closeServo();
    public:
        WaterDispenser(int pin_pump, int pin_vent, HardwareSerial* serial);
        void begin();
        virtual void loop();
        virtual void dispense(int amount);
};
#endif