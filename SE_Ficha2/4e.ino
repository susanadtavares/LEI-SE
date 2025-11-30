#include <LiquidCrystal.h>
#include "DHT.h"

// LCD
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

// DHT22
#define PINO_DHT 8
#define TIPO_DHT DHT22
DHT dht(PINO_DHT, TIPO_DHT);

#define PINO_LDR   A5
#define PINO_MQ135 A0

// LEDs para alerta
#define LED_LDR   6   // Luminosidade
#define LED_TEMP  7   // Temperatura
#define LED_HUM   9   // Humidade
#define LED_AR    10  // Qualidade do ar

// LIMITES
const int   LIMITES_LDR_POUCA_CLARIDADE = 200;  
const int   LIMITES_AR_MAU              = 400;  
const float LIMITES_TEMP_ALTA           = 28.0; 
const float LIMITES_TEMP_BAIXA          = 16.0; 
const float LIMITES_HUM_ALTA            = 70.0; 
const float LIMITES_HUM_BAIXA           = 30.0; 

// ----------------------------------------

void setup() {
  lcd.begin(16, 2);
  dht.begin();
  lcd.leftToRight();

  // LEDs
  pinMode(LED_LDR,  OUTPUT);
  pinMode(LED_TEMP, OUTPUT);
  pinMode(LED_HUM,  OUTPUT);
  pinMode(LED_AR,   OUTPUT);

  digitalWrite(LED_LDR,  LOW);
  digitalWrite(LED_TEMP, LOW);
  digitalWrite(LED_HUM,  LOW);
  digitalWrite(LED_AR,   LOW);

  mensagemInicial();
}

void loop() {
  // Mostrar 5x todos os sensores ao longo de ~20s (5 leituras x 4s)
  long   somaLdr  = 0;
  long   somaAr   = 0;
  double somaHum  = 0;
  double somaTemp = 0;

  for (int i = 0; i < 5; i++) {
    int   ldr   = analogRead(PINO_LDR);
    int   ar    = analogRead(PINO_MQ135);
    float hum   = dht.readHumidity();     
    float tempC = dht.readTemperature();  

    somaLdr  += ldr;
    somaAr   += ar;
    somaHum  += hum;
    somaTemp += tempC;

    lcd.setCursor(0, 0); lcd.print("Amostragem 20s ");
    lcd.setCursor(0, 1); lcd.print("Leitura "); lcd.print(i+1); lcd.print("/5   ");

    delay(4000); 
  }

  // Médias
  int   ldrMedio   = (int)((somaLdr / 5.0) + 0.5);
  int   arMedio    = (int)((somaAr  / 5.0) + 0.5);
  float humMedia   = (float)(somaHum  / 5.0);
  float tempMedia  = (float)(somaTemp / 5.0);

  // Atualiza LEDs de alerta (um por sensor)
  atualizaLEDs(ldrMedio, arMedio, humMedia, tempMedia);

  // Apresenta resultados 
  mostrarValor("Luminosidade:", ldrMedio);
  mostrarTemperatura(tempMedia);
  mostrarHumidade(humMedia);
  mostrarValor("Qualid. do Ar:", arMedio);

  // Mostra mensagens de alerta com scroll 
  mostrarAlertasComScroll(ldrMedio, arMedio, humMedia, tempMedia);

  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Nova amostragem");
  lcd.setCursor(0, 1); lcd.print("em breve...");
  delay(2000);
}

// Funções de apresentação

void mensagemInicial() {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print("Monitor Ambiente");
  lcd.setCursor(0, 1); lcd.print("C/ LEDs Alerta");
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

// Mostra uma mensagem com scroll
void mostraScroll(const char* linha1, const char* linha2, uint16_t pausaAntes=600, uint16_t pausaDepois=1200) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(linha1);
  lcd.setCursor(0, 1); lcd.print(linha2);
  delay(pausaAntes);

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

// LEDs de alerta 

void atualizaLEDs(int ldrMedio, int arMedio, float humMedia, float tempMedia) {
  // Luminosidade: pouca claridade -> alerta
  bool alertaLdr  = (ldrMedio < LIMIAR_LDR_POUCA_CLARIDADE);

  // Temperatura fora do intervalo confortável
  bool alertaTemp = (tempMedia >= LIMIAR_TEMP_ALTA) || (tempMedia <= LIMIAR_TEMP_BAIXA);

  // Humidade fora do intervalo confortável
  bool alertaHum  = (humMedia >= LIMIAR_HUM_ALTA) || (humMedia <= LIMIAR_HUM_BAIXA);

  // Qualidade do ar: valor alto (pior) -> alerta
  bool alertaAr   = (arMedio > LIMIAR_AR_MAU);

  digitalWrite(LED_LDR,  alertaLdr  ? HIGH : LOW);
  digitalWrite(LED_TEMP, alertaTemp ? HIGH : LOW);
  digitalWrite(LED_HUM,  alertaHum  ? HIGH : LOW);
  digitalWrite(LED_AR,   alertaAr   ? HIGH : LOW);
}

// Alertas com scroll

void mostrarAlertasComScroll(int ldrMedio, int arMedio, float humMedia, float tempMedia) {
  bool mostrouAlgum = false;

  if (tempMedia >= LIMIAR_TEMP_ALTA)  { mostraScroll("ALERTA:", "Temp. muito elevada"); mostrouAlgum = true; }
  else if (tempMedia <= LIMIAR_TEMP_BAIXA) { mostraScroll("ALERTA:", "Temperatura baixa"); mostrouAlgum = true; }

  if (humMedia >= LIMIAR_HUM_ALTA)  { mostraScroll("ALERTA:", "Humidade elevada"); mostrouAlgum = true; }
  else if (humMedia <= LIMIAR_HUM_BAIXA) { mostraScroll("ALERTA:", "Humidade baixa"); mostrouAlgum = true; }

  if (ldrMedio < LIMIAR_LDR_POUCA_CLARIDADE) { mostraScroll("ALERTA:", "Pouca claridade na sala"); mostrouAlgum = true; }

  if (arMedio > LIMIAR_AR_MAU) { mostraScroll("ALERTA:", "Deve abrir uma janela"); mostrouAlgum = true; }

  if (!mostrouAlgum) {
    mostraScroll("Condições OK", "Ambiente confortavel");
  }
}
