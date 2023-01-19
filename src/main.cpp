#include <Arduino.h>
#include "Controller.h"

Controller controller;

void commandHandler(String *parameters, int parameter_amount) {
  if(parameter_amount >= 1) {
    if(parameters[0] == "DISP") {
      if(parameters[1] == "zwetschge") {
        // zwetschge.dispense(parameters[2].toInt());
      }
    }
  }
  
  for(int i = 0; i < parameter_amount; i++) {
      Serial.print("Parameter ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(parameters[i]);
  }
}

void setup() {
  Serial.begin(115200);
  controller.begin(GPIO_NUM_41, GPIO_NUM_42);
  controller.listen(commandHandler);
}

void loop() {
  controller.loop();
}