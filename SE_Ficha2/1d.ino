int ldrPin = A5;
int ledPin = 10;
void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int valorLDR = analogRead(ldrPin);
  
  // Converte o valor lido para a escala do PWM (0–255)
  int intensidadeLED = map(valorLDR, 0, 1023, 0, 255);
  
  // Ajusta o brilho do LED
  analogWrite(ledPin, intensidadeLED);

  Serial.println(valorLDR);
  
  delay(10);
}
