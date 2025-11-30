int valorLdr = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  valorLdr = analogRead(0);

  Serial.println(valorLdr);
  delay(5000);
}
