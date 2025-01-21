#include <Arduino.h>
#include <Adafruit_BusIO_Register.h>
#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <MQTT.h>
#include <LCD_I2C.h>

#define Motor 32
#define Button 19
#define LED1  4
#define LED2  18

// WiFi and MQTT configuration
const char ssid[] = "manny";
const char pass[] = "qwertyui";
const char mqtt_broker[] = "test.mosquitto.org";
const char mqtt_command_input_topic[] = "group1.2/command/input";
const char mqtt_command_output_topic[] = "group1.2/command/output";
const char mqtt_client_id[] = "capybara";
int MQTT_PORT = 1883;

WiFiClient net;
MQTTClient client;
LCD_I2C lcd(0x27, 16, 2);

int ledState = 0; // Keeps track of the current LED state
bool buttonPressed = false;

// Function prototypes
void connect();
void messageReceived(String &topic, String &payload);
void updateLEDsAndMotor();

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(Motor, OUTPUT);
  pinMode(Button, INPUT);

  // Turn off LEDs and Motor initially
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(Motor, LOW);

  // Initialize Serial communication
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);
  connect();

  lcd.begin();
  lcd.clear();
  lcd.backlight();
  lcd.print("ESP32 Ready");

  client.publish(mqtt_command_output_topic, "ESP32 Ready");
  client.publish(mqtt_command_output_topic, "หยุด");
  lcd.clear();
  lcd.print("หยุด");

}

void loop() {
  client.loop();
  delay(10);

  if (!client.connected()) {
    connect();
  }
  Serial.println(digitalRead(Button)); // Handle button press
  if (digitalRead(Button) == HIGH) {
    if (!buttonPressed) { // Avoid multiple presses
      buttonPressed = true;
      ledState = (ledState + 1) % 3; // Cycle through states: 0 -> 1 -> 2 -> 0
      updateLEDsAndMotor();
    }
  } else {
    buttonPressed = false;
  }
}

// Function to update LEDs and Motor based on the current state
void updateLEDsAndMotor() {
  switch (ledState) {
    case 0: // All LEDs off, Motor off
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(Motor, LOW);
      client.publish(mqtt_command_output_topic, "หยุด");
      lcd.clear();
      lcd.print("หยุด");
      break;

    case 1: // LED1 on, LED2 off, Motor off
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      digitalWrite(Motor, LOW);
      client.publish(mqtt_command_output_topic, "หยุด");
      lcd.clear();
      lcd.print("หยุด");
      break;

    case 2: // Both LEDs on, Motor on
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(Motor, HIGH);
      client.publish(mqtt_command_output_topic, "หมุน");
      lcd.clear();
      lcd.print("หมุน");
      break;
  }
}

// Function to connect to WiFi and MQTT broker
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id)) {  
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
  client.subscribe(mqtt_command_input_topic);
  client.subscribe(mqtt_command_output_topic);
}

// Callback function for MQTT messages
void messageReceived(String &topic, String &payload) {
  if (payload.length() == 0) return;
  Serial.println("incoming: " + topic + " - " + payload);
  if (topic == mqtt_command_input_topic) {
    if(payload == "0"){
      ledState = 0;
      updateLEDsAndMotor();
    }
    if(payload == "1"){
      ledState = 1;
      updateLEDsAndMotor();
    }
    if(payload == "2"){
      ledState = 2;
      updateLEDsAndMotor();
    }
  }
}
