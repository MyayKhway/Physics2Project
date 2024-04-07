float pH_value, temp_value, pH_sum;
float temp_volt;
float Voltage;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(pH_value, INPUT); 
} 
 
void loop() 
{   pH_sum = 0;
    for (int i = 0; i < 5; i++) {
    pH_sum += analogRead(A0);
    delay(200); // Delay between readings (adjust for desired sample rate)
  }
  pH_value = pH_sum/5.0;
  Voltage = pH_value * (5.0 / 1023.0); 
  Serial.print("pH voltage is: ");
  Serial.println(Voltage); 
  delay(1000); 
}