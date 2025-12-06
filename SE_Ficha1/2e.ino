int s = 3;
int o = 3;
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  while(s > 0){
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(300);
    Serial.print(".");
    s--;
  } 

  while(o > 0){
    digitalWrite(13, HIGH);
    delay(1500);
    digitalWrite(13, LOW);
    delay(300);
    Serial.print("_");
    o--;
    s = 3;
  }
}