#include <Arduino.h>

#define LED     23
#define BUTTON  32

int c = 0;                  // ตัวแปรนับค่า
bool buttonState = HIGH;    // สถานะปุ่มปัจจุบัน
bool lastButtonState = HIGH; // สถานะปุ่มครั้งก่อนหน้า

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);   // ตั้งค่า pin ของปุ่มเป็น input
  pinMode(LED, OUTPUT);     // ตั้งค่า pin ของ LED เป็น output
}

void loop() {
  // อ่านสถานะปุ่ม
  buttonState = digitalRead(BUTTON);

  // ตรวจจับการเปลี่ยนสถานะจาก HIGH -> LOW (การกดปุ่ม)
  if (buttonState == LOW && lastButtonState == HIGH) {
    c++;                    // เพิ่มค่าเมื่อมีการกดปุ่ม
    Serial.println(c);      // พิมพ์ค่าปัจจุบันออกทาง Serial
    digitalWrite(LED, HIGH);// เปิดไฟ LED
    delay(100);             // ดีเลย์เล็กน้อยเพื่อป้องกันการเด้งของปุ่ม (debounce)
  }

  // หากปล่อยปุ่ม (HIGH) ให้ปิดไฟ LED
  if (buttonState == HIGH) {
    digitalWrite(LED, LOW); // ปิดไฟ LED
  }

  // อัปเดตสถานะครั้งก่อนหน้า
  lastButtonState = buttonState;
}