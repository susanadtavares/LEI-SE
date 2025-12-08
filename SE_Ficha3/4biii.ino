const int TRIG = 9;
const int ECHO = 8;

long readMicroseconds() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  return pulseIn(ECHO, HIGH, 30000UL); // timeout ~30ms (~5m)
}

float readCm() {
  // média simples de 3 leituras
  long us1 = readMicroseconds();
  long us2 = readMicroseconds();
  long us3 = readMicroseconds();
  long us = (us1 + us2 + us3) / 3;
  // velocidade som ~ 340 m/s → 29.1 us por cm ida-e-volta
  float cm = us / 58.0; 
  return cm;
}

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  float cm = readCm();
  // limita a um intervalo útil (ex.: 5..80 cm)
  if (cm >= 5 && cm <= 80) {
    Serial.println((int)cm);
  }
  delay(30); // ~33 Hz
}

