 #ifndef WaterPump_h
 #define WaterPump_h

 class WaterPump {
    private:
        int pin;
        long unit_size;
        bool state;
    public:
        WaterPump(int pin);
        void dispense(bool state);
        void loop();
 };
 #endif