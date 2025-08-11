// Solution to the LED Car Arrangment Problem
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

void setup() {
  Serial.begin(115200);

  pinMode(PIN_14, OUTPUT);
  pinMode(PIN_25, OUTPUT);
  pinMode(PIN_26, OUTPUT);
  pinMode(PIN_27, OUTPUT);

  // Initialize all pins LOW
  digitalWrite(PIN_14, LOW);
  digitalWrite(PIN_25, LOW);
  digitalWrite(PIN_26, LOW);
  digitalWrite(PIN_27, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/control", []() {
    String cmd = server.arg("cmd");

    // Turn all pins LOW initially
    digitalWrite(PIN_14, LOW);
    digitalWrite(PIN_25, LOW);
    digitalWrite(PIN_26, LOW);
    digitalWrite(PIN_27, LOW);

    if (cmd == "w") {
      digitalWrite(PIN_14, HIGH);
      digitalWrite(PIN_26, HIGH);
      
    } else if (cmd == "s") {
      digitalWrite(PIN_27, HIGH);
      digitalWrite(PIN_25, HIGH);
      
    } else if (cmd == "a") {
      digitalWrite(PIN_14, HIGH);
      digitalWrite(PIN_27, HIGH);
      
    } else if (cmd == "d") {
      digitalWrite(PIN_26, HIGH);
      digitalWrite(PIN_25, HIGH);
    } else if (cmd == "x") {
      // Stop all, keep all LOW
      server.send(200, "text/plain", "All pins OFF");
    } else {
      server.send(200, "text/plain", "Unknown command");
    }
  });

  server.enableCORS(true);
  server.begin();
}

void loop() {
  server.handleClient();
}
