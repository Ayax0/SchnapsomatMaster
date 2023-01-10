#include <Arduino.h>
#include "Dispenser.h"

Dispenser::Dispenser(int pin, long unit_size) {
    this->pin = pin;
    this->unit_size = unit_size;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Dispenser::dispense(int amount) {
    end_timestamp = millis() + amount * unit_size;
}

void Dispenser::loop() {
    if(millis() < end_timestamp) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}