#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClientSecure.h>
#include "TRIGGER_WIFI.h"               
#include "TRIGGER_GOOGLESHEETS.h"
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
const int AirValue = 790;   //you need to replace this value with Value_1
const int WaterValue = 390;  //you need to replace this value with Value_2
const int SensorPin = A0;
int soilMoistureValue = 0;
int soilmoisturepercent=0;

char column_name_in_sheets[][7] = {"value1"};                        
String Sheets_GAS_ID = "AKfycbysUwja3-CeKQ9EUq21A1D4uEG8dRlvW8JfsyhR9YtuAPbGpeTOHcqxvEryDG-MbdOgMQ";                                         
int No_of_Parameters = 1;
 
void setup() 
{
  Serial.begin(9600);
  while (!Serial);
  WIFI_Connect("Galaxy M31","0plmnko9");                                                     /*Provide you Wi-Fi SSID and password to connect to Wi-Fi*/
  Google_Sheets_Init(column_name_in_sheets, Sheets_GAS_ID, No_of_Parameters );
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
}
void loop() 
{
soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent > 100)
{
  Serial.println("100 %");
  
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(20,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Moisture");
  
  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("100 %");
  display.display();
  
  delay(250);
  display.clearDisplay();
}
else if(soilmoisturepercent <0)
{
  Serial.println("0 %");
  
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(20,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Moisture");
  
  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("0 %");
  display.display();
 
  delay(250);
  display.clearDisplay();
}
else if(soilmoisturepercent >=0 && soilmoisturepercent <= 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  float a = soilmoisturepercent;
Data_to_Sheets(No_of_Parameters,a);
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(20,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Moisture");
  
  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent);
  display.setCursor(70,40);
  display.setTextSize(3);
  display.println(" %");
  display.display();
 
  delay(250);
  display.clearDisplay();
  Serial.println();
  delay(1000);
}  
}
