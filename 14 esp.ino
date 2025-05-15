void setup() {
  // Initialize Serial communication at 115200 baud rate
  Serial.begin(115200);
  Serial.println("ESP32 Serial Communication Started!");
}

void loop() {
  // Check if data is available to read from Serial
  if (Serial.available()) {
    // Read the incoming data
    String receivedData = Serial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(receivedData);

    // Echo the received data back to the sender
    Serial.print("Echo: ");
    Serial.println(receivedData);
  }
}

