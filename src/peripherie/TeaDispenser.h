#ifndef TeaDispenser_h
#define TeaDispenser_h

#include "Dispenser.h"

class TeaDispenser: public Dispenser {
    private:
        int pinOut;
        int pinIn;
        int count; 
        int amount;     
    public:
        TeaDispenser(int pinOut, int pinIn);
        virtual void dispense(int amount);
        virtual void loop();            
};
#endif