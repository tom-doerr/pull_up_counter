//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use of a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 Library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 Example added 9 Jul 2009
 by Tom Igoe
 Modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include "SR04.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);




#define TRIG_PIN 3
#define ECHO_PIN 2 

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance;
long rep_counter;
long last_val;
long raw_distance;
long distance_smoothed;
float gamma;

void setup() {
  
   Serial.begin(9600);//Initialization of Serial Port
   delay(1000);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World!");
  gamma = 0.99;
}

void loop() {
  raw_distance = sr04.Distance();
  if (raw_distance == 1185) {
    distance = 0;
  }
  else {
    distance = raw_distance;
  }
   distance_smoothed = (0.9 * distance_smoothed) + (0.1 * distance);
   //distance = sr04.Distance();
   if (distance_smoothed < 9
   
   0) {
    if (last_val >= 50) {
      rep_counter += 1;
    }
   }
   last_val = distance_smoothed;
   
   Serial.print(distance_smoothed);
   Serial.println("cm");//The difference between "Serial.print" and "Serial.println" 
                        //is that "Serial.println" can change lines.
   delay(10);

  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(rep_counter);
  lcd.print("   ");
  lcd.print(distance_smoothed);
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 60000);
  lcd.print(" min");
}
