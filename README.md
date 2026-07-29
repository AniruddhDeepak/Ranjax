<h1 style="font-size: 2.5em;"> 🤖 Ranjax</h1>

A 3D-printed, Arduino-controlled robotic hand built for multi-finger movement and gestures demonstration.

---

 ⚡ Quick Features

* 🖐️ 5-Digit Motion: Individual finger control powered by servo motors.
* 🎯 Custom Gestures: Simple commands for gestures like **Fist**, **Point**, **Peace**, and **Wave**.
* ⚙️ Hardware Protection: Pulse-width limits built into code to prevent mechanical binding or servo stall.
* 📦 Clean Code Structure: Separated files for main code, gesture definitions, and hardware setup.

---

 🛠️ **Components Needed**

| Component | Quantity | Notes |

| Microcontroller | 1 | Arduino UNO / Mega/ ESP32 |

| Servo Motors | 6 | Micro Servos (SG90,MG90S,MG995) |

| Power Supply | 2 | 3.7v Lithium-ion batteries for DC supply to the servos |

| 3D Printed Parts| 

| Other Hardware | 1 | DC-DC Buck converter, PCA9685(Only applicable if Arduino UNO is used and also preferred method than using Arduino Mega) |

| Fishing wire | 1 | 10m should be fine

| Elastic wire | 1 | 10m should be fine

|Lithium-Ion Battery Holder|1|Dual cell holder is recommended

---

⚠️ **Important**: Always power the servos using a dedicated external power supply with a **common ground** connected to the Arduino. Do not power multiple servos directly off the Arduino 5V pin!

---

*For more precise steps and components refer the link below*
https://www.instructables.com/3D-Printed-Robotic-Arm-2/

---
⚠️⚠️**Issues and the fix in the procedure present in above link** : 

The Thumb does not have a dedicated servo motor for closing and opening of the fingers of the thumb only.....although it does have an MG90S servo motor for to and fro motion of the thumb but connecting the fishing wire from the thumb fingers to an SG90 servo is advisable if you want the fingers of the thumb to move as well.
If the above fix is apllied to one's project then the servo count adds up to 6 i.e (4-MG995, 1-MG90S, 1-SG90S).

**Photos of the Robotic hand and the alterations is provided**

---

⚠️Component connections is provided in the folder src(Source Code)

---
## 📂 Project Layout

```text
ranjax/
├── README.md               # Project guide
├── LICENSE                 # MIT License
├── .gitignore              # Git clean-up filter
├── hardware/               # 3D printable STL files
├── src/                    # Source Code
│   ├── gestures.h          # Gesture angles & functions
│   └── config.h            # Pin definitions & servo limits
|   └── calibration.h       # Manual calibration code
├── Pictures
