/**
 * @file config.h
 * @brief Hardware Configuration & Servo Pulse Bounds for ranjax Robotic Hand
 * Pulse width alteratons advised for specific servo and based on the maunfacturer
 * Hardware Architecture:
 * - Controller: Arduino UNO / Nano (I2C interface)
 * - PWM Driver: Adafruit PCA9685 16-Channel 12-bit PWM Servo Driver
 * - Power System: Li-ion Battery Pack -> Buck Converter (5V-6V DC) -> PCA9685 V+ Rail
 * - Servos: 4x MG995 (Fingers 2-5), 1x MG90S (Thumb Pivot), 1x SG90 (Thumb Flexion)
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// ==========================================
// 1. I2C & PCA9685 SETTINGS
// ==========================================
#define PCA9685_I2C_ADDR   0x40  // Default I2C address for PCA9685
#define SERVO_FREQ         50    // Analog servos run at ~50 Hz

// ==========================================
// 2. PCA9685 CHANNEL MAPPINGS
// ==========================================
#define CH_THUMB_ROTATION  0    // MG90S - Opposition / Pivot
#define CH_THUMB_FLEXION   1    // SG90  - Digit Curling
#define CH_INDEX           2    // MG995 - Index Finger Flexion
#define CH_MIDDLE          3    // MG995 - Middle Finger Flexion
#define CH_RING            4    // MG995 - Ring Finger Flexion
#define CH_PINKY           5    // MG995 - Pinky Finger Flexion

// Total active servo count
#define NUM_SERVOS         6

// ==========================================
// 3. PWM PULSE WIDTH CALIBRATION (12-bit: 0 to 4095)
// ==========================================
// Standard 50Hz servos expect pulse lengths between ~150 (0°) and ~600 (180°)
// Adjust these values if your tendons bind or reach physical stops before 0°/180°.

#define USMIN  600   // Minimum pulse length in microseconds (~150 ticks at 12-bit)
#define USMAX  2400  // Maximum pulse length in microseconds (~600 ticks at 12-bit)

// Individual Digit Motion Boundaries (In Degrees: 0 to 180)
// Fine-tune these angles to prevent mechanical tendon over-tensioning

// Thumb Rotation (MG90S)
#define THUMB_ROT_OPEN    0     // Rest / Away from palm
#define THUMB_ROT_CLOSED  120   // Opposed across palm

// Thumb Flexion (SG90)
#define THUMB_FLEX_OPEN   0     // Fully extended
#define THUMB_FLEX_CLOSED 160   // Curled grip

// Index Finger (MG995)
#define INDEX_OPEN        0
#define INDEX_CLOSED      170

// Middle Finger (MG995)
#define MIDDLE_OPEN       0
#define MIDDLE_CLOSED     170

// Ring Finger (MG995)
#define RING_OPEN         0
#define RING_CLOSED       170

// Pinky Finger (MG995)
#define PINKY_OPEN        0
#define PINKY_CLOSED      170

// ==========================================
// 4. MOTION & TIMING PARAMETERS
// ==========================================
#define DEFAULT_SWEEP_DELAY  15   // Milliseconds delay between step angles for smooth movement
#define SERIAL_BAUD_RATE     115200

#endif // CONFIG_H
