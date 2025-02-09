#include <Arduino.h>
#define LDR  35    // use gpio36 or Analog 1 pin for input
#define LED 4

int LDR_Value = 0;
int static_variable = 250;

void setup() {
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  Serial.begin(115200);
}

void loop() {
  LDR_Value = analogRead(LDR);

  // Serial.print("Variable_1:");
  if (LDR_Value <= static_variable) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
  Serial.print(">LDR_Value: ");
  Serial.println(LDR_Value);
  Serial.println(LDR_Value);
  // Serial.print(",");
  // Serial.print("Variable_2:");
  // Serial.println(static_variable);
  delay(20);
}