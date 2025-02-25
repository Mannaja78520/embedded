#include <Wire.h>
#include <Arduino.h>
#include <ESP32Servo.h>


const int servoPins[8] = {16, 17, 5, 18, 19, 4, 0, 2};

Servo servos[8];

void setup() {
    Serial.begin(115200); 
    for (int i = 0; i < 8; i++) {
        servos[i].attach(servoPins[i]); 
    }
    Serial.println("พิมพ์หมายเลขเซอร์โว (1-8) ตามด้วยองศาที่ต้องการ เช่น '3 120'");
}

void loop() {
    if (Serial.available() > 0) {
        int servoID = Serial.parseInt();  //รับค่ามาจากที่พิมตัวแรก
        int angle = Serial.parseInt(); //รับค่าองศาที่พิมตัวที่สอง 
        Serial.flush(); //เครียร์กันข้อมูลเก่าถูกนำไปใช้ 

        if (servoID >= 1 && servoID <= 8 && angle >= 0 && angle <= 180) {
            servos[servoID - 1].write(angle); // ปรับองศาของเซอร์โวที่เลือก
            Serial.print("Number of servos: ");
            Serial.print(servoID);
            Serial.print(" moving to ");
            Serial.print(angle);
            Serial.println(" Degree: "); 
        } else {
            Serial.println("⚠️ Error please fill correct form เช่น '2 90'");
        }
    }
}
