void setup() {
  Serial.begin(115200);
  Serial.println("Type something and press Enter:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // read until newline
    input.trim(); // remove whitespace

    Serial.print("You typed: ");
    Serial.println(input);
    
    Serial.println("Type something else:");
  }
}
