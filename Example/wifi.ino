#include <WiFi.h>  // Library to handle WiFi connections (comes with ESP32)

// Replace these with your WiFi network details
const char* ssid     = "YOUR_SSID";      // Your WiFi name
const char* password = "YOUR_PASSWORD";  // Your WiFi password

void setup() {
  // Start the Serial Monitor so we can print messages to the computer
  Serial.begin(115200);

  // Set the LED pin as output (LED_BUILTIN is usually GPIO 2 on ESP32 boards)
  pinMode(LED_BUILTIN, OUTPUT);

  // Print a message that we are starting the WiFi connection
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Tell the ESP32 to connect to the WiFi
  WiFi.begin(ssid, password);

  // Wait here until connected (keep printing dots while trying)
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);       // Wait half a second
    Serial.print("."); // Show progress
  }

  // Once connected, print a confirmation message
  Serial.println("\n Connected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Show the ESP32's IP address

  // Turn the LED on for 1 second to show success
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // This runs over and over again, but for now we do nothing
}
