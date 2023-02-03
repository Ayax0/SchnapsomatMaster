#ifndef Dispenser_h
#define Dispenser_h

class Dispenser {
    public:
        virtual void dispense(int amount) = 0;
        virtual void loop() = 0;
};
#endif