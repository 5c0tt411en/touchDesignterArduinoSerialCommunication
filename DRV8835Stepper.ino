#include <Stepper.h>

// 1回転(360度)するステップ数
#define STEPS 480

// 毎分の回転数(rpm)
int rpm = 60;
String s = "";
int inByte = 0, angle = 0, prev = 0, state = 1, stepNum = 0, dir = 1;

Stepper st00(STEPS, 8, 9, 10, 11);

void setup() {
  Serial.begin(9600);
  st00.setSpeed(rpm);
  pinMode(13, OUTPUT);
}

void loop() {
  inByte = Serial.read();
  if (isDigit(inByte)) {
    s += char(inByte);
  }
  if (char(inByte) == '\n') {
    Serial.print(s);
    angle = s.toInt();
//    Serial.println(angle - prev);
    s = "";
  }

  analogWrite(13, angle);

  if       (angle - prev < 0)  dir = -1;
  else if  (angle - prev == 0) dir = 0;
  else if  (angle - prev > 0)  dir = 1;
  prev = angle;

  st00.step(dir);
}
