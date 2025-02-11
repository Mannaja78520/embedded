#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>

// กำหนดขา GPIO
const int ledPin = 16;   // ขา LED
const int buttonPin = 17; // ขาปุ่มกด

// กำหนดค่าพารามิเตอร์ PWM
const int pwmChannel = 0;  
const int freq = 1000;     
const int resolution = 8;  

// กำหนดระดับความสว่าง (0%, 25%, 50%, 75%, 100%)
const int brightnessLevels[] = {0, 64, 128, 192, 255};  
const int totalLevels = sizeof(brightnessLevels) / sizeof(brightnessLevels[0]);

int brightnessIndex = 0; // ระดับความสว่างเริ่มต้น
bool lastButtonState = HIGH; // ใช้เพื่อตรวจจับการกดปุ่ม

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // ใช้ Pull-up ภายในเพื่อลดสัญญาณรบกวน
  
  // ตั้งค่า PWM
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(ledPin, pwmChannel);

  // เริ่มต้นด้วยระดับแรก
  ledcWrite(pwmChannel, brightnessLevels[brightnessIndex]);
}

void loop() {
  bool buttonState = digitalRead(buttonPin); 

  // ตรวจจับการกดปุ่ม (ตรวจจับการเปลี่ยนจาก HIGH → LOW)
  if (buttonState == LOW && lastButtonState == HIGH) {
    brightnessIndex = (brightnessIndex + 1) % totalLevels; // วนค่าจาก 0 → 4
    ledcWrite(pwmChannel, brightnessLevels[brightnessIndex]); // อัปเดตความสว่าง

    delay(200); // หน่วงเวลาเพื่อป้องกันการกดซ้ำเร็วเกินไป
  }

  lastButtonState = buttonState; // อัปเดตสถานะปุ่ม
}
