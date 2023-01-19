#include <ArduinoJson.h>
#include "Controller.h"
#include "Packet.h"

Controller::Controller() {
    SerialPort = new HardwareSerial(1);
}

void Controller::begin(int rx, int tx) {
    SerialPort->begin(115200, SERIAL_8N1, rx, tx);
}

void Controller::listen(void (*pipeline)(String *parameters, int parameter_amount)) {
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
            }
        } else {
            Serial.print("SerializationError: ");
            Serial.println(error.c_str());

            while(SerialPort->available() > 0) SerialPort->read();
        }

        Packet(PACKET_OK).exec(SerialPort);
    }
}