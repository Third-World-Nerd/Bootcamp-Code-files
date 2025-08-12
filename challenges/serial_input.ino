void setup() {
  Serial.begin(115200);
  Serial.println("Type something and press Enter:");
}

void loop() {
  if (Serial.available()) {
    // Read the input from the serial monitor
    ____
    input.trim(); // remove whitespace

    Serial.print("You typed: ");
    // Print what you read in the serial monitor
    ___
    
    Serial.println("Type something else:");
  }
}
