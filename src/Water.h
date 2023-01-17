#ifndef Water_h
#define Water_h

#define SERVO_FREQ 50

#include <Adafruit_PWMServoDriver.h>

class Water {
    private:
        Adafruit_PWMServoDriver* servo;
        int pin_servo;
        int pin_magnet;
        
        long unit_size;
        long end_timestamp;
        int servo_position_open;
        int servo_position_close;
        bool signal_magnetic_valve;
    public:
        Water(int pin_servo, int pin_magnet, long unit_size, int servo_position_open, int servo_position_close );
        void dispense(int amount);
        void loop();
};
#endif