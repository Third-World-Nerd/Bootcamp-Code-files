#ifndef UTILITY_H
#define UTILITY_H

#include <WiFi.h>
#include <WebServer.h>

// ===== Wi-Fi Credentials =====
const char* ssid = "my_phone";
const char* password = "12345678";

// ===== Motor Pins =====
#define PIN_14 14
#define PIN_25 25
#define PIN_26 26
#define PIN_27 27

// Web server on port 80
WebServer server(80);

// Latest command from client
String latest_command = "";

// ========================== FUNCTIONS ==========================

// Connect to Wi-Fi
void connect_to_wifi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
}

// Print IP address
void get_ip_address() {
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Setup motor pins
void setup_led_pins() {
  pinMode(PIN_14, OUTPUT);
  pinMode(PIN_25, OUTPUT);
  pinMode(PIN_26, OUTPUT);
  pinMode(PIN_27, OUTPUT);
}

// ===== LED control functions =====
void stopAll() {
  digitalWrite(PIN_14, LOW);
  digitalWrite(PIN_25, LOW);
  digitalWrite(PIN_26, LOW);
  digitalWrite(PIN_27, LOW);
}

void forward() {
  stopAll();
  digitalWrite(PIN_14, HIGH);
  digitalWrite(PIN_26, HIGH);
}

void backward() {
  stopAll();
  digitalWrite(PIN_27, HIGH);
  digitalWrite(PIN_25, HIGH);
}

void left() {
  stopAll();
  digitalWrite(PIN_14, HIGH);
  digitalWrite(PIN_27, HIGH);
}

void right() {
  stopAll();
  digitalWrite(PIN_26, HIGH);
  digitalWrite(PIN_25, HIGH);
}

// ================== SERVER ==================

// Setup server route once
void setup_server_command() {
  server.on("/control", []() {
    latest_command = server.arg("cmd");
    Serial.printf("Received command: %s\n", latest_command.c_str());
    server.send(200, "text/plain", "Command received: " + latest_command);
  });
  server.enableCORS(true);
}

// Start server
void start_server() {
  server.begin();
}

// Handle incoming requests
String get_server_command() {
  server.handleClient();
  return latest_command;
}

// Clear the stored command
void clear_command() {
  latest_command = "";
}

#endif
