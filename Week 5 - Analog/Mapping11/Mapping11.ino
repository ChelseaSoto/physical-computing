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
  if(digitalRead(CPLAY_SLIDESWITCHPIN)){
    int points = 0;

    //while loop to keep the player going until they win five times in a row
    while(points < 5){
    //initialize x and y axis variables
    float xValue = CircuitPlayground.motionX();
    float yValue = CircuitPlayground.motionY();
    
    //random number between 0-3
    int says = random(0,4);
    //switch statement  
    switch(says){
      case 0: //left +y
        //lights up the left half of the board
        CircuitPlayground.setPixelColor(7, 255, 255, 255);//#, r, g, b
        CircuitPlayground.setPixelColor(8, 255, 255, 255);
        CircuitPlayground.setPixelColor(9, 255, 255, 255);
        CircuitPlayground.setPixelColor(0, 255, 255, 255);
        CircuitPlayground.setPixelColor(1, 255, 255, 255);
        CircuitPlayground.setPixelColor(2, 255, 255, 255);
        delay(debounce);
        
        //checks if the player rotated it in the correct direction
        points = positiveCheck(yValue, points);
        break;
      case 1: //right -y
        //lights up the right half of the board
        CircuitPlayground.setPixelColor(7, 255, 255, 255);//#, r, g, b
        CircuitPlayground.setPixelColor(6, 255, 255, 255);
        CircuitPlayground.setPixelColor(5, 255, 255, 255);
        CircuitPlayground.setPixelColor(4, 255, 255, 255);
        CircuitPlayground.setPixelColor(3, 255, 255, 255);
        CircuitPlayground.setPixelColor(2, 255, 255, 255);
        delay(debounce);
        
        //checks if the player rotated it in the correct direction
        if (yValue < 0){ //yes
          //flash green
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 0, 255, 0);
          }
          
          delay(debounce);

          CircuitPlayground.clearPixels();
          points++;
        }else{
          //flash red
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
          }
          
          delay(debounce);
          CircuitPlayground.clearPixels();
          //flash a second time
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
          }
          CircuitPlayground.clearPixels();
          points = 0;
        }
        break;
      case 2: //up +x
        //lights up the upper half of the board
        CircuitPlayground.setPixelColor(9, 255, 255, 255);//#, r, g, b
        CircuitPlayground.setPixelColor(8, 255, 255, 255);
        CircuitPlayground.setPixelColor(7, 255, 255, 255);
        CircuitPlayground.setPixelColor(6, 255, 255, 255);
        CircuitPlayground.setPixelColor(5, 255, 255, 255);
        delay(debounce);
        
        //checks if the player rotated it in the correct direction
        points = positiveCheck(yValue, points);
        break;
      case 3: //down -x
        //lights up the upper half of the board
        CircuitPlayground.setPixelColor(4, 255, 255, 255);//#, r, g, b
        CircuitPlayground.setPixelColor(3, 255, 255, 255);
        CircuitPlayground.setPixelColor(2, 255, 255, 255);
        CircuitPlayground.setPixelColor(1, 255, 255, 255);
        CircuitPlayground.setPixelColor(0, 255, 255, 255);
        
        delay(debounce);
        CircuitPlayground.clearPixels();
        
        //checks if the player rotated it in the correct direction
        if (xValue < 0){ //yes
          //flash green
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 0, 255, 0);
          }
          
          delay(debounce);

          CircuitPlayground.clearPixels();
          points++;
        }else{
          //flash red
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
          }
          
          delay(debounce);
          CircuitPlayground.clearPixels();
          //flash a second time
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
          }
          CircuitPlayground.clearPixels();
          points = 0;
        }


        break;
    }
    }
  }
}

int positiveCheck(float value, int points){
    if (value > 0){ //yes
          //flash green
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 0, 255, 0);
          }
          
          delay(debounce);

          CircuitPlayground.clearPixels();
          points++;
        }else{
          //flash red
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
          }
          
          delay(debounce);
          CircuitPlayground.clearPixels();
          //flash a second time
          for(int i = 0; i <= 9; i++){
            CircuitPlayground.setPixelColor(i, 255, 0, 0);
          }
          CircuitPlayground.clearPixels();
          points = 0;
        }
    return points;
  }


/*
toggle switch turn on or off
when turned on, animation maybe before

int points = 0;
while(points < 5){
randomize numbers 
0 left
1 right
2 up
3 down
-
4 block light
5 sound


switch statement
case 0:
  light up left half
  check if player tilts left
  if yes -> flash green or continue next, points++
  if no -> flash red twice, points = 0
  break; //will this break the switch statement only or the while loop too?
case 1: 
  light up right half
  check if player tilts right
  if yes -> flash green or continue next, points++
  if no -> flash red twice, points = 0
  break;
.
.
.
}

once points == 5 -> flash green twice or something
*/