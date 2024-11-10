#define BLYNK_TEMPLATE_ID "TMPL3fKztbE4f"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "18qe0uJnOZo317FiaR0I75KeBEwuQb9B"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
char ssid[] = "poco";
char pass[] = "goranshh";

// Initialize HardwareSerial for communication with Arduino
HardwareSerial mySerial(1); // Use UART1 (GPIO16-RX, GPIO17-TX)

void setup() {
    // Debugging via Serial Monitor
    Serial.begin(115200);
    mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX=GPIO16, TX=GPIO17
    Blynk.begin(auth, ssid, pass); // Start Blynk

    // Initialize LED state
    Blynk.virtualWrite(V10, 0); // Set LED for sensor 1 to OFF
    Blynk.virtualWrite(V11, 0); // Set LED for sensor 2 to OFF
}

void loop() {
    // Blynk run
    Blynk.run();

    // Check if there's data available from the Arduino
    if (mySerial.available()) {
        String data = mySerial.readStringUntil('\n'); // Read a line of data
        processData(data); // Process the received data
    }
}

// Function to process the data and send it to Blynk
void processData(String data) {
    // Split the received string by comma
    int commaIndex = data.indexOf(',');
    String sensor1 = data.substring(0, commaIndex);
    String sensor2 = data.substring(commaIndex + 1,data.length()-1);

    // Update the LED state based on sensor values
    int ledState1 = (sensor1 == "Occupied") ? 1 : 0; // LED ON for "Occupied", OFF for "Available"
    int ledState2 = (sensor2 == "Occupied") ? 1 : 0; // LED ON for "Occupied", OFF for "Available"

    // Send the LED states to the corresponding Blynk virtual pins
    Blynk.virtualWrite(V10, ledState1);
    Blynk.virtualWrite(V11, ledState2);

    // Print the received values for debugging
    Serial.print("Sensor 1: ");
    Serial.println(sensor1);
    Serial.print("Sensor 2: ");
    Serial.println(sensor2);
}
