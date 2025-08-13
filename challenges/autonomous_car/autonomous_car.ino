#include "utility.h"

/*
  🚗 Autonomous Car Challenge 🚗
  Your task:
  1. Use the ultrasonic sensor to measure distance.
  2. Move forward when the path is clear.
  3. Stop and check left/right when an obstacle is detected.
  4. Reverse if no path is clear.

  Replace ___ with your own code.
*/

void setup() {
  Serial.begin(115200);

  // Initialize sensors and motors
  ___; // Set up ultrasonic pins
  ___; // Set up motor pins

  Serial.println("Autonomous Car Ready!");
  delay(2000);
}

void loop() {
  // Measure distance ahead
  ___; // Get distance in cm
  Serial.print("Distance: ");
  Serial.println(___);

  // === Movement Logic ===
  if (___) { // Condition for clear path
    ___;     // Move forward
    delay(FORWARD_CHECK_TIME);
  } 
  else { 
        // Complete this logic

    if (___) { // Condition for left path clear
      ___;    
    } 
    else {
      // Return to center

      // Check right path
      
      }
    }
  }
}
