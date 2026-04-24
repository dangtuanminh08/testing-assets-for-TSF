int IR_PIN = 2;
int MQ4Pin= A0;

volatile unsigned int counter = 0; 
unsigned long previousMs = 0;
unsigned int rpm = 0; 

float sensorResistance = 4.8;

void IRinterrupt() {
  counter++;
}

void setup() {
  pinMode(IR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IR_PIN), IRinterrupt, FALLING);
  Serial.begin(9600); 
}

void loop() {
  unsigned long currentMs = millis();

  if (currentMs - previousMs >= 1000) {
    noInterrupts();
    unsigned int pulses = counter;
    counter = 0;
    interrupts();

    rpm = (pulses/2)*60;
    previousMs = currentMs;
  }

  int sensorValue = analogRead(MQ4Pin);
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
  Serial.print(" | RPM: ");
  Serial.println(rpm);
}
