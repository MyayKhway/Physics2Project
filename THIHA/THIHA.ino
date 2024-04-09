#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 srituhobby = Adafruit_SSD1306(128, 64, &Wire); // OLED

#define sensor A0
#define led 9
#define Highpulse 540

int sX = 0;
int sY = 60;
int x = 0;
int Svalue;
int value;
int current_state;
int previous_state = 0;
long Stime = 0;
long Ltime = 0;
int count = 0;
int Bpm = 0;

void setup() {
  Serial.begin(9600);
  srituhobby.begin(SSD1306_SWITCHCAPVCC, 0x3C);// Address 0x3C for 128x32
  delay(1000);
  pinMode(led, OUTPUT);
  srituhobby.clearDisplay();
}

void loop() {
  Svalue = analogRead(sensor);
  current_state = currentstt(Svalue);
  if (current_state!=previous_state){
      if (current_state < previous_state){
        Serial.print("Pulse ");
        count++;
        Serial.println(count);
      }
    previous_state = current_state;
  }
  
  // if(current_state < previous_state){
  //   Serial.print("Pulse");
  // }
  Serial.println(Svalue);
  value = map(Svalue, 0, 1024, 0, 45);

  int y = 60 - value;

  if (x > 128) {
    x = 0;
    sX = 0;
    srituhobby.clearDisplay();
  }

  srituhobby.drawLine(sX, sY, x, y, WHITE);
  sX = x;
  sY = y;
  x ++;

  BPM();

  srituhobby.setCursor(0, 0);
  srituhobby.setTextSize(2);
  srituhobby.setTextColor(SSD1306_WHITE);
  srituhobby.print("BPM :");
  srituhobby.display();

}

void BPM() {

  if (Svalue > Highpulse) {
    Stime = millis() - Ltime;
    //count++;
    if (Stime / 1000 >= 60) {
      srituhobby.setCursor(60, 0);
      srituhobby.setTextSize(2);
      srituhobby.setTextColor(SSD1306_WHITE);
      srituhobby.print(count);
      srituhobby.print("   ");
      srituhobby.display();
      delay(5000);
      count = 0;
      previous_state = 0;
    }
  }
}
int currentstt(int x)
{
  if (Svalue >= 800) return 1;
  if (Svalue < 800) return 2;
}