#include <LiquidCrystal.h>
#include "DHT.h"

// LCD 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensor DHT22
#define PIN_DHT 8
#define TIPO_DHT DHT22
DHT dht(PIN_DHT, TIPO_DHT);

#define PIN_LDR   A5
#define PIN_MQ135 A0

int sensorAtual = 0;

void setup() {
  lcd.begin(16, 2);
  dht.begin();
}

void loop() {
  int valorLdr = analogRead(PIN_LDR);
  int valorAr  = analogRead(PIN_MQ135);
  float humidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  lcd.clear();

  switch (sensorAtual) {
    case 0: // Luminosidade
      lcd.setCursor(0, 0);
      lcd.print("Luminosidade:");
      lcd.setCursor(0, 1);
      lcd.print(valorLdr);
      break;

    case 1: // Temperatura
      lcd.setCursor(0, 0);
      lcd.print("Temperatura:");
      lcd.setCursor(0, 1);
      lcd.print(temperatura, 1); 
      lcd.print((char)223);
      lcd.print("C");
      break;

    case 2: // Humidade
      lcd.setCursor(0, 0);
      lcd.print("Humidade:");
      lcd.setCursor(0, 1);
      lcd.print(humidade, 1);
      lcd.print("%");
      break;

    case 3: // Qualidade do Ar
      lcd.setCursor(0, 0);
      lcd.print("Qualid. do Ar:");
      lcd.setCursor(0, 1);
      lcd.print(valorAr);  
      break;
  }

  delay(5000);  
  lcd.clear();
  delay(1000);  

  sensorAtual++;
  if (sensorAtual > 3) sensorAtual = 0;
}
