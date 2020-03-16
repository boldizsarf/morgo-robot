/* Morgo Robot code */

/* Libs */
#include <Arduino.h>
#include <Servo.h>

/* Defines */

Servo front_right;
Servo front_left;
Servo rear_right;
Servo rear_left;

long duration1;
int distance1;

long duration2;
int distance2;

long duration3;
int distance3;

int frontObstacle;
int rightObstacle;
int leftObstacle;

/* Basic servo functions */

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

void moveForward2() {
  FLForward();
  delay(250);
  FRForward();
  delay(250);
  RLForward();
  delay(250);
  RRForward();
  delay(250);
  allServoTo90();
  delay(250);
}

void TurnRight() {
  FLForward();
  delay(250);
  RLForward();
  delay(250);
  FRBackward();
  delay(250);
  allServoTo90();
  delay(250);
}

void TurnLeft() {
  FRForward();
  delay(250);
  RRForward();
  delay(250);
  FLBackward();
  delay(250);
  allServoTo90();
  delay(250);
}

void moveBackward() {
  RRBackward();
  delay(250);
  RLBackward();
  delay(250);
  FRBackward();
  delay(250);
  FLBackward();
  delay(250);
  allServoTo90();
  delay(250);
}

/* Sounds */

void sysStartupSound() {
  tone(5, 329.63, 300);
  delay(100);
  tone(5, 311.13, 300);
  delay(100);
  tone(5, 329.63, 300);
  delay(100);
  tone(5,311.13, 300);
  delay(100);
  tone(5, 329.63, 300);
  delay(100);
  tone(5, 246.94, 300);
  delay(100);
  tone(5, 293.66,300);
  delay(100);
  tone(5, 261.63,300);
  delay(150);
  tone(5, 220, 900);
}

void sysReadySound() {
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

/* Obstacle sensors */

void checkObstacle() {
  /* Front */
    // Clears the trigPin
    digitalWrite(13, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(13, HIGH);
    delayMicroseconds(10);
    digitalWrite(13, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration1 = pulseIn(2, HIGH);
    // Calculating the distance
    distance1= duration1*0.034/2;
    // Set the int
    if (distance1 < 20 && distance1 > 10) {
      frontObstacle = 1;
    } else if (distance1 < 10) {
      frontObstacle = 2;
    } else {
      frontObstacle = 0;
    }

    /* Right */
      // Clears the trigPin
      digitalWrite(6, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(6, HIGH);
      delayMicroseconds(10);
      digitalWrite(6, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration2 = pulseIn(7, HIGH);
      // Calculating the distance
      distance2 = duration2*0.034/2;
      // Set the int
      if (distance2 < 20 && distance2 > 10) {
        rightObstacle = 1;
      } else if (distance2 < 10) {
        rightObstacle = 2;
      } else {
        rightObstacle = 0;
      }

      /* Left */
        // Clears the trigPin
        digitalWrite(8, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(8, HIGH);
        delayMicroseconds(10);
        digitalWrite(8, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        duration3 = pulseIn(12, HIGH);
        // Calculating the distance
        distance3 = duration3*0.034/2;
        // Set the int
        if (distance3 < 20 && distance3 > 10) {
          leftObstacle = 1;
        } else if (distance3 < 10) {
          leftObstacle = 2;
        } else {
          leftObstacle = 0;
        }
}

/* Setup */

void setup() {

  Serial.begin(9600);

  /* Startup sound */
  sysStartupSound();

  /* Setup the sensors */
  pinMode(13, OUTPUT); // Setup front sensor trig
  pinMode(2, INPUT);  // Setup front sensor echo

  pinMode(6, OUTPUT); // Setup right sensor trig
  pinMode(7, INPUT);  // Setup right sensor echo

  pinMode(8, OUTPUT); // Setup left sensor trig
  pinMode(12, INPUT);  // Setup left sensor echo

  /* Attach servos and set them to zero */
  attachServos();
  allServoToZero();
  delay(400);

  /* System is ready */
  sysReadySound();
  delay(1000);

  /* Start the situp process */
  sitUp();
  delay(1000);

  /* Ready for action */
  startMovingSound();
}

/* Loop */

void loop() {
  checkObstacle();
  switch (frontObstacle) {
    case 0:
      moveForward2();
      break;
    case 1:
      switch (rightObstacle) {
        case 0:
          TurnRight();
          break;
        case 1 || 2:
          switch (leftObstacle) {
            case 0:
              TurnLeft();
              break;
            case 1 || 2:
              moveBackward();
              break;
          }
          break;
      }
      break;
    case 2:
      moveBackward();
      break;
  }
}
