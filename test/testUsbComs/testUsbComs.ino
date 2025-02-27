String receivedNumber = "";  // Store the received number
bool startReceived = false;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setup complete! Starting...");
}

void loop() {
  if (Serial.available() > 0) {
    String receivedData = Serial.readStringUntil('\n');  // Read incoming data

    if (receivedData == "START") {
      startReceived = true;
      Serial.println("Received START command");
      if (receivedNumber.length() > 0) {
        Serial.println("Number: " + receivedNumber);
      }
    } else {
      receivedNumber = receivedData;  // Store the number
    }
  }
}
