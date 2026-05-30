#include "Temperatursensor.h"

Temperatursensor::Temperatursensor(int pin1) {
    this->pin1 = pin1;
    this->lastTemperature = -999.0;
    this->initialized = false;

    oneWire = new OneWire(pin1);
    sensors = new DallasTemperature(oneWire);
}

// -------------------------------------------------------
// Destruktor: Speicher freigeben
// -------------------------------------------------------
Temperatursensor::~Temperatursensor() {
    delete sensors;
    delete oneWire;
}

void Temperatursensor::begin() {
    sensors->begin();
    initialized = true;
}

// -------------------------------------------------------
// loop(): In loop() aufrufen — liest Temperatur periodisch
// Messung wird alle 1000ms neu angefordert
// -------------------------------------------------------
void Temperatursensor::loop() {
    if (!initialized) return;

    static unsigned long lastRequest = 0;
    unsigned long now = millis();

    if (now - lastRequest >= 1000) {
        lastRequest = now;
        sensors->requestTemperatures();
        lastTemperature = sensors->getTempCByIndex(0);
    }
}

// -------------------------------------------------------
// getTemperature(): Zuletzt gemessene Temperatur in °C
// -------------------------------------------------------
float Temperatursensor::getTemperature() {
    return lastTemperature;
}

// -------------------------------------------------------
// isValid(): Filtert typische DS18B20 Fehlerwerte heraus
//   -127.0 = kein Sensor / Kurzschluss
//    85.0  = Power-On-Reset Wert (noch keine echte Messung)
// -------------------------------------------------------
bool Temperatursensor::isValid() {
    return (lastTemperature != -999.0 &&
            lastTemperature != DEVICE_DISCONNECTED_C &&   // -127.0
            lastTemperature != 85.0);
}

// -------------------------------------------------------
// requestTemperature(): Messung manuell anstoßen
// (z.B. wenn du nicht loop() nutzt)
// -------------------------------------------------------
void Temperatursensor::requestTemperature() {
    if (!initialized) return;
    sensors->requestTemperatures();
    lastTemperature = sensors->getTempCByIndex(0);
}