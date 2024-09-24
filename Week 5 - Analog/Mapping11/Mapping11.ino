/*
Analog Team 11
Kel Diaz-Acosta and Chelsea Soto
This is a Simon Says game. Neopixels light up to give a command and the player must do what it says.
*/
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

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