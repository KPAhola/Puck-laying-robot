// C++ code
//
/*
 * Todo: When the motor turns on, the display turns off
 * 
*/
#define ULTRASONIC_TRIGGER 12
#define ULTRASONIC_ECHO 13
#define ULTRASONIC_POWER 11
#define CLK 9
#define DIO 8
#define STB 7
#define BUTTON 5
#define ROTATION 4
#define MOTOR 3

#define STOP_DISTANCE 10
#define DISTANCE_PER_IR_PULSE 1
#define SOUND_WAVE_TRAVEL_TIME_TO_DISTANCE_MULTIPLIER 0.01723

static const uint8_t digits[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};

static double distance_travelled = 0;
static boolean is_running = false;

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

void sendCommand(uint8_t command) {
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, command);
  digitalWrite(STB, HIGH);
}

void display_value(double value) {
  if (value > 9999) {
    value = 9999;
  }
  int digit1 = value / 1000;
  value -= 1000 * digit1;
  int digit2 = value / 100;
  value -= 100 * digit2;
  int digit3 = value / 10;
  value -= 10 * digit3;
  int digit4 = value;
  if (value - digit4 >= 0.5) {
    digit4++;
  }
  sendCommand(0x40);
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, 0xc0);
  shiftOut(DIO, CLK, LSBFIRST, digits[digit1]);
  shiftOut(DIO, CLK, LSBFIRST, 0x00);
  shiftOut(DIO, CLK, LSBFIRST, digits[digit2]);
  shiftOut(DIO, CLK, LSBFIRST, 0x00);
  shiftOut(DIO, CLK, LSBFIRST, digits[digit3]);
  shiftOut(DIO, CLK, LSBFIRST, 0x00);
  shiftOut(DIO, CLK, LSBFIRST, digits[digit4]);
  shiftOut(DIO, CLK, LSBFIRST, 0x00);
  digitalWrite(STB, HIGH);
}

void setup()
{
  pinMode(MOTOR, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DIO, OUTPUT);
  pinMode(STB, OUTPUT);
  pinMode(ROTATION, INPUT);
  pinMode(ULTRASONIC_POWER, OUTPUT);
  digitalWrite(ULTRASONIC_POWER, HIGH);
  sendCommand(0x8f);
}

void loop()
{
  if (digitalRead(BUTTON)) {
      is_running = true;
      delay(1000);
      while(is_running) {
         double obstacle_distance = SOUND_WAVE_TRAVEL_TIME_TO_DISTANCE_MULTIPLIER * readUltrasonicDistance(ULTRASONIC_TRIGGER, ULTRASONIC_ECHO);
          if (obstacle_distance <= STOP_DISTANCE) {
            digitalWrite(MOTOR, HIGH);
          } else {
            analogWrite(MOTOR, LOW);
          }
        if (digitalRead(ROTATION)) {
        distance_travelled += DISTANCE_PER_IR_PULSE;
        }
        display_value(distance_travelled);
        if (digitalRead(BUTTON)) {
          is_running = false;
        }
      }
    }
  delay(10); // Wait for 10 millisecond(s)
}
