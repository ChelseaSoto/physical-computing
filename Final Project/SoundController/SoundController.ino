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

// constant variables
const int debounce = 100;
const int threshold = 10;
const int valueNum = 10; // number of values to take in

void setup() {
    // initialize libraries
    CircuitPlayground.begin();
    Keyboard.begin();

    // serial initialization
    Serial.begin(9600);

    // initialize pins
    pinMode(potent, INPUT);       // potentiometer
    pinMode(eSwitch, INPUT_PULLUP);  // external switch
}

void loop() {
    // Check if the slide switch is on
    if (digitalRead(CPLAY_SLIDESWITCHPIN)) {
        
        // Check sound level average every loop
        float average = checkAverage(valueNum);

        // Check switch state for mode selection
        bool mode = digitalRead(eSwitch) == LOW;

        if (mode) {  // FIREBOY CONTROLS
            // Potentiometer value check
            int potValue = analogRead(potent);

            // Moving left or right
            if (potValue < 490) {
                Keyboard.press(KEY_LEFT_ARROW);
                Keyboard.release(KEY_RIGHT_ARROW);
            } else if (potValue > 513) {
                Keyboard.press(KEY_RIGHT_ARROW);
                Keyboard.release(KEY_LEFT_ARROW);
            } else {
                Keyboard.releaseAll();  // No movement
                Serial.println("not moving");
            }

            // Check current sound level
            float currentValue = CircuitPlayground.soundSensor();

            // Calculate difference to compare with threshold
            float difference = average - currentValue;

            // Jumping
            if (difference >= threshold) {
                Keyboard.press(KEY_UP_ARROW);
            } else {
                Keyboard.release(KEY_UP_ARROW);
            }

        } else {  // WATERGIRL CONTROLS
            // Potentiometer value check
            int potValue = analogRead(potent);

            // Moving left or right
            if (potValue < 490) {
                Keyboard.press('A');
                Keyboard.release('D');
            } else if (potValue > 513) {
                Keyboard.press('D');
                Keyboard.release('A');
            } else {
                Keyboard.releaseAll();  // No movement
                Serial.println("not moving");
            }

            // Check current sound level
            float currentValue = CircuitPlayground.soundSensor();

            // Calculate difference to compare with threshold
            float difference = average - currentValue;

            // Jumping
            if (difference >= threshold) {
                Keyboard.press('W');
            } else {
                Keyboard.release('W');
            }
        }

        // Small delay to avoid switch debounce issues
        delay(50);
    }
}

// Function to check the average sound level
float checkAverage(int valueNum) {
    float valueSum = 0.0;

    for (int i = 0; i < valueNum; i++) {
        float currentValue = CircuitPlayground.soundSensor();
        valueSum += currentValue;
        Serial.print("Current sound level: ");
        Serial.println(currentValue);
        delay(debounce);
    }

    float average = valueSum / valueNum;

    Serial.print("AVERAGE SOUND LEVEL: ");
    Serial.println(average);

    return average;
}
