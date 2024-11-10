Upload the Code:

Upload the Arduino code to the Arduino board.
Then, upload the ESP32 code to the ESP32.
Connect to Wi-Fi:

Open the Serial Monitor at 115200 baud on the ESP32 to confirm that it connects to Wi-Fi and Blynk. You should see the IP address of the ESP32 printed once connected.
Test the API:

Copy the IP address displayed in the Serial Monitor.
Open a browser or use an HTTP client (e.g., Postman) and enter the following URL:
arduino
Copy code
http://<ESP32_IP>/status
You should receive a JSON response showing the status of each parking slot
