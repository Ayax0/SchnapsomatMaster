#include "WaterDispenser.h"

WaterDispenser::WaterDispenser(int pin_pump, int pin_vent) {
    this->pin_pump = pin_pump;
    this->pin_vent = pin_vent;

    pinMode(11, OUTPUT);
    
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);
    servo.setPeriodHertz(50);
    servo.attach(11, 500, 2400);

    pinMode(pin_pump, OUTPUT);
    pinMode(pin_vent, OUTPUT);
}

void WaterDispenser::dispense(int amount) {
    digitalWrite(pin_pump, HIGH);
    delay(1000);
    digitalWrite(pin_pump, LOW);

    for(int pos = 0; pos <= 180; pos++) {
        servo.write(pos);
        delay(20);
    }
}