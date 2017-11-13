
/*

ME313 Personal Energy
BATTERY VOLTAGE READ EXAMPLE

Nov 11, 2017

@Adafruit
@Dickson Chow

Public Domain

*/


// Include libraries for SDCard read/write
#include <SPI.h>
#include <SD.h>


// The analogue pin that reads the battery voltage in built-in 100k resistor divider
#define VBATPIN A7


/* the setup function runs once when you press reset or power the board */
void setup() {
  // initialize digital pin 13 as an output for LED.
  pinMode(13, OUTPUT);
}



/* the loop function runs over and over again forever */
void loop() {

  //BLINK TEST
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second


/*
BATTERY VOLTAGE READ
LiPo battery full will read 4.2v 
and will settle at 3.7v and slowly sink down to 3.2v
before the protection circuit cuts it off.

4.2v = battery full
~3.7v = battery normal
3.2v = battery low

*/
float measuredvbat = analogRead(VBATPIN);
measuredvbat *= 2;    // we divided by 2, so multiply back
measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
measuredvbat /= 1024; // convert to voltage
Serial.print("VBat: " ); Serial.println(measuredvbat); // Prints the voltage to serial monitor



  
}
