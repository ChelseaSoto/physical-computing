/*
Analog Team 11
Kel Diaz-Acosta and Chelsea Soto
This is a Simon Says game. Neopixels light up to give a command and the player must do what it says.
*/
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

const int debounce = 25;
const int threshold = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(neo, OUTPUT);
  CircuitPlayground.begin();
  pinMode(CPLAY_SLIDESWITCHPIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(CPLAY_SLIDESWITCHPIN)) {
    int points = 0;

    //while loop to keep the player going until they win five times in a row
    while (points < 5) {
      //initialize x and y axis variables
      float xValue = CircuitPlayground.motionX();
      float yValue = CircuitPlayground.motionY();

      //random number between 0-3
      int says = random(0, 4);
      //switch statement
      switch (says) {
        case 0:  //left +y
          //lights up the left half of the board
          simonSays(0, 2);
          simonSays(7, 9);

          delay(debounce);
          CircuitPlayground.clearPixels();

          //checks if the player rotated it in the correct direction
          points = positiveCheck(yValue, points);
          break;
        case 1:  //right -y
          //lights up the right half of the board
          simonSays(2, 7);
          delay(debounce);
          CircuitPlayground.clearPixels();

          //checks if the player rotated it in the correct direction
          points = negativeCheck(yValue, points);
          break;
        case 2:  //up +x
          //lights up the upper half of the board
          simonSays(5, 9);
          delay(debounce);
          CircuitPlayground.clearPixels();

          //checks if the player rotated it in the correct direction
          points = positiveCheck(yValue, points);
          break;
        case 3:  //down -x
          //lights up the upper half of the board
          simonSays(0, 4);
          delay(debounce);
          CircuitPlayground.clearPixels();

          //checks if the player rotated it in the correct direction
          points = negativeCheck(xValue, points);

          break;
      }
    }


    //if win condition is met
    if (points >= 5) {
      //flash green three times
      for (int i; i <= 3; i++) {
        green();
      }

      //reset points to start the game again
      points = 0;
    }
  }
}

//Simon Says to . . .
void simonSays(int min, int max) {
  for (int i = min; i <= max; i++) {
    CircuitPlayground.setPixelColor(i, 255, 255, 255);  //#, r, g, b
  }
}

//checks if in the positive of the axis past the threshold
int positiveCheck(float value, int points) {
  if (value > threshold) {  //yes
    //flash green once
    green();
    points++;
  } else {  //no
    //flash red twice
    for (int i = 0; i <= 2; i++) {
      red();
    }
    points = 0;
  }
  return points;
}

//checks if in the negative of the axis past the threshold
int negativeCheck(float value, int points) {
  if (value < threshold) {  //yes
    //flash green once
    green();
    points++;
  } else {  //no
    //flash red twice
    for (int i = 0; i <= 2; i++) {
      red();
    }
    points = 0;
  }
  return points;
}

//flashes red once
void red() {
  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, 255, 0, 0);  //#, r, g, b
  }
  delay(debounce);
  CircuitPlayground.clearPixels();
}

//flashes green once
void green() {
  for (int i = 0; i <= 9; i++) {
    CircuitPlayground.setPixelColor(i, 0, 255, 0);  //#, r, g, b
  }
  delay(debounce);
  CircuitPlayground.clearPixels();
}