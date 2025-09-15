const int chargePin = A0;
const int clockPin = A1;
const int resetPin = A2;
const int debugPin = 53;

const int dataPins[] = {52, 50, 48, 46, 44, 42, 40, 38};
const int addressPins[] = {36, 34, 32, 30, 28, 26, 24, 22};

int clockCycle = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(chargePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(resetPin, INPUT);
  pinMode(debugPin, INPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(addressPins[i], INPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(dataPins[i], INPUT);
  }

  Serial.println("Iniciando CPU");
  digitalWrite(chargePin, HIGH); // Liga o IC
}

void loop() {
  delay(100);
  digitalWrite(clockPin, HIGH);

  delay(100);
  digitalWrite(clockPin, LOW);

  clockCycle += 1;

  if (clockCycle == 2) {
    Serial.println("Tempo inicial de 2 clocks ultrapassado. Iniciando leitura de bus address e data.");
    digitalWrite(resetPin, HIGH); // Permite o push button "triggar" o RESET
  } else if (clockCycle > 2) {
    handleClock();
  }
}

void handleClock() {
  byte dataValue = 0;
  byte addressValue = 0;

  for (int i = 0; i < 8; i++) {
    if (digitalRead(dataPins[i]) == HIGH) {
      dataValue |= (1 << i);
    }
  }

  for (int i = 0; i < 8; i++) {
    if (digitalRead(addressPins[i]) == HIGH) {
      addressValue |= (1 << i);
    }
  }

  Serial.print("Address: ");
  Serial.print(addressValue, HEX);
  Serial.print(" | Data: ");
  Serial.println(dataValue, HEX);

  int isDebugPressed = (digitalRead(debugPin) == HIGH);
  Serial.print("isResetPressed: ");
  Serial.println(isDebugPressed);
}