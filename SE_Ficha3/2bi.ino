#include <Servo.h>

Servo myservo;

int potpin = 0;
int val;
int pos;
int del;

void setup()
{
  Serial.begin(9600);
  myservo.attach(9);
}

void loop()
{
  for (pos = 0; pos <= 180; pos += 1) {
    val = analogRead(potpin);
    del = map(val, 0, 1023, 16, 2);
    if (del != 16) {
        myservo.write(pos);
        Serial.println(del);
        delay(del);
    }
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    val = analogRead(potpin);
    del = map(val, 0, 1023, 16, 2);
    if (del != 16) {
        myservo.write(pos);
        Serial.println(del);
        delay(del);
    }
  }
}
