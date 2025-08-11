const int ledPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);
  Serial.println("Enter the number of seconds to keep the LED ON:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // remove whitespace

    int duration = input.toInt();
    if (duration > 0) {
      Serial.print("Turning LED ON for ");
      Serial.print(duration);
      Serial.println(" seconds...");
      
      digitalWrite(ledPin, HIGH);
      delay(duration * 1000);
      digitalWrite(ledPin, LOW);
      
      Serial.println("LED OFF. Enter another number:");
    } else {
      Serial.println("Invalid input! Please enter a positive integer:");
    }
  }
}
