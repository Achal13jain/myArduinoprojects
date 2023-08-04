
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (0x27, 16,2); //
//float value=0;
//float rev=0;
//int rpm;
//int oldtime=0;
//int newtime;
//void isr() //interrupt service routine
//{
//rev++;
//}
int sensor = 2; // Hall sensor at pin 2
volatile byte counts;
unsigned int rpm; //unsigned gives only positive values
unsigned long previoustime; //it will store the last activation time to zero out the loop
void count_function()
{ /*The ISR function
    Called on Interrupt
    Update counts*/
  counts++;         // pulses counter
}
void setup()
{
lcd.init (); //initialize LCD
// Turn on the backlight on LCD. 
lcd. backlight ();
//attachInterrupt(digitalPinToInterrupt(2),isr,RISING); //attaching the interrupt
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
//newtime=millis()-oldtime; //finds the time 
//int wings= 2; // no of wings of rotating object, for disc object use 1 with white tape on one side
//int RPMnew = rev/wings; //here we used fan which has 3 wings
//rpm=(RPMnew/newtime)*60000; //calculates rpm
//oldtime=millis(); //saves the current time
//rev=0;
//lcd.clear();
//lcd.setCursor(0,0);
//lcd.print("___TACHOMETER___");
//lcd.setCursor(0,1);
//lcd.print( rpm);
//lcd.print(" RPM");
//lcd.print(" ");
//attachInterrupt(digitalPinToInterrupt(2),isr,RISING);

  rpm = (counts * 60000) / (millis() - previoustime); //counts the rate of pulses per ms so we need to make pulse per ms to pulses per minute by the factor of 60000
  previoustime = millis(); //Resets the clock as said earlier
  counts = 0; //Resets the counter
//  Serial.print("RPM=");
//  Serial.println(rpm); //Calculated values are displayed
  
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("___TACHOMETER___");
lcd.setCursor(0,1);
lcd.print( rpm);
lcd.print(" RPM");
lcd.print(" ");
attachInterrupt(0, count_function, RISING); //Counter restarted so we can evaluate the rpm again.
}
