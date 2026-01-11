# Headlight Swap: Halogen to Xenon (HID) with Leveling

This guide details the process of swapping stock Halogen headlights to stock Xenon (HID) headlights. While the physical installation is "Plug n Play" (the plugs match), two key features require modification to function correctly:

1.  **"Flash to Pass"**: The high beam flash when pulling the stalk.
2.  **Auto-leveling**: Without the suspension sensors, the headlights default to their lowest position, significantly reducing visibility.

---

## 1. Fix "Flash to Pass" Feature

**The Problem:** Pulling the turn signal handle halfway does not flash the high beams.

**The Solution:**
1.  Locate the headlamp plug coming from the car (7 cables).
2.  Identify **PIN 2** and **PIN 7** (Thin Black and White wires, located one below the other).
3.  Cut the wire for **PIN 7**.
4.  Take the wire coming from the **plug side** (NOT the car side) of Pin 7 and splice it into **PIN 2**.

The "Flash to Pass" feature should now work.

---

## 2. Manual Height Control (Arduino Emulation)

**The Problem:** Because the car lacks the auto-leveling suspension sensors, the Xenon headlights default to the lowest position. Even with manual adjustment screws, the throw is too short for safe driving.

**The Solution:** We can emulate the leveling sensor signal using an Arduino and a potentiometer to control the height manually from inside the cabin.

### Hardware Required
* Arduino Uno or ESP8266 (Tested with both)
* Mosfet (e.g., CEP83A3)
* Potentiometer (Volume knob from an old speaker or a generic B10K)

### Software
Download the code for your specific board from the repository:
[Download Source Code](https://github.com/Deat.../SAAB-Auto-leveling-sensor-arduino)

### Installation Steps

#### Step 1: Arduino Setup
Flash the code to your Arduino. Connect the Arduino, Mosfet, and Potentiometer according to the diagram below.

![Wiring Diagram](path/to/your/diagram_image.jpg)
*(Replace this path with your actual image file)*

#### Step 2: Car Connector Pinout
1.  In the car, pull out the original headlamp level adjuster button (the switch with 0–4 levels).
2.  Look at the back of the button to identify the pin numbers. We will use **Pin 3** and **Pin 10**.

| Pin | Function |
| :--- | :--- |
| **Pin 3** | Minus / Ground (-) |
| **Pin 9** | Plus / Power (+) |
| **Pin 10** | Leveling Signal |

#### Step 3: Wiring
1.  **Mosfet Source** (Blue wire in diagram): Connect to **PIN 3** on the headlight adjuster connector.
2.  **Mosfet Drain** (Yellow wire in diagram): Connect to **PIN 10** on the headlight adjuster connector.

#### Step 4: Testing
1.  Connect the Arduino via USB to a power source (Laptop or USB car charger).
2.  Turn the potentiometer from side to side.
3.  Verify that the headlight beams move up and down corresponding to the knob rotation.

---

**Note:** If you have questions regarding the pins or the process, please refer to the photos in this repository or open an issue.
