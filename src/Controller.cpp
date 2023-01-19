#include <ArduinoJson.h>
#include "Controller.h"
#include "Packet.h"

Controller::Controller(int rx, int tx) {
    SerialPort = new HardwareSerial(1);
    SerialPort->begin(115200, SERIAL_8N1, rx, tx);
    ready = true;
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
                // TODO: Packet Processor

                if(ready) Packet(PACKET_OK).exec(SerialPort);
                else Packet(PACKET_NOK).exec(SerialPort);
            }
        } else {
            Serial.print("SerializationError: ");
            Serial.println(error.c_str());

            while(SerialPort->available() > 0) SerialPort->read();
        }
    }
}