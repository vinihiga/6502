int ADDRESS_BUS[16] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
int DATA_BUS[8] = {39, 41, 43, 45, 47, 49, 51, 53};
int CLOCK_PIN = 8;
int RW_PIN = 9;

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(RW_PIN, INPUT);
  pinMode(POWER_PIN, OUTPUT);

  for (int i = 0; i < 16; i++) {
    pinMode(ADDRESS_BUS[i], INPUT);
  }

  for (int j = 0; j < 8; j++) {
    pinMode(DATA_BUS[j], INPUT);
  }

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  log();
  tick();
}

void tick() {
  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(CLOCK_PIN, LOW);
}

void log() {
  // Reading Address Memory
  Serial.print("ADDRESS: ");
  for (int i = 15; i >= 0; i-- ) {
    int bitStatus = digitalRead(ADDRESS_BUS[i]) ? 1 : 0;
    Serial.print(bitStatus);
  }

  // Reading Data from that Memory Region
  Serial.print("     DATA: ");
  for (int j = 7; j >= 0; j-- ) {
    int bitStatus = digitalRead(DATA_BUS[j]) ? 1 : 0;
    Serial.print(bitStatus);
  }

  // Reading state of R/W pin
  Serial.print("     R/W Pin: ");
  Serial.print(digitalRead(RW_PIN) ? "READ" : "WRITING");
  
  Serial.println();
}
