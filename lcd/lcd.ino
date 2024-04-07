#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t testChar[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}; // filled block

void setup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(0, testChar); // Sends the custom char to lcd
}

void loop() {
  loading_animation(0,0);
  loading_animation(7,0);
  loading_animation(14,0);
  display_member_names();

}

void display_member_names() {
  lcd.clear();
  lcd.print("Khant Nyi Lynn");
  delay(2000);
  lcd.clear();
  lcd.print("Aung Htet Oo");
  delay(2000);
  lcd.clear();
  lcd.print("Phoo Pwint Khine");  
  delay(2000);
  lcd.clear();
  lcd.print("Kaung Htun Kywel");  
  delay(2000);
  lcd.clear();
  lcd.print("Htet2 Lwin Aung");  
  delay(2000);
  lcd.clear();
}

void loading_animation(int row, int col) {
  lcd.clear();
  lcd.setCursor(row, col);
  lcd.print((char)0);
  delay(250);
  lcd.clear();
  lcd.setCursor(row+1, col);
  lcd.print((char)0);
  delay(250);
  lcd.clear();
  lcd.setCursor(row+1, col+1);
  lcd.print((char)0);
  delay(250);
  lcd.clear();
  lcd.setCursor(row, col+1);
  lcd.print((char)0);
  delay(250);
}