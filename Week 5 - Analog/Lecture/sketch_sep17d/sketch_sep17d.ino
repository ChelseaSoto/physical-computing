/*
Doing it without the analog but the built in temperature sensor.
Works like a thermometer in Celsius
*/
#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //pinMode(A8, INPUT);

  
  CircuitPlayground.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //int value = analogRead(A8);
  
  //using the library
  int value = CircuitPlayground.temperatureSensor();


  Serial.println(value);
  delay(100);
  CircuitPlayground.clearPixels();
  int pixels = map(value, 0, 1023, 0, 9); //spits out a value between 0 to 9. Highest measurement is 1023
  for(int i = 0; i < pixels; i++){
    CircuitPlayground.setPixelColor(i, 0xFF00FF);
  }
}
