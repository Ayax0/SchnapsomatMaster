#include <Arduino.h>
#include "Controller.h"
#include "peripherie/GenericDispenser.h"
#include "peripherie/OutletDispenser.h"

Controller Schnapsomat_Ctrl(&Serial3);

GenericDispenser FluidPump1(53, 52, 340); //1cl Vodka
GenericDispenser FluidPump2(51, 50, 340); //1cl Zwätsche
GenericDispenser FluidPump3(49, 48, 340); //1cl Träsch

GenericDispenser FluidPump4(45, 44, 340); //Zucker
GenericDispenser FluidPump5(43, 42, 340); //Kaffee

GenericDispenser FluidPump6(41, 40, 340); //Hagenbutte
GenericDispenser FluidPump7(39, 38, 340); //Pfefferminze


GenericDispenser FluidPump8(47, 46, 365); //Wasser

OutletDispenser FluidPump9(37, 36, 10600); //Auslass

void setup() {
  // Logging
  Serial.begin(115200);

  Schnapsomat_Ctrl.begin();
  Schnapsomat_Ctrl.registerDispenser(0, &FluidPump1);
  Schnapsomat_Ctrl.registerDispenser(1, &FluidPump2);
  Schnapsomat_Ctrl.registerDispenser(2, &FluidPump3);
  Schnapsomat_Ctrl.registerDispenser(3, &FluidPump4);
  Schnapsomat_Ctrl.registerDispenser(4, &FluidPump5);
  Schnapsomat_Ctrl.registerDispenser(5, &FluidPump6);
  Schnapsomat_Ctrl.registerDispenser(6, &FluidPump7);
  Schnapsomat_Ctrl.registerDispenser(7, &FluidPump8);
  Schnapsomat_Ctrl.registerDispenser(8, &FluidPump9);

  Serial.println("Status: OK");
}

void loop() {
  Schnapsomat_Ctrl.loop();
}