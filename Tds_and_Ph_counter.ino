#include <EEPROM.h>
#include "GravityTDS.h"
#include <LiquidCrystal_I2C.h>
#include "Ph.h"
#define TdsSensorPin A1
#define PhPin A0
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 

float temperature = 25,tdsValue = 0;
const int adcResolution=1024;

LiquidCrystal_I2C lcd(0x27, 16, 2);
GravityTDS gravityTds;
Ph ph(PhPin,adcResolution);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
    Serial.begin(9600);
    lcd.init();
    lcd.begin(16, 2);
    lcd.backlight();
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(adcResolution);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization
    sensors.begin(); 
}

void loop()
{
    sensors.requestTemperatures();
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(sensors.getTempCByIndex(0));  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value
    Serial.print(tdsValue,0);
    Serial.println("ppm");
    lcd.setCursor(0, 0);
    lcd.print("pH   : ");
    lcd.print(ph.counterMean());
    lcd.setCursor(1, 0);
    lcd.print("TDS : "); 
    lcd.print(tdsValue,0);
    delay(1000);
}
