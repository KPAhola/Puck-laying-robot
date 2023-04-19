// C++ code
//
#define STOP_DISTANCE 10
#define SOUND_WAVE_TRAVEL_TIME_TO_DISTANCE_MULTIPLIER 0.01723

static double distance_travelled = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void display_distance(double distance) {
  int digit1 = distance / 1000;
  distance -= 1000 * digit1;
  int digit2 = distance / 100;
  distance -= 100 * digit2;
  int digit3 = distance / 10;
  distance -= 10 * digit3;
  int digit4 = distance;
  Serial.print(digit1);
  Serial.print(digit2);
  Serial.print(digit3);
  Serial.println(digit4);
}

void setup()
{
  pinMode(A5, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  double obstacle_distance = SOUND_WAVE_TRAVEL_TIME_TO_DISTANCE_MULTIPLIER * readUltrasonicDistance(10, 9);
  if (obstacle_distance <= STOP_DISTANCE) {
    digitalWrite(3, HIGH);
   } else {
  	analogWrite(3, map(analogRead(A5), 0, 1023, 0, 255));
   }
  display_distance(distance_travelled);
  delay(500); // Wait for 500 millisecond(s)
}
