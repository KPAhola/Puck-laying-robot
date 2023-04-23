#define CLK 2
#define DIO 3
#define STB 4


static const uint8_t digits[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
static int value = 0;

void sendCommand(uint8_t command) {
  digitalWrite(STB, LOW);
  shiftOut(DIO, CLK, LSBFIRST, command);
  digitalWrite(STB, HIGH);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK, OUTPUT);
  pinMode(DIO, OUTPUT);
  pinMode(STB, OUTPUT);
  sendCommand(0x8f);

}

void loop() {
  // put your main code here, to run repeatedly:
  display_value(value);
  value++;
  delay(100);
}

void display_value(int value) {
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
