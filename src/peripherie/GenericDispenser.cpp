#include <Arduino.h>
#include "GenericDispenser.h"

GenericDispenser::GenericDispenser(int pin1, int pin2, long unit_size) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->unit_size = unit_size;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

void GenericDispenser::dispense(int amount) {
    end_timestamp = millis() + amount * unit_size;
}

void GenericDispenser::loop() {
    if (millis() < end_timestamp) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    } else {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
    }
}