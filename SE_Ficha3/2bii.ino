#include <Servo.h>

Servo myservo;

int potpin = 0;
int val;
int pos;
int del;
int velocidades[] = {15, 8, 2};

void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
}

void loop()
{
  for (pos = 0; pos <= 180; pos += 1) {
    val = analogRead(potpin);
      del = map(val, 0, 1023, 1, 4);
    Serial.println(del);
    switch(del) {
      case 1:
          break;
      case 2:
          myservo.write(pos);
          delay(velocidades[0]);
          break;
      case 3:
          myservo.write(pos);
          delay(velocidades[1]);
          break;
      case 4:
          myservo.write(pos);
          delay(velocidades[2]);
          break;
    }
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    val = analogRead(potpin);
      del = map(val, 0, 1023, 1, 4);
    Serial.println(del);
    switch(del) {
      case 1:
          break;
      case 2:
          myservo.write(pos);
          delay(velocidades[0]);
          break;
      case 3:
          myservo.write(pos);
          delay(velocidades[1]);
          break;
      case 4:
          myservo.write(pos);
          delay(velocidades[2]);
          break;
    }
  }
}
