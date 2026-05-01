int MQ4_PIN= A0;
float sensorResistance = 6.93;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(mq4Pin);
  float voltage = sensorValue * (5.0/1023.0);

  float resistance = (5.0 - voltage) / voltage;
  float ratio = resistance/sensorResistance;

  float ppm = pow(10, (-0.39 * log10(ratio) + 1.41));

  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.print(" | Resistance (k ohms): ");
  Serial.print(resistance);
  Serial.print(" | Ratio : ");
  Serial.print(resistance/sensorResistance);
  Serial.print(" | PPM (methane): ");
  Serial.println(ppm);

}
