#include "Waterlevel.h"

// -------------------------------------------------------
// Konstruktor
// pin1        = RX-Pin (Daten vom Sensor)
// pin2        = TX-Pin (reserviert, A02YYUW sendet nur)
// serial      = HardwareSerial Port z.B. Serial1, Serial2
// thresholdLow  = Distanz in mm → Tank gilt als LEER  (grosser Wert = wenig Wasser)
// thresholdHigh = Distanz in mm → Tank gilt als VOLL  (kleiner Wert = viel Wasser)
// -------------------------------------------------------
Waterlevel::Waterlevel(int pin1, int pin2, HardwareSerial& serial,
                       int thresholdLow, int thresholdHigh) {
    this->pin1          = pin1;
    this->pin2          = pin2;
    this->thresholdLow  = thresholdLow;
    this->thresholdHigh = thresholdHigh;
    this->lastDistance  = -1;
    this->initialized   = false;
    this->valid         = false;
    this->sensorSerial  = &serial;
}

// -------------------------------------------------------
// begin(): In setup() aufrufen
// A02YYUW kommuniziert mit 9600 Baud
// -------------------------------------------------------
void Waterlevel::begin() {
    sensorSerial->begin(9600);
    initialized = true;
}

void Waterlevel::loop() {
    if (!initialized) return;
    readSensor();
}

// -------------------------------------------------------
// readSensor(): Liest das 4-Byte Protokoll des A02YYUW
//
// Protokoll: 0xFF | H-Byte | L-Byte | Checksum
// Checksum  = (0xFF + H + L) & 0x00FF
// Distanz   = (H << 8) | L  → in mm
// Gültig:   100mm – 450mm
// -------------------------------------------------------
bool Waterlevel::readSensor() {
    // Warten bis mindestens 4 Bytes verfügbar
    if (sensorSerial->available() < 4) return false;

    // Auf Startbyte 0xFF synchronisieren
    if (sensorSerial->read() != 0xFF) return false;

    // Verbleibende 3 Bytes lesen
    uint8_t h        = sensorSerial->read();
    uint8_t l        = sensorSerial->read();
    uint8_t checksum = sensorSerial->read();

    // Checksum prüfen
    uint8_t calculated = (0xFF + h + l) & 0x00FF;
    if (checksum != calculated) {
        valid = false;
        return false;
    }

    int distance = (h << 8) | l;

    // Gültigkeitsbereich des Sensors: 100mm – 450mm
    if (distance < 100 || distance > 450) {
        valid = false;
        return false;
    }

    lastDistance = distance;
    valid = true;
    return true;
}

// -------------------------------------------------------
// getDistance(): Letzte gültige Distanz in mm
// -------------------------------------------------------
int Waterlevel::getDistance() {
    return lastDistance;
}

// -------------------------------------------------------
// isValid(): True wenn letzte Messung gültig war
// -------------------------------------------------------
bool Waterlevel::isValid() {
    return valid;
}

// -------------------------------------------------------
// isBelowLow(): Distanz > thresholdLow → Tank leer
// (Sensor sitzt oben → grosse Distanz = wenig Wasser)
// -------------------------------------------------------
bool Waterlevel::isBelowLow() {
    if (!valid) return false;
    return lastDistance > thresholdLow;
}

// -------------------------------------------------------
// isAboveHigh(): Distanz < thresholdHigh → Tank voll
// -------------------------------------------------------
bool Waterlevel::isAboveHigh() {
    if (!valid) return false;
    return lastDistance < thresholdHigh;
}

// -------------------------------------------------------
// isInRange(): Wasserstand zwischen den Schwellwerten
// -------------------------------------------------------
bool Waterlevel::isInRange() {
    if (!valid) return false;
    return (lastDistance >= thresholdHigh && lastDistance <= thresholdLow);
}