#ifndef Waterlevel_H
#define Waterlevel_H

#include <Arduino.h>

class Waterlevel {
    private:
        int pin1;               // RX-Pin (empfängt Daten vom Sensor)
        int pin2;               // TX-Pin (nicht aktiv genutzt, aber reserviert)
        int thresholdLow;       // Unterer Schwellwert in mm (z.B. Tank leer)
        int thresholdHigh;      // Oberer Schwellwert in mm  (z.B. Tank voll)

        int lastDistance;       // Letzte gemessene Distanz in mm
        bool initialized;
        bool valid;             // True wenn letzte Messung gültig war

        HardwareSerial* sensorSerial;  // UART-Port (Serial1, Serial2, Serial3)

        bool readSensor();      // Liest und validiert das 4-Byte Paket

    public:
        Waterlevel(int pin1, int pin2, HardwareSerial& serial,
                   int thresholdLow, int thresholdHigh);

        void begin();
        void loop();

        int  getDistance();     // Distanz in mm
        bool isValid();         // Letzte Messung gültig?
        bool isBelowLow();      // Distanz > thresholdHigh  → Tank leer  (Sensor misst von oben)
        bool isAboveHigh();     // Distanz < thresholdLow   → Tank voll
        bool isInRange();       // Distanz zwischen den Schwellwerten
};

#endif