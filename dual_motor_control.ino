// Dual Motor Control example sketch
// by Andrew Kramer
// 5/28/2015

// makes motor A run at 1/4 power and
// motor B run at 1/8 power
// in a differential drive robot this would cause the robot to
// drive in a small circle

#define PWMA 6 // PWM pin for right hand motor
#define AIN1 9 // direction control pin 1 for right motor
               // AIN1 on the motor controller
#define AIN2 8 // direction control pin 2 for right motor
               // AIN2 pin on motor controller
#define PWMB 11 // PWM pin for left hand motor
#define BIN1 13 // direction control pin 1 for left motor
#define BIN2 12 // direction control pin 2 for left motor

void setup() {
  // set all pins to output
  for (int pin = 3; pin <= 5; pin++) {
    pinMode(pin, OUTPUT); // set pins 3 through 5 to OUTPUT
  }
  for (int pin = 7; pin <= 9; pin++) {
    pinMode(pin, OUTPUT); // set pins 7 through 9 to OUTPUT
  }
  // set both motors to forward 
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  // set right motor to run at 1/2 power
  analogWrite(PWMA, 32);
  // set left motor to run at 1/8 power 
  analogWrite(PWMB, 16);
}

void loop() {
  // we're just making the motors run at constant speed,
  // so there's nothing to do here
}
