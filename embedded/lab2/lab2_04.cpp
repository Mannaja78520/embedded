#include <Arduino.h>
#include <motor_esp.h>
#include <Adafruit_BusIO_Register.h>


#define motor1PWM 23 
#define motor1PinA 22 
#define motor1PinB 19 
#define LED1 5 
#define LED2 18 

Motor motor1(20000, 8, 0, 1, motor1PWM, motor1PinA, motor1PinB);


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
}

void loop() {
  motor1.spin(255);
  digitalWrite(LED1, HIGH);
  delay(5000);
  motor1.brake();
  digitalWrite(LED1, LOW);
  delay(1000);
  motor1.spin(-255);
  digitalWrite(LED2, HIGH);
  delay(3000);
  motor1.brake();
  digitalWrite(LED2, LOW);
  delay(1000);
}