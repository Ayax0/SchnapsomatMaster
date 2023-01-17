#include <Arduino.h>
#include "Water.h"
#include <WaterPump.h>

Water water(0,GPIO_NUM_5,2000,90,0);
WaterPump waterPump(GPIO_NUM_4);


