#ifndef Water_h
#define Water_h

class FluidPump {
    private:
        int pin;
        long unit_size;
        long end_timestamp;
        int servo_position;
        bool signal_magnetic_valve;
    public:
        FluidPump(int pin, long unit_size);
        void dispense(int amount);
        void loop();
};
#endif