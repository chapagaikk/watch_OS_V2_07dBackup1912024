#include <SPI.h>
#include <TFT_eSPI.h>  // Hardware-specific library
#include <ESP32Time.h>
#include "driver/gpio.h"
#include "esp_sleep.h"
#include <EEPROM.h>
//#include <QMC5883L.h>
#include <BH1750.h>  //BH1750 Library
#include "Free_Fonts.h"
#include "MAX30105.h"   // SparkFun librarry for MAX30102 sensor
#include "heartRate.h"
//#include "MAX30100_PulseOximeter.h"
//#include "heartRate.h"  // Heartrate measurement algorithm
#include "dial240.h"    //Image data
#include "fonts.h"
#include "images.h"
//#include <BluetoothSerial.h>
#include <EEPROM.h>
//#include <Wire.h>
#include <MPU6050_tockn.h>  // acelerometer and gyroscope sensor
#include <esp32-hal-touch.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define EEPROM_SIZE 25
#define FONT_SMALL NotoSansBold15
#define FONT_LARGE NotoSansBold36
#define TFT_GREY 0x5AEB
#define TFT_SKYBLUE 0x067D
#define color1 TFT_WHITE
#define color2 0x8410  //0x8410
#define color3 0x5ACB
#define color4 0x15B3
#define color5 0x00A3
#define colour6 0x0926
#define colour7 TFT_BLACK
#define Light_Green 0x07E8
#define background 0xB635
#define LCD_BACKLIGHT 4
#define TFTW 240          // screen width
#define TFTH 240          // screen height
#define TFTW2 (TFTW / 2)  // half screen width
#define TFTH2 (TFTH / 2)  // half screen height
#define TOUCH_PIN 2
#define NTP_OFFSET 21600        // In seconds
#define NTP_INTERVAL 60 * 1000  // In miliseconds
#define NTP_ADDRESS "1.asia.pool.ntp.org"

/////////////////////////////////////////////////////
/*Function Prototype Declarations Here*/
/////////////////////////////////////////////////////
void detectStep();
void ShortClick();
void LongPress();
void watchtask();
void timesettings();
void settings();
void HRApp();
//void CompassApp();
void watchfacedsp();
void handleTouch();
//void onBeatDetected();
float updateMovingAverage(float newValue);
void calculateThreshold();
void calibrateSensor();
void DisplayStep();
// WiFi credentials
//const char* ssid = "CST-ECE";
//const char* password = "CST@12345";
const char* ssid = "PBX-T";
const char* password = "Password@1234";
// Bluetooth Serial object
//BluetoothSerial SerialBT;
WiFiClient client;

/* ADXL345 global variables. */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // Replace with your desired I2C address
// Constants for adaptive thresholding
const float ThresholdMultiplier = 500; // Adjust this value as needed
const int WindowSize = 10; // Number of samples for calculating moving average
const int StepCompletionThreshold = 2; // Minimum readings below threshold to complete a step
// Variables for adaptive thresholding
float threshold = 0.0;
float accelerationWindow[WindowSize];
int currentIndex = 0;
int stepCount = 0;
int readingsBelowThreshold = 0;
float offsetX, offsetY, offsetZ;
float XVal, YVal, ZVal;
float ThresholdAccl;

// Define the EEPROM size
//#define EEPROM_SIZE 512

// Define the EEPROM address to store data
//#define DATA_ADDRESS 0

//BluetoothSerial SerialBT;
unsigned long previousMillis = 0;
const long interval = 10000;  // Interval in milliseconds (10 sec), to send the data from esp to other device using BT
int dataRead;


ESP32Time rtc(43200);   // RTC instance with offset in seconds

//BH1750 lightMeter;  //BH1750 Instance
//QMC5883L compass;
//MAX30105 particleSensor;  //MAX30102 instance

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
TFT_eSprite img = TFT_eSprite(&tft);
TFT_eSprite img1 = TFT_eSprite(&tft);
TFT_eSprite img2 = TFT_eSprite(&tft);

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;  // Saved H, M, S x & y multipliers
float sdeg = 0, mdeg = 0, hdeg = 0;
uint16_t osx = 120, osy = 140, omx = 120, omy = 140, ohx = 120, ohy = 140;  // Saved H, M, S x & y coords
uint16_t x0 = 0, x1 = 0, yy0 = 0, yy1 = 0;
uint32_t targetTime = 0;                       // for next 1 second timeout
static uint8_t conv2d(const char* p);          // Forward declaration needed for IDE 1.6.x
uint8_t hh = conv2d(__TIME__), mm = conv2d(__TIME__ + 3), ss = conv2d(__TIME__ + 6); // Get H, M, S from compile time
uint8_t t_hh = 0, t_mm = 0, t_dd = 0, t_mn = 0;  //
uint32_t t_yr = 0;
//uint8_t t_hh = 0, mm = 0, ss = 0;
unsigned long lastfacechange = 0;
unsigned long lastwake = 0;
unsigned long lastpressed = 0;
unsigned long lastvaluechange = 0;
bool initial = 1;
volatile int counter = 0;
float VALUE;
float lastValue = 0;
int lastsec = 0;
int pressstate = 0;
unsigned long lastDisplayUpdate = 0;

/*const byte RATE_SIZE = 4;  //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];     //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0;  //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;
bool beat = false;*/
bool detectingPulse = false; 

double rad = 0.01745;
float x[360];
float y[360];
bool facechange = false;
bool Screenchange = false;
float px[360];
float py[360];
float lx[360];
float ly[360];
int r = 104;
int ssx = 120;
int ssy = 140;
String cc[12] = { "45", "40", "35", "30", "25", "20", "15", "10", "05", "0", "55", "50" };
String days[] = { "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY" };
String days1[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };
int start[12];
int startP[60];
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;
int angle = 0;
bool onOff = 0;
bool debounce = 0;
int watchface = 0, Screen = 0, SubScreen = 0, Autoscreen, AutoBright, AutoscreenTime, Brigtnesslevel;
String h, m, s, d1, d2, m1, m2;
//volatile unsigned int TouchStartTime = 0;
volatile unsigned int TotalPressTime = 0;

int lastAngle = 0;
float circle = 100;
bool dir = 0;
int rAngle = 359;
volatile bool ClickDetected = false;
bool ShortClicked = false;
bool LongPressed = false;
int Touchthreshold = 40;

//Pulse Sensor Definations
/*#define REPORTING_PERIOD_MS 800
PulseOximeter pox;
uint32_t tsLastReport = 0;
float AverageBeat=0, AverageSPO2=0;
long beginCount=0;*/
MAX30105 particleSensor;
const byte RATE_SIZE = 3; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
float beatsPerMinute;
int beatAvg;
int AveragingTime = 0;

// This function is called from the interrupt when the signal on the PIN_INPUT has changed.
// do not use Serial in here.
void IRAM_ATTR touchInterruptHandler() { 
  ClickDetected = true; 
  if (TotalPressTime == 0){
    TotalPressTime = millis();
  }
}

/*void onBeatDetected()
{
  Serial.println("Beat!");
}*/

void setup(void) {
  Wire.begin();
  //Wire.setClock(100000 );
  Serial.begin(115200);
  //setting of the gyroscope
 // mpu6050.begin();
 // mpu6050.calcGyroOffsets(true);
  // Initialize EEPROM with the specified size
  //EEPROM.begin(EEPROM_SIZE);
  WiFi.mode(WIFI_STA);
  Serial.println(F("ESP32 Watch OS."));
  // Read and print the data stored in EEPROM
 // readData();
 // SerialBT.begin("ESP32_BT"); // Bluetooth device name

  gpio_hold_dis((gpio_num_t)LCD_BACKLIGHT);
  pinMode(LCD_BACKLIGHT, OUTPUT);
  digitalWrite(LCD_BACKLIGHT, LOW);

  EEPROM.begin(EEPROM_SIZE);
  EEPROM.writeInt(10, 0);
  EEPROM.commit();

  if (EEPROM.read(0) > 3) {   //first IF EEPROM.read(0) watchFace
    //Serial.println("first IF EEPROM read(0)>3");
    //Serial.println(EEPROM.read(0));

    EEPROM.write(0, 4);
    EEPROM.commit();
  }
  watchface = EEPROM.read(0);
  //Serial.println("Out first IF");
  //Serial.println(watchface);

  if (EEPROM.read(1) > 5) {  //secondIF read(1) (AutoScreen)
    Serial.println(F(EEPROM.read(1))); 
    
    EEPROM.write(1, 5);
    EEPROM.commit();
    //Serial.println("Sec IF EEPROM.read(1) Autoscreen");
    //Serial.println(EEPROM.read(1));
  }
  Autoscreen = EEPROM.read(1); 
  //Serial.println(" Autoscreen Out IF 2");
  //Serial.println(Autoscreen);

  if (EEPROM.read(2) > 5) { //3rd IF AutoBright
    Serial.print(F(EEPROM.read(2)));
    EEPROM.write(2, 5);
    EEPROM.commit();
    //Serial.println(" 3rd IF, AutoBright:");
    //Serial.print(EEPROM.read(2));
  }
  AutoBright = EEPROM.read(2);
  
  //rtc.setTime(ss, mm, hh, 17, 1, 2024);  // 17th Jan 2024 compile date
  configTime(NTP_OFFSET, 0, NTP_ADDRESS);
  struct tm timeinfo;
  if (getLocalTime(&timeinfo)){
    rtc.setTimeStruct(timeinfo); 
  }

  String yearString = String(timeinfo.tm_year + 1900); // Add 1900 to get the actual year // Convert the month to a string
  String monthString = String(timeinfo.tm_mon + 1); // Add 1 to get the actual month (0-11)  // Convert the day to a string
  String dayString = String(timeinfo.tm_mday); // Convert the hour to a string
  String hourString = String(timeinfo.tm_hour); // Convert the minute to a string
  String minuteString = String(timeinfo.tm_min); // Convert the second to a string
  String secondString = String(timeinfo.tm_sec); // Print the individual components
  Serial.print("Time: ");   Serial.print(yearString);   Serial.print("-");
  Serial.print(monthString);   Serial.print("-");   Serial.print(dayString);
  Serial.print(" ");   Serial.print(hourString);   Serial.print(":");
  Serial.print(minuteString);   Serial.print(":"); Serial.println(secondString);

  // Set the TFT display brightness
  //lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE);  //Init BH1750 library
  //Set a constant brightness value (adjust as needed)
  const int constantBrightness = 50;  // Set your desired constant brightness level

  analogWrite(LCD_BACKLIGHT, constantBrightness);

  if (AutoBright == 0) {
    unsigned int lv = 200;  //constrain(lightMeter.readLightLevel(), 50, 500);
    analogWrite(LCD_BACKLIGHT, lv / 2);
    } else {
    analogWrite(LCD_BACKLIGHT, AutoBright * 50);
  }

  tft.init();
  //Serial.println("TFT Init");

  tft.setRotation(0);
  //tft.setColorDepth(16);
  tft.setSwapBytes(true);
  tft.fillScreen(colour7);
  int xw = tft.width() / 2;  // xw, yh is middle of screen
  int yh = tft.height() / 2;
  tft.setPivot(xw, yh);  // Set pivot to middle of TFT screen

  img.setSwapBytes(true);
  img.createSprite(240, 240);
  img.setTextDatum(4);

  img1.createSprite(240, 70);
  img1.setSwapBytes(true);
  img1.setTextDatum(4);


  img2.createSprite(240, 70);
  img2.setSwapBytes(true);
  img2.setTextDatum(4);

  targetTime = millis() + 1000;
  facechange = true;
  Serial.println("TFT Init Done, Check LCD");
  
    // Initialize WiFi
  WiFi.begin(ssid, password);
  delay(2000);

 if (WiFi.status() != WL_CONNECTED) {
    //delay(2000);
    Serial.println(F("Connecting to WiFi..."));
  }
  
  else if (WiFi.status() == WL_CONNECTED){
    Serial.println(F("Connected to WiFi"));
    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
  }

  //timeClient.begin();

  // Initialize Bluetooth
  //SerialBT.begin("Clock Bluetooth");
  //Serial.println("Bluetooth initialized");

  //esp_sleep_enable_ext0_wakeup(GPIO_NUM_2, 1);  //1 = High, 0 = Low
  //esp_sleep_enable_ext0_wakeup(PIN_INPUT, 1);  //1 = High, 0 = Low
  // setup interrupt routine
  // when not registering to the interrupt the sketch also works when the tick is called frequently.
  //attachInterrupt(digitalPinToInterrupt(PIN_INPUT), checkTicks, CHANGE);
  
  //particleSensor.begin(Wire, I2C_SPEED_FAST);
  //particleSensor.setup();                     //Configure sensor with default settings
  //particleSensor.setPulseAmplitudeRed(0x0A);  //Turn Red LED to low to indicate sensor is running
  //particleSensor.setPulseAmplitudeIR(0xFF);   //Turn Red LED to low to indicate sensor is running
  //particleSensor.setPulseAmplitudeGreen(0);   //Turn off Green LED
  //particleSensor.shutDown();
  //Serial.println("Particle Sensor Begin");

  /*if (!pox.begin()) {
    Serial.println("Pulse Sensor Begin FAILED");
    delay(1000);
  } else {
    Serial.println("Pulse Sensor Begin Success");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
  */
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
  particleSensor.shutDown();

  //ADXL345 Setup;
  Serial.println(F("Accelerometer Test")); Serial.println(F(""));
  if (!accel.begin()) {  // Initialize accelerometer sensor
    Serial.println(F("Failed to initialize ADXL345 sensor!"));
    while (1);
  }
  // Set accelerometer range (optional)
  accel.setRange(ADXL345_RANGE_16_G);
  calibrateSensor();
  calculateThreshold();
  threshold = ThresholdAccl*ThresholdMultiplier;
  Serial.print("Threshold : "); Serial.print(threshold);
  Serial.println("ADXL Setup Complete");
  //compass.init();
  //compass.setSamplingRate(50);
  // Serial.println("Compass InitDone, Going to Main Loop");
  touchAttachInterrupt(TOUCH_PIN, touchInterruptHandler, Touchthreshold);
  esp_sleep_enable_touchpad_wakeup();

  lastwake = millis();
  Serial.println(F("Setup Complete"));

}
////////////////////////////////////////
/*********** MAIN LOOP ****************/
////////////////////////////////////////
void loop() {
  
  //pox.update();

  // Serial.println("I am back in Loop");
  if (ClickDetected && (touchRead(TOUCH_PIN) > Touchthreshold) && TotalPressTime > 0){
    handleTouch();
  }

  //  mpu6050.update();
  //  ax = mpu6050.getAccX();
  //  ay = mpu6050.getAccY();
  //  az = mpu6050.getAccZ();

  //  Serial.println("MPU Configured:");
  //  detectStep();

  // Data to be stored in EEPROM (integer value)
  //  int dataToStore = stepCount;

  // Store data in EEPROM
  //writeData(dataToStore);

  // Read and print the updated data from EEPROM
  //readData();

  // Wait for some time before looping
 //delay(10);

/*  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the current time
    previousMillis = currentMillis;

    // Send the footstep count to Serial Bluetooth Terminal
    SerialBT.print(" Footstep: ");
    SerialBT.println(dataRead);
  } */

  //button.tick();
  if (Screen < 5) {  //WatchFace=4, Autoscreen=5;, AutoBright = 5;
    //Serial.print("Screen:"); Serial.println(Screen);
    watchtask();
  }
}

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
/*
//for storing the data in EEPROM
void writeData(int data) {
  // Check if there is enough space in EEPROM to store the data
  if (DATA_ADDRESS + sizeof(data) <= EEPROM_SIZE) {
    // Write data to EEPROM
    EEPROM.put(DATA_ADDRESS, data);
    EEPROM.commit(); // Commit the changes to EEPROM
    Serial.println("Data written to EEPROM successfully!");
  } else {
    Serial.println("Not enough space in EEPROM to store data!");
  }
}
//for reading the data from EEPROM
void readData() {
  // Read and print data from EEPROM
  
  EEPROM.get(DATA_ADDRESS, dataRead);

  Serial.print("Data read from EEPROM: ");
  Serial.println(dataRead);
}
*/

void handleTouch() {
  unsigned long touchDuration = millis() - TotalPressTime;
  if (touchDuration > 50){
    if (touchDuration < 800){  //(touchRead(2) > 40) && 
      //Serial.println("Short Touch Detected");
      //Serial.printf("Touch T0 detected for %ld mSec\n", touchDuration);
      ShortClick();
      ClickDetected = false;
      TotalPressTime = 0;
    }
    //TouchStartTime = 0;
    else if ((touchDuration > 800) && (touchDuration < 2500)){ //(touchRead(2) > 40) && 
      //Serial.println("Long Touch Detected");
      //Serial.printf("Touch T0 detected for %ld mSec\n", touchDuration);
      LongPress();
      ClickDetected = false;
      TotalPressTime = 0;
    }
    
    else { 
      //Serial.println("Out of Range");
      //Serial.printf("Touch T0 detected for %ld mSec\n", touchDuration);
      // LongPress();
      ClickDetected = false;
      TotalPressTime = 0;
    }
  }
}
// Callback (registered below) fired when a pulse is detected

