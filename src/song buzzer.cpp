#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>

#define BUZZER 16
#define LED 21
hw_timer_t *My_timer = NULL;


const int melody[] = {1175,1568,1760,1976,1976,0,1976,1760,1976,1568,0,1568}; // ypu my are sun shine my only sun shine
const int noteDurations[] = {500,500,500,500,500,1000,500,500,500,500,500,500}; //velocity of melody
volatile int currentNote = 0;

void IRAM_ATTR onTimer() {
    digitalWrite(LED, !digitalRead(LED)); 
    tone(BUZZER, melody[currentNote]);
    currentNote = (currentNote + 1) % 9; 
    
   
    timerAlarmWrite(My_timer, noteDurations[currentNote] * 1000, true); 
}

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    
    My_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(My_timer, &onTimer, true);
    timerAlarmWrite(My_timer, noteDurations[currentNote] * 1000, true); // Set initial note duration (in microseconds)
    timerAlarmEnable(My_timer);
}

void loop() {
   
}
