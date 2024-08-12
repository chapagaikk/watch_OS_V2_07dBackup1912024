# ESP32WatchJuly2024

Update all the Changes made in the codes and Libraries requirement including pin configurations in this file. 

We ll use this as reference when we make connections and run program next time. 

Controller: ESP32 Wroom 32D
Note: In order to get the SPI pins of ESP32, use the sketch below and check in the serial monitor.
//Find the default SPI pins for your board
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);  
}
void loop() {}

Pins: 
1.	Vcc – Vcc 3.3V
2.	GND – GND
3.	DIN – GPIO 23 (MOSI)
4.	CLK – GPIO18 
5.	CS – GPIO15
6.	DC – GPIO2
7.	RST – GPIO4
8.	BL – Connected to 3.3V

Change in the Config file:
-	The user setup file is located in: ..\Documents\Arduino\libraries\TFT_eSPI
-	Donot change anything in User_Setup.h
-	The cange acan be made only in User_Setup_Select.h
-	Open the file: User_Setup_Select.h 
-	Comment any #defines after #ifndef USER_SETUP_LOADED
-	Uncomment: #include <User_Setups/Setup46_GC9A01_ESP32.h>  for 240x240 LCD GC9A01
-	Open the folder: ..\Documents\Arduino\libraries\TFT_eSPI\User_Setups
-	Open the Setup46_GC9A01_ESP32.h file and check for the Pin Configurations.
-	For the current case the Pins are as follow for ESP32 Wroom 32D with 240x240 LCD GC9A01
o	Din – GPIO15
o	CS – GPIO14
o	DC – GPIO26
o	RST – GPIO33
o	BL – GPIO19
9.	For other LCDs, similarly: 
a.	Open the file: User_Setup_Select.h 
b.	Comment any previous #defines after #ifndef USER_SETUP_LOADED
c.	Uncomment: #include <User_Setups/*.h>  based on the graphics driver and the TFT used.
d.	For 128x128 LCD with ST7735 chip the pin used are same as GCA above with ESP32
i.	Din – GPIO15
ii.	CS – GPIO14
iii.	DC – GPIO26
iv.	RST – GPIO33
v.	BL – GPIO19
10.	Open the Source Code ESPWatchxxx.ino using Arduino IDE. Compile the code for the ESPDevkit board after selecting the required port.
a.	Before compiling, the ESP library and board should have been installed in the Arduino IDE 
b.	Follow the steps in https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
11.	When compiling, there are multiple libraries required in the code.
a.	Primary Libraries required to install are:
i.	TFT_espi library #include <TFT_eSPI.h>
ii.	Adafruit Sensor Library
iii.	Adafruit ADXL345 library
iv.	EEPROM library if not already in ESP board library
v.	
12.	Upload the code on to the board.

