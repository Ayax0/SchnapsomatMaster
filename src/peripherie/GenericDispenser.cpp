#include <Arduino.h>
#include "GenericDispenser.h"

GenericDispenser::GenericDispenser(int pin, long unit_size) {
    this->pin = pin;
    this->unit_size = unit_size;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void GenericDispenser::dispense(int amount) {
    end_timestamp = millis() + amount * unit_size;
}

void GenericDispenser::loop() {
    if(millis() < end_timestamp) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}