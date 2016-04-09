// Single Motor Control example sketch
// by Andrew Kramer
// 5/28/2015

// makes the motor run at 1/2 power

#define PWMA 3 // PWM pin for right hand motor
#define AIN1 4 // direction control pin 1
               // AIN1 on the motor controller
#define AIN2 5 // direction control pin 2 
               // AIN2 pin on motor controller

void setup() {
  // set all pins to output
  for (int pin = 3; pin <= 5; pin++) {
    pinMode(pin, OUTPUT); // set pins 3 through 5 to OUTPUT
  }
  // set motor direction to forward 
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  // set the motor to run at 1/2 power
  analogWrite(PWMA, 128);
}

void loop() {
  // we're just making the motor run at a constant speed,
  // so there's nothing to do here
}
