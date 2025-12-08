const int xpin = A2;
const int ypin = A1;
const int zpin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("X: ");
  Serial.print(analogRead(xpin));
  Serial.print(" Y: ");
  Serial.print(analogRead(ypin));
  Serial.print(" Z: ");
  Serial.print(analogRead(zpin));
  Serial.print('\n');

  delay(500);
}
