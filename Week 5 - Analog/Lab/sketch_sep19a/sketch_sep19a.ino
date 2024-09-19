//Galaga left arrow, right arrow, and space bar
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

const int debounce = 100;
const int threshold = 500;

void setup() {
  // put your setup code here, to run once:
  //Circuit Playground Initialization
  Circuit.Playground.begin();
  pinMode(CPLAY_SLIDESWITCHPIN, INPUT_PULLUP); //7
  pinMode(CPLAY_LEFTBUTTON, INPUT_PULLDOWN);
  pinMode(CPLAY_RIGHTBUTTON, INPUT_PULLDOWN);

  //keyboard initialization
  Keyboard.begin();

  //erial initialization
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(CPLAY_SLIDESWITCHPIN)){ //SAFETY - runs code only when switch is flipped
    
    if(digitalRead(CPLAY_LEFTBUTTON)){ //if left button/arrow is pressed
      Keyboard.write(KEY_LEFT_ARROW); //KEY_LEFT_ARROW or 'A'
      delay(debounce);
    }
    
    if(digitalRead(CPLAY_RIGHTBUTTON)){ //if right button/arrow is pressed
      Keyboard.write(KEY_RIGHT_ARROW); //KEY_RIGHT_ARROW or 'D'
      delay(debounce);
    }

    int light = CircuitPlayground.lightSensor();
    if(light > 500){
      Keyboard.write(' ');
      delay(debounce);
    }
  }
}
