int parking_slot1_ir_s = 4; // parking slot 1 infrared sensor connected with pin number 4 of Arduino
int parking_slot2_ir_s = 5; // parking slot 2 infrared sensor connected with pin number 5 of Arduino

String sensor1; // To hold the status of sensor 1
String sensor2; // To hold the status of sensor 2

void setup() {
    Serial.begin(9600); // Initialize Serial for communication
    pinMode(parking_slot1_ir_s, INPUT); // Set pin 4 as INPUT
    pinMode(parking_slot2_ir_s, INPUT); // Set pin 5 as INPUT
}

void loop() {
    readParkingSlots(); // Read the status of parking slots
    String cdata = sensor1 + "," + sensor2; // Create a comma-separated string of sensor values
    Serial.println(cdata); // Send data to ESP32
    delay(6000); // 6000 milliseconds (6 seconds)
}

void readParkingSlots() {
    // Check status of parking slot 1
    if (digitalRead(parking_slot1_ir_s) == LOW) {
        sensor1 = "Occupied"; // Slot 1 is occupied
    } else {
        sensor1 = "Available"; // Slot 1 is available
    }

    // Check status of parking slot 2
    if (digitalRead(parking_slot2_ir_s) == LOW) {
        sensor2 = "Occupied"; // Slot 2 is occupied
    } else {
        sensor2 = "Available"; // Slot 2 is available
    }
}
