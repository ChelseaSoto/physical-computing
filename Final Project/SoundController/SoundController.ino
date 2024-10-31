#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_hu_HU.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_pt_PT.h>

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

#include <math.h>

// assign pins
const int potent = A4; // potentiometer middle pin
const int eSwitch = A7; // external switch middle pin
const int redLED = A3;
const int blueLED = A2;

// constant variables
const int debounce = 100; // Debounce time in ms for each sound check
const int threshold = 5; // Sound threshold for jumping
const int valueNum = 10; // Number of values to calculate average sound level
unsigned long lastAverageTime = 0; // Timer for average calculation
const unsigned long averageInterval = 15000; // Time in ms between average calculations

float baselineAverage = 0.0; // Store initial baseline

void setup() {
  // initialize libraries
  CircuitPlayground.begin();
  Keyboard.begin();

  // serial initialization
  Serial.begin(9600);

  // initialize pins
  pinMode(potent, INPUT); // potentiometer
  pinMode(eSwitch, INPUT_PULLUP); // external switch
  pinMode(redLED, OUTPUT);          // red LED for Fireboy
  pinMode(blueLED, OUTPUT);         // blue LED for Watergirl

  // Set initial LED states to off
  digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);

  // Calculate initial baseline
  baselineAverage = checkAverage(valueNum);
}

void loop() {
  // Check if the slide switch is on
  if (digitalRead(CPLAY_SLIDESWITCHPIN)) {

    // Check if it's time to recalculate the baseline average
    if (millis() - lastAverageTime >= averageInterval) {
      baselineAverage = checkAverage(valueNum);
      lastAverageTime = millis();
    }

    // Check switch state for mode selection
    bool mode = digitalRead(eSwitch) == LOW;

    // Potentiometer value check
    int potValue = analogRead(potent);

    // FIREBOY CONTROLS
    if (mode) {
      // LEDs
      digitalWrite(redLED, HIGH);   // Turn on red LED for Fireboy
      digitalWrite(blueLED, LOW);   // Ensure blue LED is off
      
      // Movement
      if (potValue < 462) { // Move right
        Keyboard.press(KEY_RIGHT_ARROW);
        Keyboard.release(KEY_LEFT_ARROW);
      } else if (potValue > 562) { // Move left
        Keyboard.press(KEY_LEFT_ARROW);
        Keyboard.release(KEY_RIGHT_ARROW);
      } else { // No movement
        Keyboard.release(KEY_LEFT_ARROW);
        Keyboard.release(KEY_RIGHT_ARROW);
        Serial.println("not moving");
      }

      // Sound check for jumping
      float currentValue = CircuitPlayground.soundSensor();
      float difference = baselineAverage - currentValue;
      if (difference >= threshold) {
        Keyboard.press(KEY_UP_ARROW); // Jump
      } else {
        Keyboard.release(KEY_UP_ARROW); // Stop jump
      }
    }

    // WATERGIRL CONTROLS
    else {
      // LEDs
      digitalWrite(blueLED, HIGH);   // Turn on blue LED for Watergirl
      digitalWrite(redLED, LOW);     // Ensure red LED is off

      // Movement
      if (potValue < 462) { // Move right
        Keyboard.press('D');
        Keyboard.release('A');
      } else if (potValue > 562) { // Move left
        Keyboard.press('A');
        Keyboard.release('D');
      } else { // No movement
        Keyboard.release('A');
        Keyboard.release('D');
        Serial.println("not moving");
      }

      // Sound check for jumping
      float currentValue = CircuitPlayground.soundSensor();
      float difference = baselineAverage - currentValue;
      if (difference >= threshold) {
        Keyboard.press('W'); // Jump
      } else {
        Keyboard.release('W'); // Stop jump
      }
    }

    // Small delay to avoid switch debounce issues
    delay(50);
  }
}

// Function to check the average sound level
float checkAverage(int valueNum) {
  float valueSum = 0.0;
  unsigned long lastDebounceTime = 0;
  int count = 0;

  while (count < valueNum) {
    if (millis() - lastDebounceTime >= debounce) {
      lastDebounceTime = millis();
      float currentValue = CircuitPlayground.soundSensor();
      valueSum += currentValue;
      count++;
      Serial.print("Current sound level: ");
      Serial.println(currentValue);
    }
  }

  float average = valueSum / valueNum;

  Serial.print("AVERAGE SOUND LEVEL: ");
  Serial.println(average);

  return average;
}
