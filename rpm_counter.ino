int IR_PIN = 2;
volatile unsigned int counter = 0; 
unsigned long previousMs = 0;
unsigned int rpm = 0;

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

    Serial.print("RPM: ");
    Serial.println(rpm);
  }
}
