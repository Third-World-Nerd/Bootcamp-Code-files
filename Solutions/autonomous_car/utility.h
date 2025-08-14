#ifndef UTILITY_H
#define UTILITY_H

// ===== Ultrasonic Sensor Pins =====
#define TRIG_PIN 17   // Tx2
#define ECHO_PIN 35   // D35

// ===== Motor Pins =====
#define ENA 14
#define IN1 13
#define IN2 12
#define ENB 19
#define IN3 32
#define IN4 15

// ===== Constants =====
#define OBSTACLE_DISTANCE 20   // Distance in cm to detect obstacle
#define TURN_DELAY 500         // Time to turn (adjust based on your car)
#define CHECK_DELAY 300        // Time to pause and check distance
#define FORWARD_CHECK_TIME 100 // Time to move forward before checking again

// ===== Motor Speed Variables =====
int high_motor_speed = 150;  // Adjust based on your motors
int low_motor_speed = 100;   // Lower speed for turning

// ================== SETUP FUNCTIONS ==================
void setup_ultrasonic_pins() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void setup_motor_pins() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// ================== ULTRASONIC ==================
float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  return (duration * 0.034) / 2;  // cm
}

// ================== MOTOR CONTROL ==================
void forward() {
  analogWrite(ENA, high_motor_speed);
  analogWrite(ENB, high_motor_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, high_motor_speed);
  analogWrite(ENB, high_motor_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, low_motor_speed);
  analogWrite(ENB, high_motor_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, high_motor_speed);
  analogWrite(ENB, low_motor_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

#endif