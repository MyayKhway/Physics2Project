#include <EEPROM.h>
#include "GravityTDS.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#define TdsSensorPin A0
#define TurbiditySensorPin  A1
#define pHSensorPin A2
GravityTDS gravityTds;
LiquidCrystal_I2C lcd(0x27, 16, 2);

float temperature = 24;

uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};

void setup()
{
    Serial.begin(9600);
    Serial.println("setup done.");
    // initialize TDS library
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC
    gravityTds.begin();
    pinMode(2, INPUT_PULLUP); // for TDS sensor
    pinMode(3, INPUT_PULLUP); // for pH sensor  
    pinMode(4, INPUT_PULLUP); // for turbidity sensor
    pinMode(5, INPUT_PULLUP);
    lcd.init();
    lcd.createChar(0, heart);
    lcd.clear();
}

void loop(){
    bool finished = false;
    int pHVal, tdsVal, turbVal = -1;
    double turbVolt, pHVolt;
    Serial.println("Loop started.");
    while(1) {
        if (finished == true) {
            break;
        }
        else {
            if (digitalRead(2) == HIGH and digitalRead(3) == LOW and digitalRead(4) == LOW and digitalRead(5) == LOW) {
                // read TDS
                double tdsSum = 0.0;
                gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
                for (int i = 0; i < 10; i++) {
                    gravityTds.update();  //sample and calculate 
                    tdsSum += gravityTds.getTdsValue();  // then get the value
                    delay(30);
                }
                tdsVal = tdsSum/10;
                Serial.print("TDS:");
                Serial.println(tdsVal);
                delay(1500);
                }
            else if (digitalRead(2) == LOW and digitalRead(3) == HIGH and digitalRead(4) == LOW and digitalRead(5) == LOW) {
                // measure pH
                int pHsum = 0;
                for (int i = 0; i < 20; i++) {
                    pHsum += analogRead(pHSensorPin);
                    delay(30);
                }
                pHVolt = ((pHsum/20.0)/1024)*5.0;
                pHVal = 21.787- (5.8065*pHVolt);
                Serial.print("pH:");
                Serial.println(pHVal);
                delay(1500);
            }
            else if (digitalRead(2) == LOW and digitalRead(3) == LOW and digitalRead(4) == HIGH and digitalRead(5) == LOW) {
                // measure turbidity
                int turbsum = 0;
                for (int i = 0; i < 20; i++) {
                  turbsum += analogRead(TurbiditySensorPin);
                  delay(30);
                }
                turbVolt = ((turbsum/20.0)/1024)*5.0;

                if (turbVolt > 3.27) turbVal = 0;
                else turbVal = (-3037*log(turbVolt))+3599;
                Serial.print("Turbidity:");
                Serial.println(turbVal);
                delay(1500);
            }
            else if (digitalRead(2) == LOW and digitalRead(3) == LOW and digitalRead(4) == LOW and digitalRead(5) == HIGH) {
                if (tdsVal != -1 and turbVal != -1 and pHVal != -1) {
                  Serial.println(pHVal);
                  Serial.println(turbVal);
                  Serial.println(tdsVal);
                  finished = true;
                  lcd.backlight();
                  lcd.clear();
                  lcd.setCursor(1,0);
                  lcd.print("TDS");
                  lcd.setCursor(0,1);
                  lcd.print(tdsVal);
                  lcd.setCursor(6, 0);
                  lcd.print("CTBD");
                  lcd.setCursor(6, 1);
                  lcd.print(turbVal);
                  lcd.setCursor(13, 0);
                  lcd.print("pH");
                  lcd.setCursor(12,1);
                  lcd.print(pHVal);
                  delay(9000);
                }
            }
        }
    }
}
