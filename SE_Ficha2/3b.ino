const int MQ135_PIN = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando leitura do sensor MQ-135...");
  delay(2000);
}

void loop() {
  int sensorValue = analogRead(MQ135_PIN);

  Serial.print("Valor: ");
  Serial.println(sensorValue);

  delay(5000);
}
