#include <Servo.h>

Servo myservo;

int potpin = 0;
int val;
int pos;
int del;

int currDel = 16;

void setup()
{
  myservo.attach(9);
}

void loop()
{
  for (pos = 0; pos <= 180; pos += 1) {
    val = analogRead(potpin);
    del = map(val, 0, 1023, 16, 2);

    if (currDel < del) currDel++;
    else if (currDel > del) currDel--;

    if (currDel != 16) {
      myservo.write(pos);
      delay(currDel);
    } else {
      pos--;
      delay(5);
    }
  }

  for (pos = 180; pos >= 0; pos -= 1) {
    val = analogRead(potpin);
    del = map(val, 0, 1023, 16, 2);

    if (currDel < del) currDel++;
    else if (currDel > del) currDel--;

    if (currDel != 16) {
      myservo.write(pos);
      delay(currDel);
    } else {
      pos++;
      delay(5);
    }
  }
}
