#ifndef Temperatursensor_H
#define Temperatursensor_H
 
#include "OneWire.h"
#include "DallasTemperature.h"
 
class Temperatursensor {
    private:
        int pin1;
        OneWire* oneWire;
        DallasTemperature* sensors;
 
        float lastTemperature;
        bool initialized;
 
    public:
        Temperatursensor(int pin1);
        ~Temperatursensor();
 
        void begin();
        void loop();
 
        float getTemperature();     // Letzte gemessene Temperatur zurückgeben
        bool isValid();             // Prüft ob Messung gültig ist (kein -127 / 85°C Fehler)
        void requestTemperature();  // Messung manuell anstoßen
};
 
#endif