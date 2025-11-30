int valorLdr = 0; 

void setup() {
  pinMode(10,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  valorLdr = analogRead(0);

  //se o valor lido for maior que 225, liga o led
  if (valorLdr >= 225) digitalWrite(10,HIGH);
  // senão, apaga o led
  else digitalWrite(10,LOW);

  Serial.println(valorLdr);
  delay(5000);
}
