int ADDRESS_BUS[16] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // abre a porta serial a 9600 bps:
  
  pinMode(13, OUTPUT);

  for (int i = 0; i < 16; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  log();
  tick();
}

void tick() {
  digitalWrite(13, HIGH);
  delayMicroseconds(1); // Approximately 50% duty cycle @ 500KHz
  digitalWrite(13, LOW);
  delayMicroseconds(1);
}

void log() {
  Serial.print("ADDRESS: ");

  for (int i = 0; i < 16; i++ ) {
    int bitStatus = digitalRead(i);
    Serial.print(bitStatus);
  }
  
  Serial.println();
}
