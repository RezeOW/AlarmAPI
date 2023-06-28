#include <WiFi.h>
#include <WebServer.h>
#include "WifiCreds.h"

// WiFi credentials
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWD;

// Pin for Alarm
const int Pin = 33;

WebServer server(80);  // create a server on port 80

void setup() {
  Serial.begin(115200);
  pinMode(Pin, OUTPUT); 
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.on("/startAlarm", HTTP_POST, startAlarm);    // start
  server.on("/stopAlarm", HTTP_POST, stopAlarm);  // stop
  server.begin();  // start the server
}

void loop() {
  // Check for incoming connections
  server.handleClient();
}

void startAlarm() {
  digitalWrite(Pin, HIGH);
  server.send(200);
  delay(10000);
  digitalWrite(Pin,LOW);

}

void stopAlarm() {
  digitalWrite(Pin, LOW);
  server.send(200);
}

