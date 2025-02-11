#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_BusIO_Register.h>
#include <ESP32Servo.h>

Servo myservo;

int servoPin = 18;
int pos = 0;

#define Button 17
#define LED 19

bool ledState = false;  // สถานะของ LED
bool lastButtonState = LOW; // เก็บสถานะปุ่มก่อนหน้า
bool currentButtonState;
bool plus;

void toggleLED();
void servoTest();

void setup() {
    Serial.begin(115200);
    pinMode(Button, INPUT_PULLUP); // ใช้ PULLUP เพื่อลดสัญญาณรบกวน
    pinMode(LED, OUTPUT);
    
    digitalWrite(LED, ledState); // ตั้งค่าเริ่มต้น
    myservo.attach(servoPin);
    myservo.write(0);
    delay(5000);
}

void loop() {
    toggleLED();

    // Servo movement logic
    if (pos <= 0) plus = true;
    if (pos >= 180) plus = false;

    if (plus) {
        myservo.write(pos);
        delay(15);
        pos++;
    } else {
        myservo.write(pos);
        delay(15);
        pos--;
    }
}

void toggleLED() {
    currentButtonState = digitalRead(Button);

    if (currentButtonState == HIGH && lastButtonState == LOW) {
        delay(50);  // ดีบัฟปุ่ม
        if (digitalRead(Button) == HIGH) { // ตรวจสอบอีกครั้งหลังดีบัฟ
            ledState = !ledState; // สลับสถานะ LED
            digitalWrite(LED, ledState);
            Serial.println(ledState ? "LED ON" : "LED OFF");
        }
    }

    lastButtonState = currentButtonState; // อัปเดตสถานะปุ่ม
}
