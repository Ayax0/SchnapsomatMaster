#include "WaterDispenser.h"

WaterDispenser::WaterDispenser(int pin_pump, int pin_vent, HardwareSerial* serial) {
    this->pin_pump = pin_pump;
    this->pin_vent = pin_vent;
    this->SerialPort = serial;

    pinMode(pin_pump, OUTPUT);
    pinMode(pin_vent, OUTPUT);
}

void WaterDispenser::begin() {
    SerialPort->begin(1000000);
    servo.pSerial = SerialPort;
    delay(10);

    digitalWrite(pin_pump, HIGH);
    pump_status = true;

    digitalWrite(pin_vent, LOW);
    vent_status = true;

    closeServo();

    delay(1000);
    servo.EnableTorque(1, 0);
}

void WaterDispenser::loop() {
    s16 servo_pos = servo.ReadPos(1);
    if(servo_pos == -1) return;
    // Serial.println(servo_pos);

    if(dispense_amount > 0) {
        if(dispense_position == 0) {
            dispense_position = 1;
            sleep = millis() + 500;
            digitalWrite(pin_vent, HIGH);
        }
        if(dispense_position == 1 && millis() > sleep) {
            dispense_position = 2;
            sleep = millis() + 1000;
            openServo();
        }
        if(dispense_position == 2 && millis() > sleep) {
            dispense_position = 3;
            sleep = millis() + 500;
            closeServo();
        }
        if(dispense_position == 3 && millis() > sleep) {
            dispense_position = 4;
            sleep = millis() + 1500;
            digitalWrite(pin_vent, LOW);
        }
        if(dispense_position == 4 && millis() > sleep) {
            dispense_amount--;
            dispense_position = 0;
            sleep = 0;
            servo.EnableTorque(1, 0);
        }
    }
}

void WaterDispenser::dispense(int amount) {
    dispense_amount += amount;
}

void WaterDispenser::openServo() {
    servo.EnableTorque(1, 1);
    servo.WritePos(1, SERVO_OPEN, 0, 1500);
}

void WaterDispenser::closeServo() {
    servo.EnableTorque(1, 1);
    servo.WritePos(1, SERVO_CLOSE, 0, 1500);
}