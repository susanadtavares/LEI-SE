int leds[] = {2, 3, 4, 5, 6, 7};   // pinos dos LEDs
int numLeds = 6;

void setup() {
  Serial.begin(9600);

  // configurar LEDs como saída
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
  }

  randomSeed(analogRead(A0));  // melhor aleatoriedade
}

void acenderLeds(int n) {
  for (int i = 0; i < numLeds; i++) {
    if (i < n) {
      digitalWrite(leds[i], HIGH);
    } else {
      digitalWrite(leds[i], LOW);
    }
  }
}

void apagarTodos() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void loop() {

  for (int lancamento = 1; lancamento <= 10; lancamento++) {

    int resultado = random(1, 7);    // número entre 1 e 6
    Serial.print("Lançamento ");
    Serial.print(lancamento);
    Serial.print(": ");
    Serial.println(resultado);

    acenderLeds(resultado);          // acende LEDs equivalentes ao número
    delay(10000);                    // 10 segundos

    apagarTodos();                   // limpa antes do próximo lançamento
    delay(500);                      // pequena pausa
  }

  // Após os 10 lançamentos, o programa fica parado
  while (true);
}
