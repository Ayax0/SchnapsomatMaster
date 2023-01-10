#ifndef Dispenser_h
#define Dispenser_h

class Dispenser{
    private:
        int pin;
        long unit_size;
        long end_timestamp;        
    public:
        Dispenser(int pin, long unit_size);
        void dispense(int amount);
        void loop();            
};
#endif
