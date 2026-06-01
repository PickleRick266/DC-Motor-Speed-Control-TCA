#include <Adafruit_LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>

// LCD
Adafruit_LiquidCrystal lcd(0);

// Potentiometer
const int potPin = A0;

// L293D motor driver pins
const int enablePin = 9;   // PWM speed control
const int input1 = 8;      // Motor direction
const int input2 = 7;      // Motor direction

// NeoPixel ring
const int ringPin = 6;
const int numPixels = 12;

Adafruit_NeoPixel ring(numPixels, ringPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(enablePin, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);

  // Set motor direction
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("DC Motor Control");

  ring.begin();
  ring.show();
}

void loop() {
  int potValue = analogRead(potPin);

  int motorSpeed = map(potValue, 0, 1023, 0, 255);
  int speedPercent = map(motorSpeed, 0, 255, 0, 100);
  int lightsOn = map(speedPercent, 0, 100, 0, numPixels);

  analogWrite(enablePin, motorSpeed);

  // LCD display
  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(speedPercent);
  lcd.print("%     ");

  lcd.setCursor(0, 1);
  lcd.print("PWM: ");
  lcd.print(motorSpeed);
  lcd.print("        ");

  // NeoPixel display
  ring.clear();

  for (int i = 0; i < lightsOn; i++) {
    if (speedPercent < 34) {
      ring.setPixelColor(i, ring.Color(0, 255, 0));       // green
    }
    else if (speedPercent < 67) {
      ring.setPixelColor(i, ring.Color(255, 150, 0));     // yellow
    }
    else {
      ring.setPixelColor(i, ring.Color(255, 0, 0));       // red
    }
  }

  ring.show();
}