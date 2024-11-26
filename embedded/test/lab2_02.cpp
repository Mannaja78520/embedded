#include <Arduino.h>

#define transister 23

void setup()
{
  pinMode(transister, OUTPUT);
}

void loop()
{
  digitalWrite(transister, HIGH);
  delay(5000);
  digitalWrite(transister, LOW);
  delay(5000);
}