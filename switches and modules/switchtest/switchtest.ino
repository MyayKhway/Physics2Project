void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
}

void loop() {
   if (digitalRead(2) == HIGH) {
       Serial.println("pH on");
   }
   if (digitalRead(3) == HIGH) {
       Serial.println("TDS on");
   }
   if (digitalRead(4) == HIGH) {
       Serial.println("Turb on");
   }
   delay(1000);
}
