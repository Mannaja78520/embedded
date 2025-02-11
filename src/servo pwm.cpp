#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>
#include <ESP32Servo.h>
Servo myservo;
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33
int servoPin = 18;
int pos = 0;
void setup() {
  myservo.attach(servoPin);
}
void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}