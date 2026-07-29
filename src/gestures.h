#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Verified microsecond limits for your MG995 and MG90S servos
#define USMIN  1000 // 0 degrees (Fingers completely straight/open)
#define USMAX  2000 // 180 degrees (Fingers completely curled/closed)
#define NUM_SERVOS 5

// Current positions array to keep track of where the servos are (for smooth transition)
int currentPositions[NUM_SERVOS] = {USMIN, USMIN, USMIN, USMIN, USMIN};

void setup() {
  Serial.begin(9600);
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50); // 50Hz for analog servos

  // Initialize the arm to the open position safely
  for (int i = 0; i < NUM_SERVOS; i++) {
    pwm.writeMicroseconds(i, USMIN);
  }

  Serial.println("Robotic Arm Gesture Controller Ready!");
  Serial.println("Available commands: open, fist, peace, point, wave");
}

void loop() {
  if (Serial.available() > 0) {
    // Read the incoming word as a string, trim whitespace/newlines
    String command = Serial.readStringUntil('\n');
    command.trim(); 
    command.toLowerCase(); // Convert to lowercase so typing "Fist" or "fist" both work

    if (command == "open") {
      Serial.println("Action: Opening Hand");
      // Target angles: All fingers open (0 degrees)
      int targets[] = {0, 0, 0, 0, 0};
      executeMovement(targets);
    } 
    else if (command == "fist") {
      Serial.println("Action: Clenching Fist");
      // Target angles: All fingers tightly curled (180 degrees)
      int targets[] = {180, 180, 180, 180, 180};
      executeMovement(targets);
    } 
    else if (command == "peace") {
      Serial.println("Action: Peace Sign");
      // Index (1) and Middle (2) open; Thumb, Ring, Pinky closed
      int targets[] = {180, 0, 0, 180, 180};
      executeMovement(targets);
    } 
    else if (command == "point") {
      Serial.println("Action: Pointing");
      // Index (1) open; All other fingers closed
      int targets[] = {180, 0, 180, 180, 180};
      executeMovement(targets);
    } 
    else if (command == "wave") {
      Serial.println("Action: Waving Hand");
      // Loop a wave sequence twice
      for(int w = 0; w < 2; w++) {
        int waveLeft[] = {0, 0, 180, 180, 180};
        executeMovement(waveLeft);
        delay(200);
        int waveRight[] = {180, 180, 0, 0, 0};
        executeMovement(waveRight);
        delay(200);
      }
      // Return to open
      int openHand[] = {0, 0, 0, 0, 0};
      executeMovement(openHand);
    }
    else if (command != "") {
      Serial.print("Unknown command: ");
      Serial.println(command);
      Serial.println("Try: open, fist, peace, point, wave");
    }
  }
}

// Function to smoothly interpolate from current positions to target positions
void executeMovement(int targetAngles[]) {
  int targetUS[NUM_SERVOS];
  
  // 1. Convert target angles to microsecond values
  for (int i = 0; i < NUM_SERVOS; i++) {
    targetUS[i] = map(targetAngles[i], 0, 180, USMIN, USMAX);
  }

  // 2. Incrementally move towards the target to prevent sudden mechanical jerks
  bool moving = true;
  int stepSize = 15; // Higher number = faster movement, Lower number = smoother movement

  while (moving) {
    moving = false;
    
    for (int i = 0; i < NUM_SERVOS; i++) {
      if (currentPositions[i] < targetUS[i]) {
        currentPositions[i] += stepSize;
        if (currentPositions[i] > targetUS[i]) currentPositions[i] = targetUS[i];
        moving = true;
      } 
      else if (currentPositions[i] > targetUS[i]) {
        currentPositions[i] -= stepSize;
        if (currentPositions[i] < targetUS[i]) currentPositions[i] = targetUS[i];
        moving = true;
      }
      
      // Write the updated step position to the servo
      pwm.writeMicroseconds(i, currentPositions[i]);
    }
    
    delay(10); // Tiny pause between steps for physical transition
  }
}
