// C++ code
//
#define STOP_DISTANCE 10
#define SOUND_WAVE_TRAVEL_TIME_TO_DISTANCE_MULTIPLIER 0.01723

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
    digitalWrite(3, 1);
   } else {
  	analogWrite(3, map(analogRead(A5), 0, 1023, 0, 255));
   }
  Serial.println(obstacle_distance);
  delay(500); // Wait for 500 millisecond(s)
}
