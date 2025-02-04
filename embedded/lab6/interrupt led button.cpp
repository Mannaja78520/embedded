#include <Arduino.h>
#include <motor_esp.h>
#include <Wire.h>
#include <WiFi.h>
#include <MQTT.h>
#include <LCD_I2C.h>
#include <Adafruit_BusIO_Register.h>

#define Button_Pin   35
#define LED1_Pin     23
#define LED2_Pin 16
 
void IRAM_ATTR IO_INT_ISR()
{
  // Toggle The LED
  digitalWrite(LED1_Pin, !digitalRead(LED1_Pin));
}
 
void setup()
{
  pinMode(LED1_Pin, OUTPUT);
  pinMode(LED2_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT);
  attachInterrupt(Button_Pin, IO_INT_ISR, RISING); // interrupt on rising edge
}
 
void loop()
{
    digitalWrite(LED2_Pin,HIGH); 
    delay(1000);
    digitalWrite(LED2_Pin,LOW);
    delay(1000);
}

