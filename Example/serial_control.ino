// Example code to use ESP32 serial monitor

const int ledPin = 2; // Built-in LED pin for ESP32

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Make sure LED is off initially
  Serial.begin(115200);
  Serial.println("Send any command to turn on LED for 5 seconds.");
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');  // Read input until newline
    Serial.print("Received command: ");
    Serial.println(command);

    digitalWrite(ledPin, HIGH);  // Turn LED on
    delay(5000);                 // Wait for 5 seconds
    digitalWrite(ledPin, LOW);   // Turn LED off
  }
}
