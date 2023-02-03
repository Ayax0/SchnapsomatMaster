#ifndef GenericDispenser_h
#define GenericDispenser_h

#include "Dispenser.h"

class GenericDispenser: public Dispenser {
    private:
        int pin;
        long unit_size;
        long end_timestamp;        
    public:
        GenericDispenser(int pin, long unit_size);
        virtual void dispense(int amount);
        virtual void loop();            
};
#endif
