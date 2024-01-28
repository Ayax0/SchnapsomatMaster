#include <Arduino.h>
#include "Controller.h"
#include "peripherie/GenericDispenser.h"
#include "peripherie/TeaDispenser.h"
#include "peripherie/WaterDispenser.h"

Controller Schnapsomat_Ctrl(&Serial3);

GenericDispenser FluidPump1(28, 3000); //1cl Vodka
GenericDispenser FluidPump2(36, 3100); //1cl Zwätsche
GenericDispenser FluidPump3(44, 3000); //1cl Träsch

GenericDispenser Powder1(45, 1400); //Zucker
GenericDispenser Powder2(53, 200); //Kaffee

// TeaDispenser Balls1(10, 19); //Hagenbutte
// TeaDispenser Balls2(11, 20); //Pfefferminze


WaterDispenser Water(29, 37, &Serial2);

void setup() {
  // Logging
  Serial.begin(115200);

  Water.begin();
  Schnapsomat_Ctrl.begin();
  Schnapsomat_Ctrl.registerDispenser(0, &Water);
  Schnapsomat_Ctrl.registerDispenser(1, &FluidPump1);
  Schnapsomat_Ctrl.registerDispenser(2, &FluidPump2);
  Schnapsomat_Ctrl.registerDispenser(3, &FluidPump3);
  Schnapsomat_Ctrl.registerDispenser(4, &Powder1);
  Schnapsomat_Ctrl.registerDispenser(5, &Powder2);
  // Schnapsomat_Ctrl.registerDispenser(6, &Balls1);
  // Schnapsomat_Ctrl.registerDispenser(7, &Balls2);

  Serial.println("Status: OK");
}

void loop() {
  Schnapsomat_Ctrl.loop();
}