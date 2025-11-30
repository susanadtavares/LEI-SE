int ldrPin = A5;       
int ledVerde = 9;      
int ledVermelho = 10;  

int passo = 0;// Contador que indica em que passo da password estamos

// Password: 0 - escuro, 0 - escuro, 1 - claro, 0 - escuro
int password[4] = {0, 0, 1, 0}; 

// Array onde vamos guardar os valores lidos pelo LDR
int input[4];

void setup() {
  pinMode(ledVerde, OUTPUT);      
  pinMode(ledVermelho, OUTPUT);   
  Serial.begin(9600);             
}

void loop() {

  // Se passaram mais de 10 segundos -> falha (acende LED vermelho)
  if (millis() > 10000) {
    digitalWrite(10, HIGH);
    while(1);
  }
  
  // A cada 1.5 segundos faz uma leitura do LDR, até completar 4 passos
  if (passo < 4 && millis() > (passo + 1) * 1500) {
      int valorLDR = analogRead(ldrPin);   
    if (valorLDR >= 170) input[passo] = 0;
    else input[passo] = 1;
    
    Serial.println(input[passo]);
    passo++;
  }
  
  // Quando já foram lidos os 4 passos -> verifica a password
  if (passo == 4) {
    for(int i = 0; i < 4; i++) {
      if (input[i] != password[i]) {
          digitalWrite(ledVermelho, HIGH);
        while(1);
      } 
    }
    digitalWrite(ledVerde, HIGH);
    while(1);
  }
  
}
