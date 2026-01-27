#include <Arduino.h>
#include "OutletDispenser.h"

OutletDispenser::OutletDispenser(int pin1, int pin2, long unit_size) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->unit_size = unit_size;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
}

void OutletDispenser::dispense(int amount) {
    start_timestamp = millis() + 1500;
    end_timestamp = start_timestamp + amount * unit_size;
}

void OutletDispenser::loop() {
    unsigned long now = millis();
    if(now > start_timestamp && now < end_timestamp) {
        digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    } else {
        digitalWrite(pin1, LOW);
        digitalWrite(pin2, LOW);
    }
}
