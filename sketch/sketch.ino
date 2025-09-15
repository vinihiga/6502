const int chargePin = A0;
const int clockPin = 2;
const int resetPin = A1;
// const int debugPin = 53;

const int addressPins[] = {52, 50, 48, 46, 44, 42, 40, 38};
const int dataPins[] = {36, 34, 32, 30, 28, 26, 24, 22};

void setup() {
  Serial.begin(9600);
  
  pinMode(chargePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  // pinMode(debugPin, INPUT);

  for (int i = 0; i < 8; i++) {
    pinMode(addressPins[i], INPUT);
  }

  for (int i = 0; i < 8; i++) {
    pinMode(dataPins[i], INPUT);
  }

  digitalWrite(chargePin, HIGH); // Liga o IC
  digitalWrite(resetPin, LOW);   // Ativa o reset
  delay(100);                   // Espera um momento para o reset ser reconhecido
  digitalWrite(resetPin, HIGH);  // Desativa o reset, liberando o processador
}

void loop() {
  digitalWrite(clockPin, HIGH);
  handleClock();
  delay(500);

  digitalWrite(clockPin, LOW);
  delay(500);
  // int isDebugPressed = (digitalRead(debugPin) == HIGH);
  // Serial.println(isDebugPressed);
}

void handleClock() {
  byte dataValue = 0;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(dataPins[i]) == HIGH) {
      dataValue |= (1 << i);
    }
  }

  byte addressValue = 0;
  for (int i = 0; i < 8; i++) {
    if (digitalRead(addressPins[i]) == HIGH) {
      addressValue |= (1 << i);
    }
  }

  Serial.print("Address: ");
  Serial.print(addressValue, HEX);
  Serial.print(" | Data: ");
  Serial.println(dataValue, HEX);
}