//TODO: display on the LCD
#include <EEPROM.h>
#include "GravityTDS.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#define TdsSensorPin A0
#define pHSensorPin A2
#define TurbiditySensorPin  A1
GravityTDS gravityTds;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperature = 26,tdsValue = 0;
double pHval, turb_val;


void setup()
{
    Serial.begin(9600);
    // initialize TDS library
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC
    gravityTds.begin();
    pinMode(pHval, INPUT); 
    pinMode(turb_val, INPUT);
    pinMode(2, OUTPUT); // for TDS sensor
    pinMode(3, OUTPUT); // for pH sensor  
    pinMode(4, OUTPUT); // for turbidity sensor
    lcd.init();
    lcd.clear();
    lcd.noBacklight(); //initialization
}

void loop()
{  
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    // measure TDS
    // TODO: turn on the module
    digitalWrite(2, HIGH);
    delay(500);
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate 
    tdsValue = gravityTds.getTdsValue();  // then get the value
    //TODO print on LCD
    //turn off the module
    digitalWrite(2, LOW);

    // measure pH
    //TODO turn on the module
    digitalWrite(3, HIGH);
    delay(500);
    int pHsum = 0;
    double pH_final;
    for (int i = 0; i < 5; i++) {
      pHsum += analogRead(pHSensorPin);
      delay(50);
    }
    pHval = ((pHsum/5.0)/1024)*5.0;
    pH_final = 21.787- (5.8065*pHval);
    //TODO print on LCD
    // turn off the module
    digitalWrite(3, LOW);
    
    // measure Turbidity
    // TODO: turn on the module
    digitalWrite(4, HIGH);
    delay(500);
    int turbsum = 0;
    for (int i = 0; i < 5; i++) {
      turbsum += analogRead(TurbiditySensorPin);
      delay(50);
    }
    turb_val = ((turbsum/5.0)/1024)*5.0;
    double turb_final;
    if (turb_val > 3.27) turb_final = 0;
    else turb_final = (-3037*log(turb_val))+3599;
    delay(500);

    Serial.print("Turbidity:");
    Serial.println(analogRead(A1));
    Serial.print("pH:");
    Serial.println(analogRead(A2));
    Serial.print("TDS:");
    Serial.println(analogRead(A3));
}
