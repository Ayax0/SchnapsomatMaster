#ifndef WaterDispenser_h
#define WaterDispenser_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ESP32Servo.h>

class WaterDispenser {
    private:
        int pin_pump;
        int pin_vent;
        int status = 0;

        TwoWire wire = TwoWire(0);
        Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, wire);
        Servo servo;
    public:
        WaterDispenser(int pin_pump, int pin_vent);
        void dispense(int amount);
        void loop();
};

#endif