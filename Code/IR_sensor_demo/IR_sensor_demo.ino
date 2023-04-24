/*
 * The code that was used to test the rotary encoder circuit
*/
#define PIN A0

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  double value = analogRead(PIN);
  Serial.println(value);
  delay(500);

}
