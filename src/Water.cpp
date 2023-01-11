#include <Arduino.h>
#include "Water.h"
#include <Adafruit_PWMServoDriver.h>

Water::Water(int pin_servo, int pin_magnet, long unit_size, int servo_position_open, int servo_position_close ) {
    this->pin_servo = pin_servo;
    this->pin_magnet = pin_magnet;    
    this->unit_size = unit_size;
    this->servo_position_open = servo_position_open;
    this->servo_position_close = servo_position_close;

    pinMode(pin_servo, OUTPUT);
    pinMode(pin_magnet, OUTPUT);
    digitalWrite(pin_servo, LOW);
    digitalWrite(pin_magnet, LOW);
}

Adafruit_PWMServoDriver pwm_servo = Adafruit_PWMServoDriver(0x40);

void setup(){
    pwm_servo.begin();
    pwm_servo.setOscillatorFrequency(27000000);
    pwm_servo.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
}

void setServoPulse(uint8_t n, double pulse) {
    double pulselength;
  
    pulselength = 1000000;   // 1,000,000 us per second
    pulselength /= SERVO_FREQ;   // Analog servos run at ~50 Hz updates
    Serial.print(pulselength); Serial.println(" us per period"); 
    pulselength /= 65535;  // 12 bits of resolution 65535
    Serial.print(pulselength); Serial.println(" us per bit"); 
    pulse *= 1000000;  // convert input seconds to us
    pulse /= pulselength;
    Serial.println(pulse);
    pwm_servo.setPWM(n, 0, pulse);
}

void Water::dispense(int amount) {
    end_timestamp = millis() + amount * unit_size;
}

void Water::loop() {
    if(millis() < end_timestamp) {
        digitalWrite(pin_magnet, HIGH);
        pwm_servo.writeMicroseconds(pin_servo, servo_position_open);
    } else {
        digitalWrite(pin_magnet, LOW);
        pwm_servo.writeMicroseconds(pin_servo, servo_position_close);
    }

}