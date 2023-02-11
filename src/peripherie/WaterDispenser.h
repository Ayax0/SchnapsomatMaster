#ifndef WaterDispenser_h
#define WaterDispenser_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Dispenser.h"

#define SERVO_CLOSE 600
#define SERVO_OPEN 150

class WaterDispenser: public Dispenser {
    private:
        int pin_pump;
        int pin_vent;

        bool pump_status;
        bool vent_status;
        bool servo_status;

        int dispense_amount = 0;
        int dispense_position = 0;
        int sleep = 0;

        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

        void openServo();
        void closeServo();
    public:
        WaterDispenser(int pin_pump, int pin_vent);
        void begin();
        virtual void loop();
        virtual void dispense(int amount);
};
#endif