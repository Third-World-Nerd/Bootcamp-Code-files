#include <WiFi.h>

// WiFi credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Built-in LED pin (usually GPIO 2)
const int ledPin = 2;

// Function to initialize hardware (LED, Serial)
void initializeHardware() {
  Serial.begin(115200);
  delay(1000);  // Wait for Serial to initialize
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn LED off initially
}

// Function to connect to WiFi
bool connectToWiFi(const char* ssid, const char* password, unsigned long timeout_ms) {
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  unsigned long startAttemptTime = millis();

  // Wait until connected or timeout reached
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout_ms) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println("Failed to connect to WiFi.");
    return false;
  }
}

// Simple task to show WiFi is connected (blink LED once)
void showConnectionStatus() {
  digitalWrite(ledPin, HIGH);  // Turn LED on
  delay(5000);
  digitalWrite(ledPin, LOW);   // Turn LED off
}

void setup() {
  // Step 1: Initialize hardware
  initializeHardware();

  // Step 2: Connect to WiFi (wait max 10 seconds)
  bool connected = connectToWiFi(ssid, password, 10000);

  // Step 3: If connected, do a simple task to show success
  if (connected) {
    showConnectionStatus();
  }
}

void loop() {
  // Nothing here for now
}
