#define trigPin 8
#define echoPin 9
#define ledVerde 6
#define ledVermelho 12

long duracao;
float distancia;

const byte interruptPin = 2;
volatile bool state = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP );
  attachInterrupt(digitalPinToInterrupt(interruptPin), cond, CHANGE);
}

void loop() {
  if (state) {
    Serial.println("Marcha atrás");
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duracao = pulseIn(echoPin, HIGH, 25000); // timeout de 25ms (~4m)

    distancia = (duracao * 0.0343) / 2; // cálculo da distância em cm
    Serial.print("distancia: ");
    Serial.println(distancia);
    // LED verde (intensidade inversa à distância)
    int brilhoVerde = map(constrain(distancia, 5, 50), 5, 50, 0, 255);
    analogWrite(ledVerde, 255 - brilhoVerde);

    // LED vermelho (pisca conforme aproximação)
    if (distancia > 30) {
      digitalWrite(ledVermelho, LOW);
      delay(500);
    } else if (distancia > 10 && distancia <= 15) {
      digitalWrite(ledVermelho, HIGH);
      delay(200);
      digitalWrite(ledVermelho, LOW);
      delay(200);
    } else if (distancia <= 10 && distancia > 5) {
      digitalWrite(ledVermelho, HIGH);
      delay(100);
      digitalWrite(ledVermelho, LOW);
      delay(100);
    } else if (distancia <= 2) {
      digitalWrite(ledVermelho, HIGH); 
    }
  } else {
    digitalWrite(ledVerde, HIGH);
    Serial.println("Em condução");
  }
}

void cond() {
  state = !state;
}
