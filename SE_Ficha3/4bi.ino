const int POT_PIN = A0;
const int BTN_PIN = 2;

void setup() {
  pinMode(BTN_PIN, INPUT_PULLUP);
  Serial.begin(19200);
}

void loop() {
  int pot = analogRead(POT_PIN);
  int btn = digitalRead(BTN_PIN) == LOW ? 1 : 0;
  Serial.print(pot);
  Serial.print(' ');
  Serial.println(btn);
  delay(10);
}
