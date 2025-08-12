// ESP32 Blink using GPIO 2 (inbuilt LED)

void setup() {
  pinMode(2, OUTPUT); // Set GPIO 2 as output
}

void loop() {
  digitalWrite(2, HIGH); // LED ON
  delay(1000);           // Wait 1 second
  digitalWrite(2, LOW);  // LED OFF
  delay(1000);           // Wait 1 second
}
