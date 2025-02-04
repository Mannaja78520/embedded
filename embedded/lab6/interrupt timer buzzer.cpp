#include <Arduino.h>
#include <motor_esp.h>
#include <Wire.h>
#include <WiFi.h>
#include <MQTT.h>
#include <LCD_I2C.h>
#include <Adafruit_BusIO_Register.h>

#define LED 21
#define Alam 16
hw_timer_t *My_timer = NULL;

// This is the Timer ISR. It is automatically called 
// on a timer alarm event.
void IRAM_ATTR onTimer(){
  digitalWrite(LED, !digitalRead(LED));
  digitalWrite(Alam, !digitalRead(Alam));
}

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Alam, OUTPUT);
  My_timer = timerBegin(0, 80, true); 
  int frequency = 690*2; // Set your desired frequency here
  int period = 1000000 / frequency;  // use tiemr 0 and set prescale to 80 so 1 tick is 1 uSec
  timerAttachInterrupt(My_timer, &onTimer, true); // point to the ISR
  timerAlarmWrite(My_timer, period, true);  // set alarm every 1 sec
  timerAlarmEnable(My_timer);  // enable the alarm
}

void loop() {

}
