int ADDRESS_BUS[16] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};
int CLOCK_PIN = 8;

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);

  for (int i = 0; i < 16; i++) {
    pinMode(ADDRESS_BUS[i], INPUT);
  }

  Serial.begin(300);
}

void loop() {
  // put your main code here, to run repeatedly:
  log();
  tick();
}

void tick() {
  digitalWrite(CLOCK_PIN, HIGH);
  delay(500);
  digitalWrite(CLOCK_PIN, LOW);
  delayMicroseconds(500);
  Serial.println("CLOCK DONE");
}

void log() {
  Serial.print("ADDRESS: ");

  for (int i = 0; i < 16; i++ ) {
    int bitStatus = digitalRead(ADDRESS_BUS[i]) ? 1 : 0;
    Serial.print(bitStatus);
  }
  
  Serial.println();
}
