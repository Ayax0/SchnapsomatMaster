#include <Arduino.h>
#include "TeaDispenser.h"

TeaDispenser::TeaDispenser(int pinOut, int pinIn) {
    this->pinOut = pinOut;
    this->pinIn = pinIn;
    this->last_state = LOW;
    this->current_state = LOW;

    pinMode(pinOut, OUTPUT);
    pinMode(pinIn, INPUT);
    digitalWrite(pinOut, LOW);
}

void TeaDispenser::dispense(int amount) {
    this->amount += amount;
}

void TeaDispenser::loop() {
    int sensor_state = digitalRead(pinIn);
     if(sensor_state != last_state && sensor_state == HIGH) {
        last_state = sensor_state;
        amount--;
    }

    if(amount > 0 && current_state == LOW) {
        current_state = HIGH;
        digitalWrite(pinOut, HIGH);
    }
    if(amount <= 0 && current_state == HIGH) {
        current_state = LOW;
        digitalWrite(pinOut, LOW);
    }    
}

