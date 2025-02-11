#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>

#define BUZZER 16
#define LED 21
#define BUTTON_PIN 14  
hw_timer_t *My_timer = NULL;

const int melody[] = {1175, 1568, 1760, 1976, 1976, 0, 1976, 1760, 1976, 1568, 0, 1568, 1};  // you are my sun shine my only sun shine
const int noteDurations[] = {500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 1000};  // Durations for the notes
volatile int currentNote = 0;
volatile int speedLevel = 2;  

void IRAM_ATTR onButtonPress() {
    speedLevel = (speedLevel + 1) % 5; 
}

void IRAM_ATTR onTimer() {
    digitalWrite(LED, !digitalRead(LED)); 
    tone(BUZZER, melody[currentNote]); 
    currentNote = (currentNote + 1) % 13; 
    
    // ปรับความเร็วตามระดับที่เลือก
    int duration = noteDurations[currentNote];
    if (speedLevel == 0) {       // ช้ามาก
        duration *= 2;           
    } else if (speedLevel == 1) { // ช้า
        duration = duration * 1.5; 
    } else if (speedLevel == 2) { // ปกติ
        // ไม่มีการปรับแต่งความเร็ว
    } else if (speedLevel == 3) { // เร็ว
        duration /= 1.5;      
    } else if (speedLevel == 4) { // เร็วมาก
        duration /= 2;           
    }

    timerAlarmWrite(My_timer, duration * 1000, true); // Duration in microseconds
}

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP); 

    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);  

    My_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(My_timer, &onTimer, true);
    timerAlarmWrite(My_timer, noteDurations[currentNote] * 1000, true);  
    timerAlarmEnable(My_timer);
}

void loop() {
   
    delay(1000); 
}
