/*
Prints out whatever is connected to A2 is measuring (force pad measures force, light sensor measures light, etc.)
*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(A2);
  Serial.println(value);
  delay(100);
}
