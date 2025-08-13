#ifndef UTILITY_H
#define UTILITY_H

#include <WiFi.h>
#include <WebServer.h>

// ===== Wi-Fi Credentials =====
const char* ssid = "my_phone";
const char* password = "12345678";

// ===== Motor Pins =====
#define ENA 14
#define IN1 13
#define IN2 12
#define ENB 19
#define IN3 32
#define IN4 15

// ===== Motor Speeds =====
int high_motor_speed = 200; // 0-255
int low_motor_speed  = 100; // 0-255

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
void setup_motor_pins() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

// Motor control functions
void forward() {
  analogWrite(ENA, high_motor_speed);
  analogWrite(ENB, high_motor_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(ENA, high_motor_speed);
  analogWrite(ENB, high_motor_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, low_motor_speed);
  analogWrite(ENB, high_motor_speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, high_motor_speed);
  analogWrite(ENB, low_motor_speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

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

// Call this in loop to handle requests
String get_server_command() {
  server.handleClient();
  return latest_command;
}

// Clear the stored command after processing
void clear_command() {
  latest_command = "";
}

#endif
