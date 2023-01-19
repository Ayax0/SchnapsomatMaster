#include <Arduino.h>
#include "WaterPump.h"

WaterPump::WaterPump (int pin) {
    this->pin = pin;

    pinMode(pin, OUTPUT);
    digitalWrite(pin,LOW);
}

void WaterPump::dispense(bool state) {
    this->state = state;
}

void WaterPump::loop() {
    if(state = true) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}
