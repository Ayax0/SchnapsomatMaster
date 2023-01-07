#include <Arduino.h>
#include "FluidPump.h"

FluidPump::FluidPump(int pin, long unit_size) {
    this->pin = pin;
    this->unit_size = unit_size;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void FluidPump::dispense(int amount) {
    end_timestamp = millis() + amount * unit_size;
}

void FluidPump::loop() {
    if(millis() < end_timestamp) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}