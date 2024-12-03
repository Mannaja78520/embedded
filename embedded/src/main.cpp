#include <Arduino.h>

#define Relay  23

void setup()
{
  pinMode(Relay, OUTPUT);
}

void loop()
{
  digitalWrite(Relay, HIGH);
  delay(5000); // Wait for 5000 millisecond(s)
  digitalWrite(Relay,LOW);
  delay(5000); // Wait for 5000 millisecond(s)
}