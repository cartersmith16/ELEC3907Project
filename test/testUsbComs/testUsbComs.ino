String receivedData = "";  // Store the received number
bool startReceived = false;
bool arrayReceived = false;


void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setup complete! Starting...");
}

void loop() {
  if (Serial.available() > 0) {
    receivedData = Serial.readStringUntil('\n');  // Read incoming data

    if (!arrayReceived) {
      Serial.println("Received array:");
      parseAndPrintArray(receivedData);
      arrayReceived = true;  // Mark array as received
      Serial.println("Array received. Waiting for START...");
    } 
    else if (arrayReceived && receivedData == "START") {
      startReceived = true;
      Serial.println("Received START command. System starting...");
    }
  }

  if (startReceived) {
    // Main functionality goes here (e.g., running motors, sensors, etc.)
    Serial.println("System is running...");
    delay(1000);
  }
}

void parseAndPrintArray(String data) {
  int values[6];  
  int index = 0;
  char* token = strtok((char*)data.c_str(), ",");

  while (token != NULL && index < 6) {
    values[index++] = atoi(token);
    token = strtok(NULL, ",");
  }

  for (int i = 0; i < index; i++) {
    Serial.print("Value ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(values[i]);
  }
}