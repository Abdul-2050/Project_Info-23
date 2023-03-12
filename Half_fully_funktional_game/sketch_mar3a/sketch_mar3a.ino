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

// const int buttonPin = 4;
// int buttonState = HIGH;


void webPage() {
  server.send(200, "text/html", index_html);
}


void setup() {
  // pinMode(buttonPin, INPUT_PULLUP);



  Serial.begin(115200);        // Start serial communication
  WiFi.begin(ssid, password);  // Connect to Wi-Fi network

  while (WiFi.status() != WL_CONNECTED) {  // Wait for connection
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Print IP address

  server.on("/", webPage);           // Handle root URL
  server.on("/about", handleAbout);  // Handle /about URL
  server.on("/getData", handleData);
  // server.on("/checkButtonStatus", handleCheckButtonStatus);

  server.begin();  // Start web server
}

// global variables that has to send to client
float yVal_right_handel = 55;
float yVal_left_handel = 55;
String buttonState = "";

void loop() {
  server.handleClient();  // Handle client requests

  if (Serial.available()) {

    String data = Serial.readStringUntil('\n');
    String values[3];
    int index = 0;

    while (data.length() > 0) {
      int separatorIndex = data.indexOf(";");
      if (separatorIndex == -1) {
        values[index] = data;
        data = "";
      } else {
        values[index] = data.substring(0, separatorIndex);
        data = data.substring(separatorIndex + 1);
      }
      index++;
    }

    yVal_right_handel= values[0].toFloat();
    yVal_left_handel= values[1].toFloat();
    buttonState= values[2];



    Serial.print(yVal_right_handel);
    Serial.print(";");
    Serial.print(yVal_left_handel);
    Serial.print(";");
    Serial.print(buttonState);
    Serial.println();
  }
}


void handleData() {
  server.send(200, "text/plain", String(yVal_right_handel) + ";" + String(yVal_left_handel) + ";" + String(buttonState));
}



// ############## Server-side Code ###################

// unsigned long lastDebounceTime = 0;
// unsigned long debounceDelay = 5;

// ######## depricated ########

// void handleCheckButtonStatus() {
//   unsigned long currentTime = millis();
//   if (currentTime - lastDebounceTime < debounceDelay) {
//     // Ignore the button state if not enough time has passed since the last change
//     return;
//   }
//   lastDebounceTime = currentTime;

//   bool buttonPressed = digitalRead(buttonPin) == LOW;
//   StaticJsonDocument<200> jsonDoc;
//   jsonDoc["buttonPressed"] = buttonPressed;
//   String jsonString;
//   serializeJson(jsonDoc, jsonString);
//   if (buttonPressed) {
//     server.send(200, "application/json", jsonString);
//   } else {
//     server.send(400, "application/json", jsonString);
//   }
// }


// ##################################################################


void handleAbout() {
  server.send(200, "text/html", "<html><body><h1>About</h1><p>This is a simple web server running on ESP8266.</p></body></html>");  // Send response
}
