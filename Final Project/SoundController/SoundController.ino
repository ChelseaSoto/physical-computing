/*

*/

#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_hu_HU.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_pt_PT.h>
#include <Keyboard_sv_SE.h>

#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

#include <math.h>


//assign pins

// potentiometer
const int potent1 = A4;
const int potent2 = A5;
const int potent3 = A6;

//external switch
const int switch1 = A7;
const int switch2 = A0;

//constant variables
const int debounce = 100;
const int threshold = 10;
const int valueNum = 10;  //number of values to take in

void setup() {
  // put your setup code here, to run once:

  //initialize libraries
  CircuitPlayground.begin();
  Keyboard.begin();

  //serial initialization
  Serial.begin(9600);

  //initialize pins
  pinMode(potent, INPUT);  // potentiometer
  pinMode(toggle, INPUT);  // external switch
}

void loop() {
  // put your main code here, to run repeatedly:

  //initialize and call function to check the average
  float average = checkAverage(valueNum);

  //checks which character is toggled
  bool mode = analogRead(toggle);

  if (mode == true) {  //FIREBOY CONTROLS

    //checks potentiometer value
    int potValue = analogRead(potent);

    //moving
    if (potValue < 500) {
      Keyboard.write(KEY_LEFT_ARROW);
    } else if (potValue > 523) {
      Keyboard.write(KEY_RIGHT_ARROW);
    } else {
      Serial.println("not moving");
    }

    //checks current sound level
    float currentValue = CircuitPlayground.soundSensor();

    //checks the difference to compare the threshold to
    float difference = average - currentValue;

    //jumping
    if (difference >= threshold) {
      Keyboard.write(KEY_UP_ARROW);
    }

  } else {  //WATERGIRL CONTROLS

    //checks potentiometer value
    int potValue = analogRead(A1);

    //moving
    if (potValue < 500) {
      Keyboard.write('A');
    } else if (potValue > 523) {
      Keyboard.write('D');
    } else {
      Serial.println("not moving");
    }

    //checks current sound level
    float currentValue = CircuitPlayground.soundSensor();

    //checks the difference to compare the threshold to
    float difference = average - currentValue;

    //jumping
    if (difference >= threshold) {
      Keyboard.write('W');
    }
  }
}


//function to check the average
float checkAverage(int valueNum) {

  //initialize the current value
  float valueSum = 0.00;

  for (int i = 0; i < valueNum; i++) {
    float currentValue = CircuitPlayground.soundSensor();
    valueSum += currentValue;
    Serial.print("current value: ");
    Serial.println(currentValue);
    Serial.print("total sum: ");
    Serial.println(valueSum);
    delay(debounce);
  }

  float average = valueSum / valueNum;

  Serial.print("AVERAGE: ");
  Serial.println(average);

  return average;
}