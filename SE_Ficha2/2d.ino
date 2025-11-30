#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define PINAZUL 9
#define PINVERDE 10
#define PINVERMELHO 11

void setup() {
  pinMode (PINAZUL, OUTPUT);
  pinMode (PINVERDE, OUTPUT);
  pinMode (PINVERMELHO, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (h >= 20 && h < 60 ) {
     digitalWrite(PINVERMELHO, LOW);
    digitalWrite(PINAZUL, HIGH); 
    digitalWrite(PINVERDE, LOW);
  }
  if (h >= 60 && h < 70) {
     digitalWrite(PINVERMELHO, LOW);
    digitalWrite(PINAZUL, HIGH); 
    digitalWrite(PINVERDE, HIGH);
  }
  if (h >= 70) {
    digitalWrite(PINVERMELHO, HIGH);
    digitalWrite(PINAZUL, HIGH); 
    digitalWrite(PINVERDE, HIGH);
  } 
  if (h < 20) {
    digitalWrite(PINAZUL, LOW);
    digitalWrite(PINVERDE, LOW);
    digitalWrite(PINVERMELHO, LOW);
  }
      

  Serial.print("Humidade: "); Serial.println(h);
  Serial.print("Temperatura: "); Serial.println(t);
  delay(5000);
}
