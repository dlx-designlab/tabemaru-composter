//Logic: Turn for a set number of turns at a certain rpm at a certain direction
//Pause for a certain time
 //turn for a set number of turns at a certain rpm at a certain direction
 //Pause again for a certain time

#define dirPin 9
#define stepPin 6
#define stepsPerRevolution 400 // Steps per revolution for your stepper motor

// Parameters for the first motion
#define rpm1 10           // RPM for the first motion
#define revolutions1 5   // Number of turns for the first motion (can be fractional)
#define direction1 HIGH    // Direction for the first motion (HIGH = CW, LOW = CCW)


// First Pause Duration
#define pauseAfterFirst 1000 // Pause time after the first motion (milliseconds)


// Parameters for the second motion
#define rpm2 30           // RPM for the second motion
#define revolutions2 0.1   // Number of turns for the second motion (can be fractional)
#define direction2 LOW     // Direction for the second motion (HIGH = CW, LOW = CCW)

// Second Pause Duration
#define pauseAfterSecond 500 // Pause time after the second motion (milliseconds)

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop() {
  // First motion
  digitalWrite(dirPin, direction1);
  runMotor(revolutions1, rpm1);

  // Pause after the first motion
  delay(pauseAfterFirst);

  // Second motion
  digitalWrite(dirPin, direction2);
  runMotor(revolutions2, rpm2);

  // Pause after the second motion
  delay(pauseAfterSecond);

}

// Function to turn motor for a set number of revolutions at a given RPM
void runMotor(float numRevolutions, int rpm) {
  long stepDelay = (60L * 1000000L) / (stepsPerRevolution * rpm); // Delay per step in microseconds
  long totalSteps = numRevolutions * stepsPerRevolution;         // Total steps for given revolutions

  for (long i = 0; i < totalSteps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay / 2); // Half-step HIGH
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay / 2); // Half-step LOW
  }
}
