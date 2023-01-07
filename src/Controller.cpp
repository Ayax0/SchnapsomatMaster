#include "Controller.h"

Controller::Controller(int rx, int tx) {
    SerialPort = new HardwareSerial(1);
    SerialPort->begin(9600, SERIAL_8N1, rx, tx);
}

int Controller::getParameterAmount(String src, char delimiter) {
    int parameter_amount = 1;
    for(int i = 0; i < src.length(); i++) {
        if(src[i] == delimiter) parameter_amount++;
    }
    return parameter_amount;
}

void Controller::proccessCommand(String src, char delimiter, String *parameters) {
    int current_index = 0;
    String current_parameter = "";
    for(int i = 0; i < src.length(); i++) {
        if(src[i] == delimiter) {
            parameters[current_index] = current_parameter;
            current_index++;
            current_parameter = "";
        } else {
            current_parameter += src[i];
        }
    }
    parameters[current_index] = current_parameter;
}

void Controller::listen(void (*pipeline)(String *parameters, int parameter_amount)) {
    this->pipeline = pipeline;
}

void Controller::loop() {
    if(SerialPort->available() > 0) {
        String cmd = SerialPort->readStringUntil(CONTROLLER_ENDOFCMD);

        if(cmd.length() > 0) {
            int parameter_amount = getParameterAmount(cmd, CONTROLLER_DELIMITER);
            String parameters[parameter_amount];
            proccessCommand(cmd, CONTROLLER_DELIMITER, parameters);

            if(pipeline != NULL) pipeline(parameters, parameter_amount);
        }
    }
}