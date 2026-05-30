#ifndef Waterfiller_h
#define Waterfiller_h

#include "Dispenser.h"

class Waterfiller : public Dispenser {
    private:
        int pin1;
        int pin2;
        long unit_size;
        long end_timestamp;
        
    public:
        Waterfiller(int pin1, int pin2, long unit_size);
        virtual void dispense(int amount);
        virtual void loop();
};
#endif
