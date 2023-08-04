
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16,2); 
int sensor = 2; 
volatile byte counts;
unsigned int rpm; 
unsigned long previoustime; 
void count_function()
{ 
  counts++;         // pulses counter
}

void setup()
{
lcd.init (); //initialize LCD
 lcd. backlight ();// Turn on the backlight on LCD
  attachInterrupt(0, count_function, RISING); //Interrupts are called on Rise of Input
  pinMode(sensor, INPUT); //Sets sensor as input
  counts = 0; // initial counts set zero
  rpm = 0;    // zero initial rpm
  previoustime = 0; //for the first loop should be equal zero
}

void loop()
{
delay(1000);
detachInterrupt(0); //detaches the interrupt
rpm = (counts * 60000) / (millis() - previoustime); //counts the rate of pulses per ms so we need to make pulse per ms to pulses per minute by the factor of 60000
previoustime = millis(); //Resets the clock as said earlier
counts = 0; //Resets the counter
lcd.clear();
lcd.setCursor(0,0);
lcd.print("___TACHOMETER___");
lcd.setCursor(0,1);
lcd.print( rpm);
lcd.print(" RPM");
lcd.print(" ");
attachInterrupt(0, count_function, RISING); //Counter restarted so we can evaluate the rpm again.
}
