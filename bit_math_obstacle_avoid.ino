/*
 * Obstacle avoidance example
 * by Andrew Kramer
 * 8/3/2015
 * 
 * Uses 3 ultrasonic sensors to determine 
 * if nearest obstacle is too close.
 * Outlines 8 possible cases for 
 * positions of obstacles.
 */

#include <NewPing.h>

#define RH_PWM 6 // PWM pin for right hand motor
#define RH_DIR1 9 // direction control for right hand motor
                  // BIN1 pin on motor controller
#define RH_DIR2 8 // direction control for right hand motor
                    // BIN2 pin on motor controller

#define LH_PWM 11 // PWM pin for left hand motor
#define LH_DIR1 13 // direction control for right hand motor
                     // AIN1 pin on motor controller
#define LH_DIR2 12 // direction control for left hand motor
                     // AIN2 pin on motor controller
                     
#define DEFAULT_SPEED 30 // default PWM level for the motors
#define TURN_DISTANCE 20 // distance at which the bot will turn
#define MAX_DISTANCE 200 // max range of sonar sensors
#define NUM_SONAR 3 // number of sonar sensors
#define NUM_CASES 8 // number of reaction cases

NewPing sonar[NUM_SONAR] = { // array of sonar sensor objects
  NewPing(A2, A2, MAX_DISTANCE), // right
  NewPing(A1, A1, MAX_DISTANCE), // front
  NewPing(A0, A0, MAX_DISTANCE) // left
};

/* list of cases
    B0000000  0: no obstacles
    B0000001  1: obstacle to the right
    B0000010  2: obstacle in front
    B0000011  3: obstacles front and right
    B0000100  4: obstacle to the left
    B0000101  5: obstacles left and right
    B0000110  6: obstacles front and left
    B0000111  7: obstacles front, left, and right
*/

byte thisCase = 0;

void setup() {
  for (int pin = 6; pin <= 13; pin++) {
    pinMode(pin, OUTPUT); // set pins 3 through 9 to OUTPUT
  }
  Serial.begin(9600);
}

void loop() {
  updateSensor();
  switch (thisCase) {
    // no obstacles
    case B00000000:
      straightForward();
      break;
    // obstacle to the right
    case B00000001:
      Serial.println("Turn left");
      turnLeft(30);
      break;
    // obstacle in front
    case B00000010:
      turnLeft(90);
      break;
    // obstacles front and right
    case B00000011:
      turnLeft(90);
      break;
    // obstacle to the left
    case B00000100:
      Serial.println("Turn right");
      turnRight(30);
      break;
    // obstacles left and right
    case B00000101:
      turnLeft(180);
      break;
    // obstacles front and left
    case B00000110:
      turnRight(90);
      break;
    // obstacles front, left, and right
    case B00000111:
      turnLeft(180);
      break;
  }
  delay(100); 
}

void updateSensor() {
    thisCase = 0;
    for (int i = 0; i < NUM_SONAR; i++) {
        int distance = sonar[i].ping_cm();
        if (distance == 0) 
            distance = MAX_DISTANCE;
        if (distance < TURN_DISTANCE)
            thisCase |= (1 << i);
    }
}

void setLeftForward() {
  digitalWrite(LH_DIR1, HIGH);
  digitalWrite(LH_DIR2, LOW);
}

void setRightForward() {
  digitalWrite(RH_DIR1, HIGH);
  digitalWrite(RH_DIR2, LOW);
}

void setBothForward() {
  setLeftForward();
  setRightForward();
}

void setLeftBackward() {
  digitalWrite(LH_DIR1, LOW);
  digitalWrite(LH_DIR2, HIGH);
}

void setRightBackward() {
  digitalWrite(RH_DIR1, LOW);
  digitalWrite(RH_DIR2, HIGH);
}

void setBothBackward() {
  setRightBackward();
  setLeftBackward();
}

void setLeftSpeed(int speed) {
  analogWrite(LH_PWM, speed);
}

void setRightSpeed(int speed) {
  analogWrite(RH_PWM, speed);
}

void setBothSpeeds(int speed) {
  setLeftSpeed(speed);
  setRightSpeed(speed);
}

// sets direction of both motors to forward and sets both speeds
// to default speed
void straightForward() {
  setBothForward();
  setBothSpeeds(DEFAULT_SPEED);
}

// makes a turn by stopping one motor
// accepts an int, 0 or 1 for left or right turn respectively
void turnLeft(int deg) {
  setBothSpeeds(0);
  delay(100);
  setLeftBackward(); // set left motor to run backward
  setBothSpeeds(DEFAULT_SPEED); // set speeds to 1/2 default
  delay(10 * deg); // allow time for the bot to turn
                   // turn time is approx 5ms per degree
  straightForward(); // resume driving forward at default speed
}

void turnRight(int deg) {
  setBothSpeeds(0);
  delay(100);
  setRightBackward(); // set right motor to run backward
  setBothSpeeds(DEFAULT_SPEED); // set speeds to 1/2 default
  delay(10 * deg); // allow time for the bot to turn
                      // turn time is approx 5ms per degree
  straightForward(); // resume driving forward at default speed
}


