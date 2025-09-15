const int chargePin = A0;
const int clockPin = A1;
const int resetPin = A2;
const int rwPin = A3;

const int dataPins[] = {52, 50, 48, 46, 44, 42, 40, 38};
const int addressPins[] = {36, 34, 32, 30, 28, 26, 24, 22, A7, A8, A9, A10, A11, A12, A13, A14, A15};

int clockCycle = 0;
const int MEM_SIZE = 4096;
byte memory[MEM_SIZE];

void setup() {
  Serial.begin(9600);
  initializeMemory();
  
  pinMode(chargePin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(resetPin, INPUT);
  pinMode(rwPin, INPUT);

  Serial.println("Iniciando CPU");
  digitalWrite(chargePin, HIGH); // Liga o IC
}

void loop() {
  delay(500);
  digitalWrite(clockPin, HIGH);
  onClock();

  delay(500);
  digitalWrite(clockPin, LOW);
  onClock();
}

void onClock() {
  if (clockCycle < 2) {
    clockCycle += 1;
    return;
  } else if (clockCycle == 2) {
    Serial.println("Tempo inicial de 2 clocks ultrapassado. Iniciando leitura de bus address e data.");
    digitalWrite(resetPin, HIGH); // Permite o push button "triggar" o RESET
    clockCycle += 1;
    return;
  }

  if (memory[0x0200] == 0x02) {
    Serial.println("--- Execução Finalizada ---");
    Serial.print("Resultado da soma (1+1) no endereço 0x0200: 0x");
    Serial.println(memory[0x0200], HEX);
    while(true); // Para o programa
  }

  handleRw();
}

void handleRw() {
  byte dataValue = 0;
  unsigned long addressValue = 0;
  int rwStatus = digitalRead(rwPin);
  
  // Configura os pinos de endereço como ENTRADA para ler o endereço
  for (int i = 0; i < 16; i++) {
    pinMode(addressPins[i], INPUT);
    if (digitalRead(addressPins[i]) == HIGH) {
      addressValue |= (1UL << i);
    }
  }

  // Se for uma operação de LEITURA (rwPin == HIGH)
  if (rwStatus == HIGH) {
    for (int i = 0; i < 8; i++) {
      pinMode(dataPins[i], OUTPUT);
    }
    
    // Fornece o byte de dados da memória ou do vetor de reset
    if (addressValue == 0xFFFC) {
      dataValue = 0x00;
    } else if (addressValue == 0xFFFD) {
      dataValue = 0x01;
    } else if (addressValue < MEM_SIZE) {
      dataValue = memory[addressValue];
    } else {
      dataValue = 0xEA; // No-operation (NOP) para endereços inválidos
    }
    
    for (int i = 0; i < 8; i++) {
      digitalWrite(dataPins[i], (dataValue >> i) & 0x01);
    }
    
    Serial.print("[READ] | Address: 0x");
    Serial.print(addressValue, HEX);
    Serial.print(" | Data: 0x");
    Serial.println(dataValue, HEX);
    
  } else { // Se for uma operação de ESCRITA (rwPin == LOW)
    // Configura os pinos de dados como ENTRADA para receber dados do 6502
    for (int i = 0; i < 8; i++) {
      pinMode(dataPins[i], INPUT);
    }
    
    // Lê o valor do barramento de dados
    for (int i = 0; i < 8; i++) {
      if (digitalRead(dataPins[i]) == HIGH) {
        dataValue |= (1 << i);
      }
    }
    
    // Armazena o valor na RAM simulada
    if (addressValue < MEM_SIZE) {
      memory[addressValue] = dataValue;
    }
    
    Serial.print("[WRITE] | Address: 0x");
    Serial.print(addressValue, HEX);
    Serial.print(" | Data: 0x");
    Serial.println(dataValue, HEX);
  }
}

void initializeMemory() {
  // Carregue o programa 1 + 1 no endereço 0x0100
  memory[0x0100] = 0xA9; // LDA #$01
  memory[0x0101] = 0x01;
  memory[0x0102] = 0x18; // CLC
  memory[0x0103] = 0x69; // ADC #$01
  memory[0x0104] = 0x01;
  memory[0x0105] = 0x8D; // STA $0200
  memory[0x0106] = 0x00; // Endereço de destino (byte baixo)
  memory[0x0107] = 0x02; // Endereço de destino (byte alto)
  memory[0x0108] = 0x00; // BRK
}