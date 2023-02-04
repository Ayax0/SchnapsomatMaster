#include <Arduino.h>
#include "Controller.h"
#include "peripherie/GenericDispenser.h"
#include "peripherie/TeaDispenser.h"
#include "peripherie/WaterDispenser.h"

HardwareSerial SerialPort(1);

Controller Schnapsomat_Ctrl(GPIO_NUM_41, GPIO_NUM_42);

GenericDispenser FluidPump1(1, 4500);
GenericDispenser FluidPump2(2, 4500);
GenericDispenser FluidPump3(3, 3000);

GenericDispenser Powder1(6, 500);
GenericDispenser Powder2(7, 500);

TeaDispenser Balls1(10, 19);
TeaDispenser Balls2(11, 20);


WaterDispenser Water(GPIO_NUM_4, GPIO_NUM_5);

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);
  Water.begin();


  // Muss dies hier noch Entfernt werden?
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);

  Schnapsomat_Ctrl.registerDispenser(0, &Water);
  Schnapsomat_Ctrl.registerDispenser(1, &FluidPump1);
  Schnapsomat_Ctrl.registerDispenser(2, &FluidPump2);
  Schnapsomat_Ctrl.registerDispenser(3, &FluidPump3);
  Schnapsomat_Ctrl.registerDispenser(4, &Powder1);
  Schnapsomat_Ctrl.registerDispenser(5, &Powder2);
  Schnapsomat_Ctrl.registerDispenser(6, &Balls1);
  Schnapsomat_Ctrl.registerDispenser(7, &Balls2);

}

void loop() {
  Schnapsomat_Ctrl.loop();
}