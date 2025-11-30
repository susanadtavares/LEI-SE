#include <LiquidCrystal.h>
#include "DHT.h"

// LCD 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// DHT22
#define PINO_DHT 8
#define TIPO_DHT DHT22
DHT dht(PINO_DHT, TIPO_DHT);

#define PINO_LDR   A5
#define PINO_MQ135 A0

// Limites 
const int   LIMITE_LDR_POUCA_CLARIDADE = 200;  // 0 a 1023 (quanto menor, mais escuro)
const int   LIMITE_AR_MAU              = 400;  // Valor bruto MQ135 (0 a 1023)
const float LIMITE_TEMP_ALTA           = 28.0; // Em graus celsius
const float LIMITE_TEMP_BAIXA          = 16.0; // Em graus celsius
const float LIMITE_HUM_ALTA            = 70.0; // Em percentagem
const float LIMITE_HUM_BAIXA           = 30.0; // Em percentagem

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  lcd.leftToRight();              
  mensagemInicial();
}

void loop() {
  // Mostrar 5x todos os sensores ao longo de ~20s (5 leituras x 4s)
  long somaLdr = 0;
  long somaAr  = 0;
  double somaHum = 0;
  double somaTemp = 0;

  for (int i = 0; i < 5; i++) {
    int   ldr   = analogRead(PINO_LDR);
    int   ar    = analogRead(PINO_MQ135);
    float hum   = dht.readHumidity();     
    float tempC = dht.readTemperature();  /

    somaLdr  += ldr;
    somaAr   += ar;
    somaHum  += hum;
    somaTemp += tempC;

    
    lcd.setCursor(0, 1);
    lcd.print("Amostragem ");
    lcd.print(i + 1);
    lcd.print("/5   ");

    delay(4000); 
  }

  // Calcular médias
  int   ldrMedio   = (int)round(somaLdr / 5.0);
  int   arMedio    = (int)round(somaAr  / 5.0);
  float humMedia   = (float)(somaHum  / 5.0);
  float tempMedia  = (float)(somaTemp / 5.0);

  // Apresentar resultados no LCD 
  mostrarValor("Luminosidade:", ldrMedio);       // valor bruto 0..1023
  mostrarTemperatura(tempMedia);                 // com símbolo de grau
  mostrarHumidade(humMedia);                     // com %
  mostrarValor("Qualid. do Ar:", arMedio);       // bruto 0..1023

  mostrarAlertasComScroll(ldrMedio, arMedio, humMedia, tempMedia);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("A iniciar nova");
  lcd.setCursor(0, 1); lcd.print("amostragem...");
  delay(2000);
}

// Funções para apresentar 

void mensagemInicial() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Monitor Ambiente");
  lcd.setCursor(0, 1); lcd.print("Amostragem 20s");
  delay(1500);
}

void mostrarValor(const char* titulo, int valor) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(titulo);
  lcd.setCursor(0, 1); lcd.print(valor);
  delay(3000);
}

void mostrarTemperatura(float tempC) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Temperatura:");
  lcd.setCursor(0, 1);
  lcd.print(tempC, 1);
  lcd.print((char)223); 
  lcd.print("C");
  delay(3000);
}

void mostrarHumidade(float hum) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Humidade:");
  lcd.setCursor(0, 1);
  lcd.print(hum, 1);
  lcd.print("%");
  delay(3000);
}

// Mostra uma mensagem longa com scroll para caber no LCD
void mostraScroll(const char* linha1, const char* linha2, uint16_t pausaAntes=600, uint16_t pausaDepois=1200) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(linha1);
  lcd.setCursor(0, 1); lcd.print(linha2);

  delay(pausaAntes);

  // 16 colunas do LCD + alguns passos extra consoante o tamanho da linha2
  for (int i = 0; i < 18; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }

  delay(pausaDepois);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(linha1);
  lcd.setCursor(0, 1); lcd.print(linha2);
  delay(800);
}

void mostrarAlertasComScroll(int ldrMedio, int arMedio, float humMedia, float tempMedia) {
  bool mostrouAlgum = false;

  // Temperatura
  if (tempMedia >= LIMIAR_TEMP_ALTA) {
    mostraScroll("ALERTA:", "Temp. muito elevada");
    mostrouAlgum = true;
  } else if (tempMedia <= LIMIAR_TEMP_BAIXA) {
    mostraScroll("ALERTA:", "Temperatura baixa");
    mostrouAlgum = true;
  }

  // Humidade
  if (humMedia >= LIMIAR_HUM_ALTA) {
    mostraScroll("ALERTA:", "Humidade elevada");
    mostrouAlgum = true;
  } else if (humMedia <= LIMIAR_HUM_BAIXA) {
    mostraScroll("ALERTA:", "Humidade baixa");
    mostrouAlgum = true;
  }

  // Luminosidade (LDR baixo = escuro)
  if (ldrMedio < LIMIAR_LDR_POUCA_CLARIDADE) {
    mostraScroll("ALERTA:", "Pouca claridade na sala");
    mostrouAlgum = true;
  }

  // Qualidade do Ar (valor alto -> pior ar)
  if (arMedio > LIMIAR_AR_MAU) {
    mostraScroll("ALERTA:", "Deve abrir uma janela");
    mostrouAlgum = true;
  }

  if (!mostrouAlgum) {
    mostraScroll("Condições OK");
  }
}
