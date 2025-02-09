#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>

#define BUZZER 16
#define LED 21
#define BUTTON_PIN 14  // Pin ที่ใช้เชื่อมต่อกับปุ่มกด
hw_timer_t *My_timer = NULL;

// Define musical notes (frequencies in Hz)
const int melody[] = {1175, 1568, 1760, 1976, 1976, 0, 1976, 1760, 1976, 1568, 0, 1568, 1};  // Notes of the melody
const int noteDurations[] = {500, 500, 500, 500, 500, 1000, 500, 500, 500, 500, 500, 500, 1000};  // Durations for the notes (in milliseconds)
volatile int currentNote = 0;
volatile int speedLevel = 2;  // ค่าเริ่มต้นที่ระดับ "ปกติ" (ค่าระดับความเร็ว)

void IRAM_ATTR onButtonPress() {
    speedLevel = (speedLevel + 1) % 5;  // เปลี่ยนระดับความเร็วของเพลง
}

void IRAM_ATTR onTimer() {
    digitalWrite(LED, !digitalRead(LED)); // Blink LED
    tone(BUZZER, melody[currentNote]); // Play note
    currentNote = (currentNote + 1) % 13; // Move to next note
    
    // ปรับความเร็วตามระดับที่เลือก
    int duration = noteDurations[currentNote];
    if (speedLevel == 0) {       // ช้ามาก
        duration *= 2;           // เพิ่มความช้า
    } else if (speedLevel == 1) { // ช้า
        duration = duration * 1.5; // ช้าลงบ้าง
    } else if (speedLevel == 2) { // ปกติ
        // ไม่มีการปรับแต่งความเร็ว
    } else if (speedLevel == 3) { // เร็ว
        duration /= 1.5;         // เร็วขึ้น
    } else if (speedLevel == 4) { // เร็วมาก
        duration /= 2;           // เร็วมาก
    }

    timerAlarmWrite(My_timer, duration * 1000, true); // Duration in microseconds
}

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // ตั้งปุ่มให้เป็น INPUT_PULLUP

    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButtonPress, FALLING);  // เมื่อกดปุ่มจะเรียกใช้ onButtonPress()

    My_timer = timerBegin(0, 80, true);
    timerAttachInterrupt(My_timer, &onTimer, true);
    timerAlarmWrite(My_timer, noteDurations[currentNote] * 1000, true);  // ตั้งค่าความยาวเสียงเริ่มต้น
    timerAlarmEnable(My_timer);
}

void loop() {
    // Loop is empty; melody is played via interrupts
    delay(1000); // ใช้เวลาในการรอเพื่อให้ปุ่มมีเวลาในการกด
}
