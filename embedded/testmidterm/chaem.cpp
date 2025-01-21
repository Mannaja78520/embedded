#include <Arduino.h>
#include <motor_esp.h>
#include <Wire.h>
#include <WiFi.h>
#include <MQTT.h>
#include <LCD_I2C.h>
#include <Adafruit_BusIO_Register.h>

// กำหนดขาสำหรับมอเตอร์และปุ่มกด
#define motor1PWM 23
#define motor1PinA 16
#define motor1PinB 19
#define buttonPin 5

// กำหนดค่าการเชื่อมต่อ WiFi และ MQTT
const char ssid[] = "Chocolate";
const char pass[] = "chocolate";
const char mqtt_broker[] = "test.mosquitto.org";
const char mqtt_command_input_topic[] = "group1.2/command/input";
const char mqtt_command_output_topic[] = "group1.2/command/output";
const char mqtt_client_id[] = "esp32_motor_control";
int MQTT_PORT = 1883;

WiFiClient net;
MQTTClient client;
LCD_I2C lcd(0x27, 16, 2);
Motor motor1(20000, 8, 0, 1, motor1PWM, motor1PinA, motor1PinB);

int motorState = 0;  
bool buttonPressed = false;

void connect();
void messageReceived(String &topic, String &payload);
void updateMotorState();

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.print("Ready to shoot!");

  WiFi.begin(ssid, pass);
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);
  connect();

  client.publish(mqtt_command_output_topic, "Ready to shoot!");
  updateMotorState();
}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }

  if (digitalRead(buttonPin) == LOW) {
    if (!buttonPressed) {
      buttonPressed = true;
      motorState = (motorState + 1) % 3; 
      updateMotorState();
    }
  } else {
    buttonPressed = false;
  }
}

void updateMotorState() {
  lcd.setCursor(0, 1);
  switch (motorState) {
    case 0:
      motor1.brake();
      lcd.print("     Stop           ");
      client.publish(mqtt_command_output_topic, "Stop");
      break;
    case 1:
      motor1.spin(255);
      lcd.print("     Clockwise      ");
      client.publish(mqtt_command_output_topic, "Clockwise");
      break;
    case 2:
      motor1.spin(-255);
      lcd.print("     Counter CW     ");
      client.publish(mqtt_command_output_topic, "Counter Clockwise");
      break;
  }
}

void connect() {
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nConnecting to MQTT...");
  while (!client.connect(mqtt_client_id)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nConnected!");
  client.subscribe(mqtt_command_input_topic);
}

void messageReceived(String &topic, String &payload) {
  Serial.println("Incoming: " + topic + " - " + payload);
  if (topic == mqtt_command_input_topic) {
    if (payload == "Clockwise") {
      motorState = 1;
    } else if (payload == "Counter Clockwise") {
      motorState = 2;
    } else if (payload == "Stop") {
      motorState = 0;
    }
    updateMotorState();
  }
}
