#ifndef UTILITY_H
#define UTILITY_H

#include <Arduino.h>

// Motor pins
#define EN12 14
#define IN1  13
#define IN2  12
#define EN34 19
#define IN3  32
#define IN4  15

// Sensor pins
#define S1 2
#define S2 33
#define S3 23
#define S4 36  // VP
#define S5 39  // VN

// Setup motor pins
void setupMotors() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN12, OUTPUT);
  pinMode(EN34, OUTPUT);
}

// Setup sensor pins
void setupSensors() {
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
}

// Motor functions
void forward(int speedMotor) {
  analogWrite(EN12, speedMotor);
  analogWrite(EN34, speedMotor);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft(int speedMotor) {
  analogWrite(EN12, speedMotor / 2);
  analogWrite(EN34, speedMotor);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight(int speedMotor) {
  analogWrite(EN12, speedMotor);
  analogWrite(EN34, speedMotor / 2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  analogWrite(EN12, 0);
  analogWrite(EN34, 0);
}

#endif
