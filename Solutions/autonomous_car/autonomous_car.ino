#include "utility.h"

void setup() {
  Serial.begin(115200);

  setup_ultrasonic_pins();
  setup_motor_pins();
  
  Serial.println("Autonomous Car Started!");
  delay(2000); // Give time to place the car
}

void loop() {
  float distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance > OBSTACLE_DISTANCE) {
    forward();
    delay(FORWARD_CHECK_TIME);
  } else {
    Serial.println("Obstacle detected! Finding alternate path...");
    stopMotors();
    delay(CHECK_DELAY);
    
    Serial.println("Checking left path...");
    turnLeft();
    delay(TURN_DELAY);
    stopMotors();
    delay(CHECK_DELAY);
    
    float leftDistance = getDistance();
    Serial.print("Left distance: ");
    Serial.print(leftDistance);
    Serial.println(" cm");
    
    if (leftDistance > OBSTACLE_DISTANCE) {
      Serial.println("Left path clear! Moving forward.");
      forward();
      delay(FORWARD_CHECK_TIME);
    } else {
      Serial.println("Left path blocked. Checking right path...");
      
      turnRight();
      delay(TURN_DELAY);
      stopMotors();
      delay(CHECK_DELAY);
      
      turnRight();
      delay(TURN_DELAY);
      stopMotors();
      delay(CHECK_DELAY);
      
      float rightDistance = getDistance();
      Serial.print("Right distance: ");
      Serial.print(rightDistance);
      Serial.println(" cm");
      
      if (rightDistance > OBSTACLE_DISTANCE) {
        Serial.println("Right path clear! Moving forward.");
        forward();
        delay(FORWARD_CHECK_TIME);
      } else {
        Serial.println("Both paths blocked! Reversing...");
        backward();
        delay(1000);
        stopMotors();
        delay(CHECK_DELAY);
      }
    }
  }
}
