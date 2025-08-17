#include <Arduino.h>
#include "utility.h"

int speedMotor = 150; // Motor speed (0-255)

void setup() {
  Serial.begin(115200);
  setupMotors();
  setupSensors();
  Serial.println("Line Follower Ready (Using analogWrite)");
}

void loop() {
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  Serial.printf("S1:%d S2:%d S3:%d S4:%d S5:%d\n", s1, s2, s3, s4, s5);

  if (s3 == HIGH && s2 == LOW && s4 == LOW) {
    forward(speedMotor);
  }
  else if (s1 == HIGH || s2 == HIGH) {
    turnRight(speedMotor);
  }
  else if (s4 == HIGH || s5 == HIGH) {
    turnLeft(speedMotor);
  }
  else {
    stopMotors();
  }

  delay(50);
}
