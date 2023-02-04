#include <Arduino.h>
#include "TeaDispenser.h"

TeaDispenser::TeaDispenser(int pinOut, int pinIn) {
    this->pinOut = pinOut;
    this->pinIn = pinIn;
    this->last_state = 0;

    pinMode(pinOut, OUTPUT);
    pinMode(pinIn, INPUT_PULLDOWN);
    digitalWrite(pinOut, LOW);
}

void TeaDispenser::dispense(int amount) {
    this->amount += amount;
}

void TeaDispenser::loop() {
    int sensor_state = digitalRead(pinIn);
    if(sensor_state == HIGH && last_state == LOW) {
        amount--;
        last_state = sensor_state;
    }

    if(amount > 0) {
        digitalWrite(pinOut, HIGH);
    } else {
        digitalWrite(pinOut, LOW);
    }    
}