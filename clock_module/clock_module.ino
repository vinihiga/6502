int ADDRESS_BUS[16] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
int DATA_BUS[8] = {3, 4, 5, 6, 7, 8, 9, 10};
int CLOCK_PIN = 2;
int RW_PIN = 11;

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(RW_PIN, INPUT);

  for (int i = 0; i < 16; i++) {
    pinMode(ADDRESS_BUS[i], INPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(DATA_BUS[i], INPUT);
  }

  Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  log();
  tick();
}

void log() {
  char output[15];
  unsigned int address = 0;
  unsigned int data = 0;

  // Reading Address Bus
  Serial.print("ADDRESS: ");
  for (int i = 15; i >= 0; i-- ) {
    int bitStatus = digitalRead(ADDRESS_BUS[i]) ? 1 : 0;
    Serial.print(bitStatus);
    address = (address << 1) + bitStatus;
  }

  Serial.print("\t");

  // Reading Data Bus
  Serial.print("DATA: ");
  for (int i = 7; i >= 0; i-- ) {
    int bitStatus = digitalRead(DATA_BUS[i]) ? 1 : 0;
    Serial.print(bitStatus);
    data = (data << 1) + bitStatus;
  }

  sprintf(output, "\t %04x \t %c \t %02x", address, digitalRead(RW_PIN) ? 'r' : 'W', data);
  Serial.println(output);
}

void tick() {
  delay(500);
  digitalWrite(CLOCK_PIN, HIGH);
  delay(500);
  digitalWrite(CLOCK_PIN, LOW);
}