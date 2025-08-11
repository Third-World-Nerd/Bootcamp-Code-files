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

// ===================================

void setup() {
  Serial.begin(115200);

  pinMode(PIN_14, OUTPUT);
  pinMode(PIN_25, OUTPUT);
  pinMode(PIN_26, OUTPUT);
  pinMode(PIN_27, OUTPUT);

  stopAll(); // Make sure motors are off at start

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  // Route for controlling motors
  server.on("/control", []() {
    String cmd = server.arg("cmd");

    if (cmd == "w") forward();
    else if (cmd == "s") backward();
    else if (cmd == "a") left();
    else if (cmd == "d") right();
    else if (cmd == "x") stopAll();
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
