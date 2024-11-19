#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);  // start serial communication
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World!");
  delay(1000);  // wait 1000 ms
}