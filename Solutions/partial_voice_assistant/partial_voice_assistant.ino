#include <Arduino.h>
#include "driver/i2s.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "mbedtls/base64.h"
#include "Audio.h"

// Pin mapping
#define I2S_BCLK   26
#define I2S_LRCL   25
#define I2S_DOUT   27   // MAX98357A DIN

#define I2S_SAMPLE_RATE   16000
#define I2S_BUFFER_SIZE   1024


Audio audio;

// WiFi credentials
const char* ssid     = "WIFI_NAME";
const char* password = "WIFI_PASSWORD";

// Gemini API endpoints (update with your API key)
const char* ai_text_endpoint = "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=API_KEY";

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
}

// Send text prompt to Gemini text model
String sendPromptToGemini(const String &prompt) {
  String reply = "";
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(ai_text_endpoint);
    http.addHeader("Content-Type", "application/json");

    String requestBody = "{\n"
                         "  \"contents\": [{\n"
                         "    \"parts\":[{\"text\":\"" + prompt + "\"}]\n"
                         "  }]\n"
                         "}";

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      reply = http.getString();
      Serial.printf("[Gemini Text Status] %d\n", httpResponseCode);
      Serial.println("Gemini Text Response: " + reply);

      DynamicJsonDocument doc(4096);
      deserializeJson(doc, reply);
      if (doc["candidates"][0]["content"]["parts"][0]["text"].is<String>()) {
        reply = doc["candidates"][0]["content"]["parts"][0]["text"].as<String>();
      }
    } else {
      Serial.printf("Error sending to Gemini text model: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    http.end();
  }
  return reply;
}




void speak(String text) {
  // Stop any current audio
  if (audio.isRunning()) audio.stopSong();

  // URL encode spaces (for Google TTS)
  text.replace(" ", "%20");

  // Construct Google Translate TTS URL
  String url = "https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=" + text + "&tl=en";

  Serial.println("Playing: " + text);
  audio.connecttohost(url.c_str()); // stream directly from Google TTS
}

void audio_info(const char *info) {
  Serial.print("info: "); Serial.println(info);
}


void setup() {
  Serial.begin(115200);
    // Initialize I2S for MAX98357A
  audio.setPinout(I2S_BCLK, I2S_LRCL, I2S_DOUT);
  audio.setVolume(100); // 0-21

  connectWiFi();
  Serial.println("Voice assistant mode started with Gemini API...");



}

void loop() {
  audio.loop(); // keep streaming any current audio
  // Check for input from Serial Monitor
  if (Serial.available()) {
    String text = Serial.readStringUntil('\n');
    String transcript = sendPromptToGemini(text);
    Serial.println(transcript);
    transcript.trim();
    if (transcript.length() > 0) {
      speak(transcript);
    }
  }

}
