#include <Esp32Servo.h>  // เรียกใช้ไลบรารี Servo

Servo myServo;  // สร้างออบเจ็กต์เซอร์โว

void setup() {
  myServo.attach(12);  // กำหนดขา PWM ที่ใช้ต่อเซอร์โว (เช่นขา 9)
  myServo.write(0);   // ตั้งค่าเซอร์โวไปที่ 0 องศา
}

void loop() {
  // ไม่มีโค้ดใน loop เพราะเราต้องการให้เซอร์โวอยู่ที่ 0 องศาตลอดเวลา
}
