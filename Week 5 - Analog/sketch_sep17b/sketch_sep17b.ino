/*
More LEDs turn on when the measurement is higher (force pad, light sensor, etc.)
*/
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A2, INPUT);
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A2);
  Serial.println(value);
  delay(100);
  CircuitPlayground.clearPixels();
  int pixels = map(value, 0, 1023, 0, 9); //spits out a value between 0 to 9. Highest measurement is 1023
  for(int i = 0; i < pixels; i++){
    CircuitPlayground.setPixelColor(i, 0xFF00FF);
  }
}
