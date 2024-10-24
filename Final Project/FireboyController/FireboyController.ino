/*
Final Team 3
Chelsea Soto and Molly Guinn

This is 1 of 2 scripts for our final controller. This is specifically for our Fireboy Controller which reads temperature.
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

const int debounce = 100000;
const int threshold = 10;

float valueSum = 0.00;    //the overall sum
const int valueNum = 10;  //number of values to take in


void setup() {
  // put your setup code here, to run once:

  //initialize libraries
  CircuitPlayground.begin();
  Keyboard.begin();

  //serial initialization
  Serial.begin(9600);

  //initialize pins
  pinMode(A1, INPUT);  // potentiometer
  pinMode(A2, INPUT);  // external switch
  pinMode(A3, INPUT);  // external thermal sensor
}

void loop() {
  // put your main code here, to run repeatedly:

  //initialize and call function to check the average
  float average = checkAverage(valueSum, valueNum);

  //checks which character is toggled
  bool mode = analogRead(A2);

  if (mode = true) {  //FIREBOY CONTROLS

    //checks potentiometer value
    int potValue = analogRead(A1);

    //moving
    if (potValue < 500) {
      Keyboard.write(KEY_LEFT_ARROW);
    } else if (potValue > 523) {
      Keyboard.write(KEY_RIGHT_ARROW);
    } else {
      Serial.println("not moving");
    }

    //checks current temperature
    float currentValue = analogRead(A3);

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

    //checks current temperature
    int currentValue = analogRead(A3);

    //checks the difference to compare the threshold to
    float difference = average - currentValue;

    //jumping
    if (difference >= threshold) {
      Keyboard.write('W');
    }
  }
}


//function to check the average
float checkAverage(float valueSum, int valueNum) {

  //initialize the current value
  float currentValue = 0.00;

  for (int i = 0; i < valueNum; i++) {
    currentValue = analogRead(A3);
    valueSum = valueSum + currentValue;
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