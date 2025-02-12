#include <WiFi.h>
#include <WiFiClient.h>


// Replace with your network credentials
const char* ssid = "WiCAN_5432048df639";
const char* password = "";

// Replace with your server details
const char* serverIP = "192.168.80.1";
const uint16_t serverPort = 3333;

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to the server
  if (!client.connect(serverIP, serverPort)) {
    Serial.println("Connection to server failed");
    return;
  }

  Serial.println("Connected to server");
}

void loop() {
  // Example CANbus identifier and message data
  uint32_t canId = 0x123; // CANbus identifier
  uint8_t data[8] = {0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23}; // Example data

  // Construct the SLCAN message
  String slcanMessage = "T";
  slcanMessage += String(canId, HEX);
  for (int i = 0; i < 8; i++) {
    slcanMessage += String(data[i], HEX);
  }
  slcanMessage += "\r";

  // Send the SLCAN message
  client.print(slcanMessage);

  // Read server response (if any)
  while (client.available()) {
    String response = client.readStringUntil('\r');
    Serial.println("Server response: " + response);
  }

  // Add a delay for demonstration purposes
  delay(5000);
}
