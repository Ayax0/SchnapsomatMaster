#include <ArduinoJson.h>
#include "Controller.h"
#include "Packet.h"

Controller::Controller(int rx, int tx) {
    SerialPort = new HardwareSerial(1);
    SerialPort->begin(9600, SERIAL_8N1, rx, tx);
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
                
                Packet(PACKET_OK).exec(SerialPort);
            }
        } else {
            Serial.print("SerializationError: ");
            Serial.println(error.c_str());

            while(SerialPort->available() > 0) SerialPort->read();
        }

        // if(cmd.length() > 0) {
        //     int parameter_amount = getParameterAmount(cmd, CONTROLLER_DELIMITER);
        //     String parameters[parameter_amount];
        //     proccessCommand(cmd, CONTROLLER_DELIMITER, parameters);

        //     if(pipeline != NULL) pipeline(parameters, parameter_amount);
        // }
    }
}