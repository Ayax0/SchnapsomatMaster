#include "WaterDispenser.h"

WaterDispenser::WaterDispenser(int pin_pump, int pin_vent) {
    this->pin_pump = pin_pump;
    this->pin_vent = pin_vent;

    pinMode(pin_pump, OUTPUT);
    pinMode(pin_vent, OUTPUT);
}

void WaterDispenser::begin() {
    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(50);
    delay(10);

    // digitalWrite(pin_pump, HIGH);
    // pump_status = true;

    digitalWrite(pin_vent, LOW);
    vent_status = true;

    servo_status = true;
    closeServo();
}

void WaterDispenser::loop() {
    if(dispense_amount > 0) {
        if(dispense_position == 0) {
            dispense_position = 1;
            sleep = millis() + 500;
            openServo();
        }
        if(dispense_position == 1 && millis() > sleep) {
            dispense_position = 2;
            sleep = millis() + 1000;
            digitalWrite(pin_vent, HIGH);
        }
        if(dispense_position == 2 && millis() > sleep) {
            dispense_position = 3;
            sleep = millis() + 2000;
            closeServo();
            digitalWrite(pin_vent, LOW);
        }
        if(dispense_position == 3 && millis() > sleep) {
            dispense_amount--;
            dispense_position = 0;
            sleep = 0;
        }
    }
}

void WaterDispenser::dispense(int amount) {
    dispense_amount += amount;
}

void WaterDispenser::openServo() {
    pwm.wakeup();
    if(servo_status) return;
    for(uint16_t pulselen = SERVO_CLOSE; pulselen > SERVO_OPEN; pulselen--) pwm.setPWM(0, 0, pulselen);
    servo_status = true;
    pwm.sleep();
}

void WaterDispenser::closeServo() {
    pwm.wakeup();
    if(!servo_status) return;
    for(uint16_t pulselen = SERVO_OPEN; pulselen < SERVO_CLOSE; pulselen++) pwm.setPWM(0, 0, pulselen);
    servo_status = false;
    pwm.sleep();
}