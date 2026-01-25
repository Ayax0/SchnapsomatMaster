#ifndef OutletDispenser_h
#define OutletDispenser_h

#include "Dispenser.h"

class OutletDispenser: public Dispenser {
    private:
        int pin1;
        int pin2;
        long unit_size;
        unsigned long start_delay_time;
        long end_timestamp; 
        bool isWaiting = false;
        bool isRunning = false;       
    public:
        OutletDispenser(int pin1, int pin2, long unit_size);
        virtual void dispense(int amount);
        virtual void loop();            
};
#endif