
/*

ME313 Personal Energy
BATTERY VOLTAGE READ AND SDCARD WRITE EXAMPLE

Nov 11, 2017

@Adafruit
@Dickson Chow

Public Domain

*/

// Include library to enable SD card read/write
#include <SPI.h>
#include <SD.h>

// Set the pin to enable SD card
#define cardSelect 4

// The analogue pin that reads the battery voltage in built-in 100k resistor divider
#define VBATPIN A7

// SD card specific
File logfile;

// blink out an error code if there is an error with the SD card
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}

uint8_t i=0; // make sure "i" is unsigned 8-bit integer for filename


// SETUP. RUNS ONCE
void setup() {

  delay (3000); // 3 second delay before startup
  
  Serial.println("\r\nBattery logger test");

  pinMode(13, OUTPUT); // Setup board LED
  pinMode(8, OUTPUT); // Setup SD card LED
  digitalWrite(13, HIGH); // Turn on board LED (system ON)

  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }
  // The following checks to see if there is already a file. If there is, a new file is created.
  char filename[15];
  strcpy(filename, "ENERGY00.TXT");
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = '0' + i/10;
    filename[7] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  // create the log file on the sd card
  logfile = SD.open(filename, FILE_WRITE);
  if( ! logfile ) {
    Serial.print("Couldnt create "); 
    Serial.println(filename);
    error(3);
  }
  Serial.print("Writing to "); 
  Serial.println(filename);

  Serial.println("Ready!");
}



// MAIN LOOP
void loop() {


  // Read the battery voltage
  float measuredvbat = analogRead(VBATPIN);
  measuredvbat *= 2;    // we divided by 2, so multiply back
  measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
  measuredvbat /= 1024; // convert to voltage
  Serial.print("Read VBAT: " ); Serial.println(measuredvbat); // Prints the voltage to serial monitor


  // Write to the log file
  digitalWrite(8, HIGH); // Turn on SD card LED
  logfile.print("VBAT = "); logfile.println(measuredvbat); // write the battery voltage to file
  Serial.print("Logged VBAT: "); Serial.println(measuredvbat); // print the battery voltage to serial monitor
  digitalWrite(8, LOW); // turn off SD card LED
  logfile.flush(); // save the data to the log file (increases power consumption)
  delay(1000); // delay 1 second
  
}
