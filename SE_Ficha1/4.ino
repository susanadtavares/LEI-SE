int ledsA[3] = {2, 3, 4};  // LEDs do Jogador A
int ledsB[3] = {5, 6, 7};  // LEDs do Jogador B

void setup() {
  Serial.begin(9600);
  
  // Configurar todos os LEDs como saída
  for (int i = 0; i < 3; i++) {
    pinMode(ledsA[i], OUTPUT);
    pinMode(ledsB[i], OUTPUT);
  }
  
  randomSeed(analogRead(A0)); // melhor aleatoriedade
}

void apagarTodos() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledsA[i], LOW);
    digitalWrite(ledsB[i], LOW);
  }
}

// Piscar todos os LEDs 2 vezes no fim de cada ronda
void piscarFimDeRonda() {
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      digitalWrite(ledsA[j], HIGH);
      digitalWrite(ledsB[j], HIGH);
    }
    delay(300);
    
    for (int j = 0; j < 3; j++) {
      digitalWrite(ledsA[j], LOW);
      digitalWrite(ledsB[j], LOW);
    }
    delay(300);
  }
}

void loop() {

  // Simular 5 corridas
  for (int corrida = 1; corrida <= 5; corrida++) {

    Serial.print("Corrida nº ");
    Serial.println(corrida);

    apagarTodos();

    int posA = 0;
    int posB = 0;

    // Continua até um jogador chegar aos 3 LEDs
    while (posA < 3 && posB < 3) {

      int vencedor = random(1, 3); // 1 ou 2

      if (vencedor == 1) {
        digitalWrite(ledsA[posA], HIGH);
        posA++;
        Serial.println("Jogador A ganhou a ronda!");
      } 
      else {
        digitalWrite(ledsB[posB], HIGH);
        posB++;
        Serial.println("Jogador B ganhou a ronda!");
      }

      delay(5000); // duração da ronda
      piscarFimDeRonda();
    }

    if (posA == 3) {
      Serial.println(">>> Jogador A venceu a corrida!");
    } else {
      Serial.println(">>> Jogador B venceu a corrida!");
    }

    delay(2000);  // pausa entre corridas
  }

  // Todas as corridas terminaram
  Serial.println("Todas as 5 corridas foram concluídas.");
  while (true); // parar o programa
}
