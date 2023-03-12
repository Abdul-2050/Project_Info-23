
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>


// #include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index_html.h"


// Replace with your network credentials
const char* ssid = "Vodafone-E5E0";
const char* password = "a4EDUdRGCrQq3U3U";


ESP8266WebServer server(80);  // Create a web server on port 80


const int buttonPin = 4;
int buttonState = HIGH;

void webPage(){
  server.send(200,"text/html", index_html);
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);



  Serial.begin(115200); // Initialize Serial Communication
  WiFi.begin(ssid, password);  // Connect to Wi-Fi network

  while (WiFi.status() != WL_CONNECTED) {  // Wait for connection
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Print IP address

  server.on("/", webPage);        // Handle root URL
  server.on("/about", handleAbout);  // Handle /about URL
  server.on("/data", handleData);




  server.begin();                    // Start web server
}

int  yVal= 0;

void loop() {


  // for recieving the Data from arduino
  if(Serial.available()) { // Check if data is available on Serial
    String data = Serial.readStringUntil('\n'); // Read data from Serial
    yVal = data.toInt();
    Serial.println(yVal); // Print received data
  }

  server.handleClient();  // Handle client requests
}

void handleData(){
  server.send(200, "text/plain", String(yVal));
}


void handleAbout() {
  server.send(200, "text/html", "<html><body><h1>About</h1><p>This is a simple web server running on ESP8266.</p></body></html>");  // Send response
}
