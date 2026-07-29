#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Verified microsecond limits for your specific MG995 and MG90S servos
#define USMIN  1000 // 0 degrees
#define USMAX  2200 // 180 degrees
#define NUM_SERVOS 6

void setup() {
  Serial.begin(9600);
  
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50); // Standard 50Hz update rate for analog servos

  Serial.println("5-Servo Robotic Arm Controller Ready!");
  Serial.println("Enter 6 angles separated by commas (e.g., 90,0,180,45,90) and press Enter:");
  
  // Home all servos to 0 degrees at startup safely
  for (int i = 0; i < NUM_SERVOS; i++) {
    pwm.writeMicroseconds(i, USMIN);
  }
}

void loop() {
  // Check if data is available in the Serial Monitor
  if (Serial.available() > 0) {
    int angles[NUM_SERVOS]; // Array to hold the 5 parsed angles
    
    // Read the 5 integers separated by commas
    for (int i = 0; i < NUM_SERVOS; i++) {
      angles[i] = Serial.parseInt(); 
    }
    
    // Clear out any trailing newline or carriage return characters
    while (Serial.available() > 0) {
      Serial.read();
    }

    Serial.print("Moving Servos to: ");
    for (int i = 0; i < NUM_SERVOS; i++) {
      // Constrain input to safe boundaries (0 to 180)
      angles[i] = constrain(angles[i], 0, 180);
      
      // Convert the angle (0-180) to exact microseconds (1000-2000)
      int targetUS = map(angles[i], 0, 180, USMIN, USMAX);
      
      // Send signal to the respective PCA9685 channel
      pwm.writeMicroseconds(i, targetUS);
      
      // Print confirmation to the serial monitor
      Serial.print(angles[i]);
      if (i < NUM_SERVOS - 1) Serial.print(", ");
    }
    Serial.println();
  }
}
