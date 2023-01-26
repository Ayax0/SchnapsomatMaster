#include <ArduinoJson.h>
#include "Controller.h"
#include "Packet.h"

Controller::Controller(int rx, int tx) {
    SerialPort = new HardwareSerial(1);
    SerialPort->begin(9600, SERIAL_8N1, rx, tx);
    ready = true;
    pipeline = NULL;
}

void Controller::listen(void (*pipeline)(StaticJsonDocument<300> packet)) {
    this->pipeline = pipeline;
}

void Controller::loop() {
    if(SerialPort->available()) {
        StaticJsonDocument<300> packet;
        DeserializationError error = deserializeJson(packet, *SerialPort);
        
        if(error == DeserializationError::Ok) {
            if(packet["id"] == PACKET_CMD) {
                Packet(PACKET_ACK).exec(SerialPort);

                Serial.print("Reveived Data: ");
                Serial.println(packet["data"].as<String>());
                if(pipeline != NULL) this->pipeline(packet);

                if(ready) Packet(PACKET_OK).exec(SerialPort);
                else Packet(PACKET_NOK).exec(SerialPort);
            }
        } else {
            Serial.print("SerializationError: ");
            Serial.println(error.c_str());

            digitalWrite(10, HIGH);
            delay(100);
            digitalWrite(10, LOW);
            delay(100);
            digitalWrite(10, HIGH);
            delay(100);
            digitalWrite(10, LOW);
            delay(100);
            digitalWrite(10, HIGH);
            delay(100);
            digitalWrite(10, LOW);
            delay(100);

            Packet(PACKET_NACK).exec(SerialPort);
        }
    }
}