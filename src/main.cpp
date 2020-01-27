#include <Arduino.h>
#include <Servo.h>

Servo front_right;
Servo front_left;
Servo rear_right;
Servo rear_left;

void attachServos() {
  front_right.attach(3);
  front_left.attach(10);
  rear_right.attach(11);
  rear_left.attach(9);
}

void allServoToZero() {
  front_right.write(0);
  front_left.write(0);
  rear_right.write(0);
  rear_left.write(0);
}

void allServoTo90(/* arguments */) {
  front_right.write(90);
  front_left.write(90);
  rear_right.write(90);
  rear_left.write(90);
}

void sitUp() {
  int pos = 0;
  for (pos = 0; pos <= 90; pos += 1) {
    front_right.write(pos);
    front_left.write(pos);
    rear_right.write(pos);
    rear_left.write(pos);
    delay(15);
  }
  delay(1000);
}

/* Move servo legs forward */

void FRForward() {
  front_right.write(130);
}

void RRForward() {
  rear_right.write(130);
}

void FLForward() {
  front_left.write(50);
}

void RLForward() {
  rear_left.write(50);
}

/* Move servo legs backward */

void FRBackward() {
  front_right.write(50);
}

void RRBackward() {
  rear_right.write(50);
}

void FLBackward() {
  front_left.write(130);
}

void RLBackward() {
  rear_left.write(130);
}

/* Move SIDE servo legs forward */

void rightForward() {
  FRForward();
  RRForward();
}

void leftForward() {
  FLForward();
  RLForward();
}

/* Move SIDE servo legs backward */

void rightBackward() {
  FRBackward();
  RRBackward();
}

void leftBackward() {
  FLBackward();
  RLBackward();
}

/* Movement */

void moveForward() {
  rightForward();
  delay(250);
  leftForward();
  delay(250);
  rightBackward();
  leftBackward();
  delay(250);
}

/* Sounds */

void sysStartupSound() {
  tone(5, 1000);
  delay(1000);
  noTone(5);
}

void servoReadySound() {
  tone(5, 2000);
  delay(250);
  noTone(5);
  delay(250);
  tone(5, 2000);
  delay(250);
  noTone(5);
}

void startMovingSound() {
  tone(5, 3000);
  delay(150);
  noTone(5);
  delay(150);
  tone(5, 3000);
  delay(150);
  noTone(5);
  delay(150);
  tone(5, 3000);
  delay(150);
  noTone(5);
}

void setup() {

  sysStartupSound();

  attachServos();
  allServoToZero();

  servoReadySound();

  delay(3000);
  sitUp();
  delay(1000);

  startMovingSound();
}

void loop() {
  moveForward();
}
