int time = 5000;
int timeFinal = 500;
int reps = 4; 

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  while(time >= 500){
    Serial.println(time);
    digitalWrite(13, HIGH);
    delay(time);

    time = time - timeFinal;
    digitalWrite(13, LOW);
    delay(time);

    while (time == 500 && reps > 0){
          Serial.println(time);
      digitalWrite(13, HIGH);
      delay(timeFinal);
      digitalWrite(13, LOW);
      delay(timeFinal);
      reps = reps - 1;
    }

  }
}