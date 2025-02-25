#include <Wire.h>
#include <AS5600.h>
#include <Arduino.h>
#include <Adafruit_BusIO_Register.h>
 
AS5600 as5600;
#define DIR_PIN 2
 
int angle_in = 0;
 
void setup() {
pinMode(DIR_PIN, OUTPUT);
Serial.begin(115200);
Wire.begin();
}
 
int Angle() {
digitalWrite(DIR_PIN, HIGH);
int in;
in = map(as5600.rawAngle(),0,4095,0,360);
return in;
}
 
void loop() {
if (as5600.detectMagnet() == 1 ) {
if (angle_in != Angle()) {
angle_in = Angle();
Serial.println(angle_in);
}
}
 

}

