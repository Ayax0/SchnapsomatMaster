#include <Arduino.h>
#include "TeaDispenser.h"

TeaDispenser::TeaDispenser(int pinOut, int pinIn) {
    this->pinOut = pinOut;
    this->pinIn = pinIn;
    
    pinMode(pinOut, OUTPUT);
    pinMode(pinIn, INPUT_PULLDOWN);
    digitalWrite(pinOut, LOW);
}

void TeaDispenser::dispense(int amount) {
    this->amount = amount;
}



void TeaDispenser::loop() {    
    if (pinIn == HIGH) {
        count++;
    }

    if( count < amount) {
        digitalWrite(pinOut,HIGH);
    } else {
        digitalWrite(pinOut, LOW);
    }    
}