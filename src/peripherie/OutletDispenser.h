#ifndef OutletDispenser_h
#define OutletDispenser_h

#include "Dispenser.h"

class OutletDispenser: public Dispenser {
    private:
        int pin1;
        int pin2;
        long unit_size;
        long start_timestamp;
        long end_timestamp;       
    public:
        OutletDispenser(int pin1, int pin2, long unit_size);
        virtual void dispense(int amount);
        virtual void loop();            
};
#endif