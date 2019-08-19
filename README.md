# Rain-Barrel-Project

## Motivation

Storm runoff adversely affects water quality; surface pollution, trash, and topsoil run into bodies of water. As a result, 
submerged aquatic wildlife such as grasses, oysters, fish, and crabs are killed. Runoff has become a problem in urban and suburban 
areas as well due to impermeable pavement and the development of wetland areas. Impermeable pavement makes flash floods from 
torrential rains worse, and houses become damaged by flooded basements.

One possible solution to this problem, at least on an individual house scale, is the use of rain barrels. These devices can be 
used to delay the flow of water. They collect rainwater from roof downspouts and store it. This stored water can then be used to 
water gardens and plants through the hose, located at the bottom of the barrel. We decided to take this concept one step further 
and creating a supplementary device that turns ordinary rain barrels into Smart Rain Barrels by automating the process by which 
the rain barrels stores and releases water.


## How it Works
Our device consists of a Sonar sensor that we will place at the top of the rain barrel that will measure the water level. 
If the Sonar sensor detects the water level above the halfway point (50 centimeters), then the water will flow through the 
solenoid valve. If the water level is below the halfway point, then the solenoid valve will remain closed. Next, there will be a 
pressure sensor that will measure the air pressure and if the pressure is less than 100 Kilopascals, then it will most likely rain, 
which will lead the solenoid valve to open and water will flow out. There will also be a button just in-case if the user wants to 
manually allow water to flow out of the solenoid valve.

The Arduino is also connected to a server via the ESP8266 which in turn is conencted to your Google Home. So, using Google 
Assistant, one allow the water to flow out.

## Materials Used

Arduino Uno

Adafruit BMP388 Pressure Sensor

Adafruit DHT11 Humidity Sensor

ESP8266

Plastic Water Solenoid Valve -9V -½” Nominal

Sonar HC-SR04

OLED 128x64 1inch mono SSD1306

Darlington Transistor Array ULN2803A

Rain Barrel

Jumper Wires

Button

## How to Run

Download all the necessary libries in the Libraries Folder. Then download the Arduino script, the ESP8266 code, and upload 
them to Arduino board. Then set up the ESP8266 server and connect it to the Google Home. And now you can control the Rain Barrel 
with your Google Assistant!

## Helpful Links

[Speak to Arduino and Control It with Google Assistant](https://create.arduino.cc/projecthub/electropeak/speak-to-arduino-and-control-it-with-google-assistant-3791ee)
