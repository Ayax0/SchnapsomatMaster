#include "Controller.h"

Controller::Controller(int rx, int tx) {
    SerialPort = new HardwareSerial(1);
    SerialPort->begin(9600, SERIAL_8N1, rx, tx);

    this->frame_position = 0;
	this->max_frame_length = max_frame_length;
	this->receive_frame_buffer = (uint8_t *)malloc(max_frame_length+1);
    this->frame_checksum = CRC16_CCITT_INIT_VAL;
    this->escape_character = false;
}

void Controller::loop() {
    while(SerialPort->available()) {
        char inChar = (char)SerialPort->read();
        charReceiver(inChar);
    }

    for(uint8_t i = 0; i < MAX_DISPENSER_AMOUNT; i++) {
        if(dispenser_registry[i] != NULL) dispenser_registry[i]->loop();
    }
}

void Controller::registerDispenser(uint8_t index, Dispenser *dispenser) {
    this->dispenser_registry[index] = dispenser;
}

// HDLC
void Controller::receiveBuffer(Buffer buffer) {
    // cmd packet
    if(buffer.readUInt8(0) == 0x01) {
        // dispense packet
        if(buffer.readUInt8(1) == 0x00) {
            uint8_t index = buffer.readUInt8(2);
            uint8_t amount = buffer.readUInt8(3);
            
            if(dispenser_registry[index] != NULL) dispenser_registry[index]->dispense(amount);
        }
    }
}

void Controller::charReceiver(uint8_t data) {
    if(data == FRAME_BOUNDARY_OCTET) {
        if(this->escape_character == true) this->escape_character = false;
        else if((this->frame_position >= 2) && (this->frame_checksum == ((this->receive_frame_buffer[this->frame_position-1] << 8 ) | (this->receive_frame_buffer[this->frame_position-2] & 0xff)))) {
            (receiveBuffer)(Buffer(receive_frame_buffer));
        }
        this->frame_position = 0;
        this->frame_checksum = CRC16_CCITT_INIT_VAL;
        return;
    }

    if(this->escape_character) {
        this->escape_character = false;
        data ^= INVERT_OCTET;
    }
    else if(data == CONTROL_ESCAPE_OCTET) {
        this->escape_character = true;
        return;
    }

    receive_frame_buffer[this->frame_position] = data;

    if(this->frame_position-2 >= 0) {
        this->frame_checksum = _crc_ccitt_update(this->frame_checksum, receive_frame_buffer[this->frame_position-2]);
    }

    this->frame_position++;

    if(this->frame_position == this->max_frame_length) {
        this->frame_position = 0;
        this->frame_checksum = CRC16_CCITT_INIT_VAL;
    }
}

void Controller::charSender(uint8_t data) {
    SerialPort->print((char) data);
}

void Controller::sendBuffer(Buffer buffer) {
    uint8_t *framebuffer = buffer.toArray();
    uint8_t frame_length = buffer.size();
    uint8_t data;
    uint16_t fcs = CRC16_CCITT_INIT_VAL;

    this->charSender((uint8_t)FRAME_BOUNDARY_OCTET);

    while(frame_length) {
        data = *framebuffer++;
        fcs = _crc_ccitt_update(fcs, data);
        if((data == CONTROL_ESCAPE_OCTET) || (data == FRAME_BOUNDARY_OCTET)) {
            this->charSender((uint8_t)CONTROL_ESCAPE_OCTET);
            data ^= INVERT_OCTET;
        }
        this->charSender((uint8_t)data);
        frame_length--;
    }
    data = low(fcs);
    if((data == CONTROL_ESCAPE_OCTET) || (data == FRAME_BOUNDARY_OCTET)) {
        this->charSender((uint8_t)CONTROL_ESCAPE_OCTET);
        data ^= (uint8_t)INVERT_OCTET;
    }
    this->charSender(data);
    data = high(fcs);
    if((data == CONTROL_ESCAPE_OCTET) || (data == FRAME_BOUNDARY_OCTET)) {
        this->charSender(CONTROL_ESCAPE_OCTET);
        data ^= INVERT_OCTET;
    }
    this->charSender(data);
}