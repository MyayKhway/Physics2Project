// Connect the circuit as follows.
// Connect to sensor
// 1 - Red wire : Sensor positive pole
// 2 - Blue wire : Sensor output
// 3 - Yellow wire : Sensor negative pole
// 4 - Omit : GND light

// Connect to Arduino board
//G - GND light
//A - Analog output in the example. with pin A0
//D - Digital output, in the example not used
//V - 5V power
void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int a0 = analogRead(A0);
  Serial.print((a0/1024.0)*5);
  Serial.println();
  delay(1000);
}
