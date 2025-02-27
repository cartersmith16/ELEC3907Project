#define LED_1 12
#define LED_2 11
#define LED_3 10
#define LED_4 9

#define BUTTON_1 8
#define BUTTON_2 7
#define BUTTON_3 6
#define BUTTON_4 5



void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setup complete! Starting...");

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);

indicateStart();

Serial.println("3 input sequence!");
resetLEDsOff();
playRound(3);
Serial.println("the 4 input sequence!");
resetLEDsOff();
playRound(4);
Serial.println("5 input sequence!");
resetLEDsOff();
playRound(5);
}

void loop() {
}

void playRound(int amount) {
  bool correct = false;
  bool complete = false;
  int* randomLightSequence = randomSequence(amount);  //Commented out for testing
  //int random3LightSequence[3] = { 12, 12, 12 };

  while (!correct) {
    Serial.println("Sequence Will Start in 3 seconds");
    delay(3000);

    displaySequence(amount, randomLightSequence);
    correct = getInputs(amount, randomLightSequence);
  }
  Serial.println("Correct sequence!");
}


void indicateStart() {
  delay(1000);
  unsigned long startTime = millis();
  while (millis() - startTime < 1500) {
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
    digitalWrite(LED_4, HIGH);

    delay(250);

    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
    digitalWrite(LED_4, LOW);

    delay(250);
  }
  delay(1000);
}

int* randomSequence(int size) {

  randomSeed(analogRead(0));
  int* randomArray = new int[size];


  for (int i = 0; i < size; i++) {
    randomArray[i] = random(9, 13);
  }

  Serial.println("The numbers are");
  for (int i = 0; i < size; i++) {
    Serial.println(randomArray[i]);
  }
  return randomArray;
}

void displaySequence(int size, int* sequence) {
  for (int i = 0; i < size; i++) {
    digitalWrite(sequence[i], HIGH);
    Serial.println("Lighting up ");
    Serial.println(sequence[i]);

    delay(400);
    digitalWrite(sequence[i], LOW);
    delay(400);
  }
}

bool getInputs(int size, int* sequence) {

  bool buttonState[4] = { false, false, false, false };      // To track button states
  bool prevButtonState[4] = { false, false, false, false };  // Previous button states

  int* userInput = new int[size];
  int pressCount = 0;
  unsigned long startMillis = millis();  // Track elapsed time
  unsigned long timeout = 10000;
  resetLEDsOff();

  Serial.println("Waiting for your input");
   while (pressCount < size && (millis() - startMillis) < timeout) { //commented out timeout for debugging
    //while (pressCount < size) { 

    // Read button states
    buttonState[0] = digitalRead(BUTTON_1);
    buttonState[1] = digitalRead(BUTTON_2);
    buttonState[2] = digitalRead(BUTTON_3);
    buttonState[3] = digitalRead(BUTTON_4);

    // Check for state changes (LOW to HIGH)
    if (buttonState[0] && !prevButtonState[0]) {
      digitalWrite(LED_1, HIGH);
      userInput[pressCount] = 12;
      Serial.println("ONE was clicked");
      if (!checkInput(userInput[pressCount], sequence[pressCount])) {
        errorFlash();
        return false;
      };
      pressCount = pressCount + 1;

    } else {
      digitalWrite(LED_1, LOW);
    }

    if (buttonState[1] && !prevButtonState[1]) {
      digitalWrite(LED_2, HIGH);
      userInput[pressCount] = 11;
      Serial.println("TWO was clicked");
      if (!checkInput(userInput[pressCount], sequence[pressCount])) {
        errorFlash();
        return false;
      };
      pressCount = pressCount + 1;

    } else {
      digitalWrite(LED_2, LOW);
    }

    if (buttonState[2] && !prevButtonState[2]) {
      digitalWrite(LED_3, HIGH);
      userInput[pressCount] = 10;
      Serial.println("THREE was clicked");
      if (!checkInput(userInput[pressCount], sequence[pressCount])) {
        errorFlash();        
        return false;
      };
      pressCount = pressCount + 1;

    } else {
      digitalWrite(LED_3, LOW);
    }

    if (buttonState[3] && !prevButtonState[3]) {
      digitalWrite(LED_4, HIGH);
      userInput[pressCount] = 9;

      Serial.println("FOUR was clicked");
      if (!checkInput(userInput[pressCount], sequence[pressCount])) {
        errorFlash();       
        return false;
      };
      pressCount = pressCount + 1;

    } else {
      digitalWrite(LED_4, LOW);
    }

    // Update previous button states
    for (int i = 0; i < 4; i++) {
      prevButtonState[i] = buttonState[i];
    }

    delay(50);  // Add a small delay for debounce
  }
  Serial.println("Out the while in get input");
    for (int i = 0; i < size; i++) {
      Serial.println("userInput:");
      Serial.println(userInput[i]);
    

  if (sequence[i] != userInput[i]) {
    delete[] userInput;
    return false;
  } 
  }
  Serial.println("GetInput returning true");
  delete[] userInput;
  return true;
}

bool checkInput(int userInput, int sequenceValue) {
  if (userInput != sequenceValue) {
    Serial.println("Incorrect Button Try again");

    return false;
  } else {
    Serial.println("Correct Button");
    return true;
  }
}

void resetLEDsOff() {
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
}

void setLEDOn() {
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_4, HIGH);
}

void errorFlash(){
  Serial.println("Error Flash");
  resetLEDsOff();
  delay(1000);
  setLEDOn();
  delay(5000);
  resetLEDsOff();
}

void buttonFlash(int LED, int button) {
  if (digitalRead(button) == HIGH) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
