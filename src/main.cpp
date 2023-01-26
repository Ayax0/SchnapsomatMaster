#include <Arduino.h>
#include "FluidPump.h"
#include "Controller.h"
#include "Dispenser.h"
#include "WaterDispenser.h"

HardwareSerial SerialPort(1);

Controller controller(GPIO_NUM_41, GPIO_NUM_42);

FluidPump fluidPump1(1, 500);
FluidPump fluidPump2(2, 500);
FluidPump fluidPump3(3, 500);

WaterDispenser water(GPIO_NUM_4, GPIO_NUM_5);

long last_cmd = 0;

void commandHandler(StaticJsonDocument<300> packet) {
  digitalWrite(10, HIGH);
  last_cmd = millis();

  JsonObject data = packet["data"].as<JsonObject>();
  if(data["action"] == "DISP") {
    String ingredience = data["ingredience"];
    int amount = data["amount"].as<int>();
    if(ingredience == "vodka") fluidPump1.dispense(amount);
    if(ingredience == "zwaetschgen") fluidPump2.dispense(amount);
    if(ingredience == "traesch") fluidPump3.dispense(amount);
  }
}

void setup() {
  Serial.begin(115200);
  controller.listen(commandHandler);

  pinMode(10, OUTPUT);

  delay(2000);
  water.dispense(1);
}

void loop() {
  controller.loop();
  fluidPump1.loop();
  fluidPump2.loop();
  fluidPump3.loop();

  if(millis() > (last_cmd + 500)) {
    digitalWrite(10, LOW);
  }
}