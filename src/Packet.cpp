#include "Packet.h"

Packet::Packet(int id) {
    this->packet["id"] = id;
    this->data = packet.createNestedObject("data");
}

void Packet::exec(HardwareSerial* SerialPort) {
    serializeJson(packet, *SerialPort);
}