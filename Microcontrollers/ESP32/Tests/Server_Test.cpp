#include <WiFi.h>

// WiFi credentials
#define WIFI_SSID "Galaxy S20+"
#define WIFI_PASSWORD "135790864"

/*
  Will need two leds and resistors where one is using the 16 GPIO and the second is using the 17 GPIO
*/

WiFiServer server(80); // Create a web server on port 80
String firstLEDState = "off";
String secondLEDState = "off";
unsigned int firstPIN = 16;
unsigned int secondPIN = 17;


void setup() {
  // Start serial communication for debugging
  Serial.begin(921600);
  pinMode(LED_BUILTIN, OUTPUT); // Set LED pin as output
  digitalWrite(LED_BUILTIN, LOW); // Turn off the LED initially


  pinMode(firstPIN, OUTPUT);
  digitalWrite(firstPIN, LOW);

  pinMode(secondPIN, OUTPUT);
  digitalWrite(secondPIN, LOW);

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
  if (request.indexOf("/16PINLED=ON") != -1) {
    digitalWrite(firstPIN, HIGH); // Turn the LED on
    Serial.println("LED turned ON");
    firstLEDState = "on";
  } else if (request.indexOf("/16PINLED=OFF") != -1) {
    digitalWrite(firstPIN, LOW); // Turn the LED off
    Serial.println("LED turned OFF");
    firstLEDState = "off";
  } else if (request.indexOf("/17PINLED=ON") != -1) {
    digitalWrite(secondPIN, HIGH);
    Serial.println("LED turned on");
    secondLEDState = "on";
  } else if (request.indexOf("17PINLED=OFF") != -1) {
    digitalWrite(secondPIN, LOW);
    Serial.println("LED turned off");
    secondLEDState = "off";
  }

// Display the HTML web page
client.println("<!DOCTYPE html><html>");
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
client.println("<link rel=\"icon\" href=\"data:,\">");
// CSS to style the on/off buttons
client.println("<style>html { font-family: monospace; display: inline-block; margin: 0px auto; text-align: center;}");
client.println(".button { background-color: yellowgreen; border: none; color: white; padding: 16px 40px;");
client.println("text-decoration: none; font-size: 32px; margin: 2px; cursor: pointer;}");
client.println(".button2 {background-color: gray;}</style></head>");

client.println("<body><h1>ESP32 Web Server</h1>");
client.println("<p>Control LED State</p>");

if (firstLEDState == "off") {
  client.println("<p><a href=\"/16PINLED=ON\"><button class=\"button\">ON</button></a></p>");
} else {
  client.println("<p><a href=\"/16PINLED=OFF\"><button class=\"button button2\">OFF</button></a></p>");
}
if (secondLEDState == "off") {
  client.println("<p><a href=\"/17PINLED=ON\"><button class=\"button\">ON</button></a></p>");
} else {
  client.println("<p><a href=\"/17PINLED=OFF\"><button class=\"button button2\">OFF</button></a></p>");
}
client.println("</body></html>");

// The HTTP response ends with another blank line
client.println();
}
