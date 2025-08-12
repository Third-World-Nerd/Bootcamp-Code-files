// Replace ___ with your code

#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "SOYAM_dhfibernet";
const char* password = "6153@6153";

WebServer server(80);

// Define pins
#define PIN_14 14
#define PIN_25 25
#define PIN_26 26
#define PIN_27 27

// ===== Motor control functions =====
void stopAll() {
  digitalWrite(PIN_14, LOW);
  digitalWrite(PIN_25, LOW);
  // Stop the other two motors too
  ___
}

void forward() {
  // Stop the other motors
  ___
  digitalWrite(PIN_14, HIGH);
  digitalWrite(PIN_26, HIGH);
}

void backward() {
  // Stop the other motors
  ___
  // Turn the appropriate LED ON
  ___
  ___
}

void left() {
  // Fill in like the above functions
  ___
  ___
  ___
}

void right() {
  // Fill in like the above functions
  ___
  ___
  ___

}

// ===================================

void setup() {
  Serial.begin(115200);

  pinMode(PIN_14, OUTPUT);
  pinMode(PIN_25, OUTPUT);
  // Configure the other pins as OUTPUT too
  ___
  ___


  // Make sure motors are off at start
  ___

  // Connect to WiFi
  ___
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  //Get your local IP
  ___
  
  // Route for controlling motors
  server.on("/control", []() {
    String cmd = server.arg("cmd");

    if (cmd == "w") forward();
    else if (cmd == "s") ___;
    else if (cmd == "a") ___;
    else if (cmd == "d") ___;
    else if (cmd == "x") ___;
    else {
      server.send(200, "text/plain", "Unknown command");
      return;
    }

    server.send(200, "text/plain", "Command executed: " + cmd);
  });

  server.enableCORS(true);
  server.begin();
}

void loop() {
  server.handleClient();
}
