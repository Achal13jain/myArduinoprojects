// Components Required:
// Arduino Uno (with ATmega8)
// Ultrasonic sensor (HC-SR04)
// LCD display (16x2)
// Breadboard and jumper wires

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
float cm; //initializing variables
float inches;
long readUltrasonicDistance(int triggerPin, int echoPin)//function to calculate distances using ultrasonic method
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);// Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);// Reads the echo pin, and returns
  return pulseIn(echoPin, HIGH); // the sound wave travel time in microseconds
}

void setup()
{
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.print("--> Distance <--");
  delay(3000);
  lcd.clear();
}

void loop()
{
  cm = 0.0344/2 * readUltrasonicDistance(3, 2);//calling readUltrasonicDistance function within the loop
  inches = (cm / 2.54);
  lcd.setCursor(0,0);
  lcd.print("Inches");
  lcd.setCursor(4,0);
  lcd.setCursor(12,0);
  lcd.print("cm");
  lcd.setCursor(1,1);
  lcd.print(inches, 1);
  lcd.setCursor(11,1);
  lcd.print(cm, 1);
  lcd.setCursor(14,1);
  delay(2000);
  lcd.clear();
}
