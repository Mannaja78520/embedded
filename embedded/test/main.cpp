#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>

// Pin definitions for stepper motor control
#define in1  4
#define in2  0
#define in3  2
#define in4  15
#define LED  18


const char ssid[] = "manny";
const char pass[] = "qwertyui";

const char mqtt_broker[]="test.mosquitto.org";
const char mqtt_topic[]="group/command";
const char mqtt_client_id[]="arduino_group_x"; // must change this string to a unique value
int MQTT_PORT=1883;


WiFiClient net;
MQTTClient client;

// Stepper motor configuration
const int stepsPerRevolution = 2048; // 28BYJ-48 motor with gearbox
const int stepDelay = 3; // Delay between steps in milliseconds

// Motor state
int stepState = 0;
float currentAngle = 0.0; // Current position in degrees
float THAILANDAngle = 0;
float UKAngle = 1*360.0/8.0;
float RUSSIAAngle = 2*360.0/8.0;
float FRANCEAngle = 3*360.0/8.0;
float JAPANAngle = 4*360.0/8.0;
float BRAZILAngle = 5*360.0/8.0;
float INDIAAngle = 6*360.0/8.0;
float AUSTRALIAAngle = 7*360.0/8.0;

// Function prototypes
void singleStep(bool forward);
void stepForward(int steps);
void stepBackward(int steps);
void moveToAngle(float targetAngle);
void moveToCuntry(String target);
void connect();
void messageReceived(String &topic, String &payload);

void setup() {
  // Initialize motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED, OUTPUT);

  // Ensure all motor pins are LOW at start
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(LED, LOW);

  // Initialize Serial communication
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  client.begin(mqtt_broker, MQTT_PORT, net);
  client.onMessage(messageReceived);
  connect();

  Serial.println("Stepper motor ready. Enter target Country:");
}

void loop() {
  client.loop();
  delay(10);
  if (!client.connected()) {
    connect();
  }
  // Check if there is input from Serial
  if (Serial.available() > 0) {
    String Country = Serial.readStringUntil('\n'); // Read input until newline
    Country.trim(); // Remove whitespace

    Serial.print("Moving to ");
    Serial.println(Country);

    // Move motor to target angle
    moveToCuntry(Country);

    Serial.println("Movement complete.");
  }
}

// Function to execute a single step in the desired direction
void singleStep(bool forward) {
  // 4-step sequence for 28BYJ-48
  static const int stepSequence[4][4] = {
    {HIGH, LOW, LOW, LOW},  // Step 1
    {LOW, HIGH, LOW, LOW},  // Step 2
    {LOW, LOW, HIGH, LOW},  // Step 3
    {LOW, LOW, LOW, HIGH}   // Step 4
  };

  // Determine next step state
  stepState = (forward) ? (stepState + 1) % 4 : (stepState + 3) % 4;

  // Apply step state to motor pins
  digitalWrite(in1, stepSequence[stepState][0]);
  digitalWrite(in2, stepSequence[stepState][1]);
  digitalWrite(in3, stepSequence[stepState][2]);
  digitalWrite(in4, stepSequence[stepState][3]);

  // Small delay for step timing
  delay(stepDelay);
}

// Function to move the motor forward for a specific number of steps
void stepForward(int steps) {
  for (int i = 0; i < steps; i++) {
    singleStep(true);
    digitalWrite(LED, HIGH);
  }
  digitalWrite(LED, LOW);
}

// Function to move the motor backward for a specific number of steps
void stepBackward(int steps) {
  for (int i = 0; i < steps; i++) {
    singleStep(false);
    digitalWrite(LED, HIGH);
  }
  digitalWrite(LED, LOW);
}

// Function to move the motor to a specific angle
void moveToAngle(float targetAngle) {
  // Calculate the shortest path
  float angleDifference = targetAngle - currentAngle;
  if (angleDifference > 180) angleDifference -= 360;
  if (angleDifference < -180) angleDifference += 360;

  // Determine the number of steps required
  int steps = (int)(stepsPerRevolution * (angleDifference / 360.0));
  if (steps > 0) {
    stepForward(steps);
  } else if (steps < 0) {
    stepBackward(-steps);
  }
  // Update the current position
  currentAngle = targetAngle;
}
void moveToCuntry(String target){
  if (target == "THAILAND") {
    moveToAngle(THAILANDAngle);
  } else if (target == "UK") {
    moveToAngle(UKAngle);
  } else if (target == "RUSSIA") {
    moveToAngle(RUSSIAAngle);
  } else if (target == "FRANCE") {
    moveToAngle(FRANCEAngle);
  } else if (target == "JAPAN") {
    moveToAngle(JAPANAngle);
  } else if (target == "BRAZIL") {
    moveToAngle(BRAZILAngle);
  } else if (target == "INDIA") {
    moveToAngle(INDIAAngle);
  } else if (target == "AUSTRALIA") {
    moveToAngle(AUSTRALIAAngle);
  } else {
    Serial.println("Invalid country name. Supported countries: THAILAND, UK, RUSSIA, FRANCE, JAPAN, BRAZILL, INDIA, AUSTRALIA");
  }
}

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

  client.subscribe(mqtt_topic);
  // client.unsubscribe("/hello");
}


void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  // Note: Do not use the client in the callback to publish, subscribe or
  // unsubscribe as it may cause deadlocks when other things arrive while
  // sending and receiving acknowledgments. Instead, change a global variable,
  // or push to a queue and handle it in the loop after calling `client.loop()`.
}