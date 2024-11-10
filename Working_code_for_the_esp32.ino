#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ESPAsyncWebServer.h>

#define BLYNK_TEMPLATE_ID "TMPL3fKztbE4f"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "18qe0uJnOZo317FiaR0I75KeBEwuQb9B"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "poco";
char pass[] = "goranshh";

// Initialize HardwareSerial for communication with Arduino
HardwareSerial mySerial(1); // Use UART1 (GPIO16-RX, GPIO17-TX)

// Initialize Async Web Server on port 80
AsyncWebServer server(80);

String sensor1 = "Available";
String sensor2 = "Available";

void setup() {
    // Start Serial communication for debugging
    Serial.begin(115200);
    mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=GPIO16, TX=GPIO17

    // Connect to Wi-Fi
    Blynk.begin(auth, ssid, pass);

    // Initialize HTTP GET endpoint for checking parking slot status
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
        String json = "{\"sensor1\": \"" + sensor1 + "\", \"sensor2\": \"" + sensor2 + "\"}";
        request->send(200, "application/json", json); // Respond with JSON data
    });

    // Start the server
    server.begin();
}

void loop() {
    // Run Blynk
    Blynk.run();

    // Read data from Arduino if available
    if (mySerial.available()) {
        String data = mySerial.readStringUntil('\n');
        processData(data);
    }
}

void processData(String data) {
    int commaIndex = data.indexOf(',');
    sensor1 = data.substring(0, commaIndex);
    sensor2 = data.substring(commaIndex + 1, data.length() - 1);

    int ledState1 = (sensor1 == "Occupied") ? 1 : 0;
    int ledState2 = (sensor2 == "Occupied") ? 1 : 0;

    Blynk.virtualWrite(V10, ledState1);
    Blynk.virtualWrite(V11, ledState2);

    Serial.print("Sensor 1: ");
    Serial.println(sensor1);
    Serial.print("Sensor 2: ");
    Serial.println(sensor2);
}
