#include <Arduino.h>

// Pin definitions for stepper motor control
#define in1  4
#define in2  0
#define in3  2
#define in4  15

// Stepper motor configuration
const int stepsPerRevolution = 2048; // 28BYJ-48 motor with gearbox
const int stepDelay = 3; // Delay between steps in milliseconds

// Motor state
int stepState = 0;
float currentAngle = 0.0; // Current position in degrees

// Function prototypes
void singleStep(bool forward);
void stepForward(int steps);
void stepBackward(int steps);
void moveToAngle(float targetAngle);
void moveToCuntry(String target);

void setup() {
  // Initialize motor control pins as outputs
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Ensure all motor pins are LOW at start
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  // Initialize Serial communication
  Serial.begin(115200);
  Serial.println("Stepper motor ready. Enter target Country:");
}

void loop() {
  // Check if there is input from Serial
  if (Serial.available() > 0) {
    String Country = Serial.readStringUntil('\n'); // Read input until newline
    Country.trim(); // Remove whitespace

    Serial.print("Moving to ");
    Serial.print(Country);

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
  }
}

// Function to move the motor backward for a specific number of steps
void stepBackward(int steps) {
  for (int i = 0; i < steps; i++) {
    singleStep(false);
  }
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
    moveToAngle(0);
  } else if (target == "UK") {
    moveToAngle(1*360.0/8.0);
  } else if (target == "RUSSIA") {
    moveToAngle(2*360.0/8.0);
  } else if (target == "FRANCE") {
    moveToAngle(3*360.0/8.0);
  } else if (target == "JAPAN") {
    moveToAngle(4*360.0/8.0);
  } else if (target == "BRAZILL") {
    moveToAngle(5*360.0/8.0);
  } else if (target == "INDIA") {
    moveToAngle(6*360.0/8.0);
  } else if (target == "AUSTRALIA") {
    moveToAngle(7*360.0/8.0);
  } else {
    Serial.println("Invalid country name. Supported countries: THAILAND, UK, RUSSIA, FRANCE, JAPAN, BRAZILL, INDIA, AUSTRALIA");
  }
}