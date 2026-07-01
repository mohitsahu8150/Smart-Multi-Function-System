# Smart Multi-Function Embedded System 🕹️⏱️

## 📖 Overview
A smart, multi-functional Arduino-based embedded system featuring a digital clock, stopwatch, and an interactive mini-game. The entire system is displayed on a 16x2 I2C LCD and is smartly controlled using just a **single push-button**. 

## ✨ Key Features
* **Mode 1: Scrolling Intro** - Displays a welcoming introduction message.
* **Mode 2: Digital Clock** - A real-time 12-hour clock (AM/PM).
* **Mode 3: Stopwatch** - A functional stopwatch with start/pause/reset capabilities controlled by the button.
* **Mode 4: Dino Mini-Game** - An interactive jumping game with dynamic speed difficulty and score tracking.
* **Single Button Interface** - Uses short presses for in-mode actions and long presses (>800ms) to switch modes.

## 🛠️ Hardware Components
* Arduino (Uno/Nano)
* 16x2 LCD Display with I2C Module
* Push Button
* Jumper Wires & Power Supply

## 💻 Software & Libraries
* **Arduino IDE**
* `Wire.h` (For I2C Communication)
* `LiquidCrystal_I2C.h` (For the LCD display)

## 👨‍💻 Developer
* **Mohit Sahu** (B.Tech 2nd Year ECE)
