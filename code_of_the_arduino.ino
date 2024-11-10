int parking_slot1_ir_s = 4; // parking slot 1 infrared sensor connected with pin number 4 of Arduino
int parking_slot2_ir_s = 5; // parking slot 2 infrared sensor connected with pin number 5 of Arduino

String sensor1;
String sensor2;

void setup() {
    Serial.begin(9600); // Initialize Serial for communication
    pinMode(parking_slot1_ir_s, INPUT); // Set pin 4 as INPUT
    pinMode(parking_slot2_ir_s, INPUT); // Set pin 5 as INPUT
}

void loop() {
    readParkingSlots();
    String cdata = sensor1 + "," + sensor2;
    Serial.println(cdata);
    delay(6000);
}

void readParkingSlots() {
    if (digitalRead(parking_slot1_ir_s) == LOW) {
        sensor1 = "Occupied";
    } else {
        sensor1 = "Available";
    }

    if (digitalRead(parking_slot2_ir_s) == LOW) {
        sensor2 = "Occupied";
    } else {
        sensor2 = "Available";
    }
}
