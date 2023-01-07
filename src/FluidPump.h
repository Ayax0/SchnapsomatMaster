#ifndef FluidPump_h
#define FluidPump_h

class FluidPump {
    private:
        int pin;
        long unit_size;
        long end_timestamp;
    public:
        FluidPump(int pin, long unit_size);
        void dispense(int amount);
        void loop();
};
#endif