#include <WiFi.h>

// WiFi credentials
#define WIFI_SSID "Placeholder"
#define WIFI_PASSWORD "Placeholder"

WiFiServer server(80); // Create a web server on port 80



void setup() {
  // Start serial communication for debugging
  Serial.begin(921600);
  pinMode(LED_BUILTIN, OUTPUT); // Set LED pin as output
  digitalWrite(LED_BUILTIN, LOW); // Turn off the LED initially

  // Connect to WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started.");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("New client connected.");
  String request = client.readStringUntil('\r');
  Serial.println("Request: " + request);

  // Handle the HTTP request
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED on
    Serial.println("LED turned ON");
  } else if (request.indexOf("/LED=OFF") != -1) {
    digitalWrite(LED_BUILTIN, LOW); // Turn the LED off
    Serial.println("LED turned OFF");
  }

  // Send a simple HTML response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>ESP32 Web Server</h1>");
  client.println("<p><a href='/LED=ON'>Turn LED ON</a></p>");
  client.println("<p><a href='/LED=OFF'>Turn LED OFF</a></p>");
  client.println("</html>");
  client.stop(); // Close the connection
  Serial.println("Client disconnected.");
}
