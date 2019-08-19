/*
 * Akhil Vasvani Rain Barrel With ESP8266 Code
 */

#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP085.h>
#include <SPI.h>
#include <Wire.h>

#define OLED_MOSI 0
#define OLED_CLK 1
#define OLED_DC 2
#define OLED_CS 3
#define OLED_RESET 4

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

Adafruit_BMP085 bmp; //creates barometric pressure sensor object

const int solenoidPin = 5;
const int pingPin = 7;
const int echoPin = 6;
const int buttonPin = 8;


// Code for ESP8266 
String inputString = ""; // a String to hold incoming data
String buff;
bool stringComplete = false;  // whether the string is complete
bool id;
int f,buf;
char x;

void setup() {
  // initialize serial communication:
  //Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT); //Sets the solenoid pin as an output
  pinMode(buttonPin, INPUT);    //Sets the button pin as an input
  bmp.begin();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.begin(SSD1306_SWITCHCAPVCC);
  
  // reserve 200 bytes for the inputString:
 inputString.reserve(200);
  
}

void loop() {
  // establish variables for duration of the ping,
  // the distance result, and the water level in centimeters:
  long duration, cm, waterLevel, pressure;
  
  // manual control of solenoid/rain barrel valve using push button:
  digitalWrite(buttonPin, HIGH); //writes push button as HIGH
  
  if(digitalRead(buttonPin) == LOW) { //if push button is pressed,
      digitalWrite(solenoidPin, HIGH);//valve is opened
  }
  
  if(digitalRead(buttonPin) == HIGH) { //if push button isn’t pressed
      digitalWrite(solenoidPin, LOW);  //valve is closed
  }
  
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The echo pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
 
  // cast pressure reading as a long int
  pressure = (long) bmp.readPressure();

  //Serial.print(cm);
  //Serial.print("cm");
  //Serial.println();

  delay(100);
  
  // water level is computed by subtracting sonar measurement by
  // height of the barrel (~85cm using tape measurer)
  waterLevel = 85.0 - cm;
              
  //Serial.print(waterLevel);
  //Serial.println("cm");

  // displays water level and atmospheric pressure measurements
  // in cm and Pa, respectively to OLED display:
  display.clearDisplay();
  display.setCursor(0, 0);
  
  display.print("Water Level: ");
  display.print(waterLevel);
  display.println("cm");
  
  display.print("Pressure: ");
  display.print(pressure);
  display.println(" Pa");
  
  display.display();
 
  // empty tank if water level exceeds 50.0 cm or pressure
  // is less than 100 kPa
  if (waterLevel > 50.0 || pressure < 100000.0) {
    openValve(); //call open valve function
    delay(30000);//wait arbitrary amount of time for water to drain
    closeValve();//call close valve function
  }
  
  // ESP8266 code
  // print the string when a newline arrives:
 if (stringComplete) {
   while (f < 100)
   { if (inputString.substring(f) == "id")
     {
       id = true;
       break;
     } f++;
   }
   if (id == true)
   {
     x = inputString.charAt(f + 4);
   }
   if (x == '4')
   { f = 0;
     while (f < 100)
     { if (inputString.substring(f) == "number")
       { f += 9;
         for (int i = 0; i < 3; i++)
         { if (inputString.charAt(f + i) == '"') i = 3;
           else buff += inputString.charAt(f + i);
         }
         buf = buff.toInt();
         analogWrite(9, buf);
         break;
       }
       f++;
     }
   }
   // clear the string:
   inputString = "";
   stringComplete = false;
 }
  
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

//Opens valve by writing solenoid pin to high.
//Prints message to OLED display.
void openValve() {
  digitalWrite(solenoidPin, HIGH);
  //Serial.println("Valve opened");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Valve opened");
  display.display();
}

//Closes valve by writing solenoid pin to low.
//Prints message to OLED display.
void closeValve() {
  digitalWrite(solenoidPin, LOW);
  //Serial.println("Valve closed");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Valve closed");
  display.display();
}

// ESP8266 Code
void serialEvent() {
 while (Serial.available()) {
   // get the new byte:
   char inChar = (char)Serial.read();
   // add it to the inputString:
   inputString += inChar;
   // if the incoming character is a newline, set a flag so the main loop can
   // do something about it:
   if (inChar == '\n') {
     stringComplete = true;
   }
 }
}
