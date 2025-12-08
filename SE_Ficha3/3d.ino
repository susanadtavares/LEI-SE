const int xPin = A0;
const int yPin = A1;
const int zPin = A2;

float xVal, yVal, zVal;
float pitch, roll;
float pitchRef = 0.0;
float rollRef = 0.0;

const float VREF = 3.3;
const int TOLERANCIA = 5;

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Sistema de Estabilizacao");
  delay(3000);

  long somaPitch = 0;
  long somaRoll = 0;
  const int nLeituras = 200;

  for (int i = 0; i < nLeituras; i++) {
    float x = analogRead(xPin);
    float y = analogRead(yPin);
    float z = analogRead(zPin);
    x = (x - 512) * (VREF / 1023.0);
    y = (y - 512) * (VREF / 1023.0);
    z = (z - 512) * (VREF / 1023.0);
    float p = atan(x / sqrt(y * y + z * z)) * (180.0 / PI);
    float r = atan(y / sqrt(x * x + z * z)) * (180.0 / PI);
    somaPitch += p;
    somaRoll += r;
    delay(10);
  }

  pitchRef = somaPitch / nLeituras;
  rollRef  = somaRoll / nLeituras;

  Serial.println("Calibracao concluida!");
  Serial.print("Pitch de referencia: ");
  Serial.print(pitchRef, 2);
  Serial.print("°, Roll de referencia: ");
  Serial.print(rollRef, 2);
  Serial.println("°");
  delay(2000);
}

void loop() {
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  zVal = analogRead(zPin);

  xVal = (xVal - 512) * (VREF / 1023.0);
  yVal = (yVal - 512) * (VREF / 1023.0);
  zVal = (zVal - 512) * (VREF / 1023.0);

  pitch = atan(xVal / sqrt(yVal * yVal + zVal * zVal)) * (180.0 / PI);
  roll  = atan(yVal / sqrt(xVal * xVal + zVal * zVal)) * (180.0 / PI);

  pitch -= pitchRef;
  roll  -= rollRef;

  Serial.print("Pitch: ");
  Serial.print(pitch, 1);
  Serial.print("°, Roll: ");
  Serial.print(roll, 1);
  Serial.println("°");

  if (pitch > TOLERANCIA)
    Serial.println("Inclinado para frente → Girar para trás!");
  else if (pitch < -TOLERANCIA)
    Serial.println("Inclinado para trás → Girar para frente!");

  if (roll > TOLERANCIA)
    Serial.println("Inclinado para a esquerda → Girar para a direita!");
  else if (roll < -TOLERANCIA)
    Serial.println("Inclinado para a direita → Girar para a esquerda!");

  delay(500);
}
