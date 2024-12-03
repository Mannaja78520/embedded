#include <Arduino.h>

#define MOTOR  23

void setup()
{
  pinMode(MOTOR, OUTPUT);
}

void loop()
{
  digitalWrite(MOTOR, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(MOTOR,LOW);
  delay(5000); // Wait for 5000 millisecond(s)
}