# 🚀 Hand Gesture Controlled Space Shooter

## Overview
This project combines a C++ space shooter built with raylib and a Python-based computer vision controller. The Python program uses MediaPipe to detect hand position and gestures through a webcam, then uses PyAutoGUI to translate those gestures into keyboard inputs for the game.
A simple **2D space shooter** built with **C++ and raylib**, controlled using **hand gestures through a webcam**. 
#### ***The core idea is to make the game playable without keyboard***

The project has two parts:

- **C++ game** → handles the gameplay.
- **Python controller** → uses OpenCV + MediaPipe to detect hand movement and sends keyboard input to the game.

## 🎮 Controls

| Action | Keyboard | Hand Gesture |
|---|---|---|
| Move Left | `A` | Hand in left zone |
| Stop | Release `A/D` | Hand in center zone |
| Move Right | `D` | Hand in right zone |
| Shoot | `Space` | Make a fist / close your fingers |
| Restart | `R` | — |
| Quit Controller | `Q` | — |

The player starts with **7 HP**.

## 🧠 How It Works

```text
Webcam
   ↓
OpenCV + MediaPipe
   ↓
Hand Position / Gesture
   ↓
PyAutoGUI
   ↓
A / D / Space
   ↓
C++ raylib Game
```

The Python program acts like a virtual keyboard, so the game itself still uses normal `A`, `D`, and `Space` controls. The controller divides the 640px camera view into left, center, and right zones and uses hand landmarks to detect the shooting gesture. fileciteturn0file1L16-L37 fileciteturn0file1L63-L88

## 📁 Project Structure

```text
project/
│
├── .venv/                  # Python virtual environment
│
├── .vscode/                # VS Code configuration
│   ├── .gitkeep
│   ├── c_cpp_properties.json
│   ├── launch.json
│   ├── settings.json
│   └── tasks.json
│
├── assets/                 # Game assets
│   ├── Backgrounds/
│   ├── Bonus/
│   ├── PNG/
│   ├── Spritesheet/
│   └── Vector/
│
├── lib/                    # Required runtime libraries
│   ├── libgcc_s_dw2-1.dll
│   └── libstdc++-6.dll
│
├── src/                    # C++ source/header files
│
├── .gitattributes
├── .gitignore
├── hand_controller.py      # Webcam hand-gesture controller
├── main.code-workspace     # VS Code workspace
├── Makefile                # C++ build configuration
├── README.md
├── requirements.txt        # Python dependencies
└── run.bat                 # Starts the game and hand controller
```

## ⚙️ Requirements

### C++

- C++ compiler
- [raylib](https://www.raylib.com/)

### Python

Install the required packages:

```bash
pip install opencv-python mediapipe pyautogui numpy
```

A webcam is also required.

## ▶️ Running the Project

The project includes a **`.bat` file** that automates starting both programs.

### Recommended

Simply run:

```text
run.bat
```

This starts:

```text
main.exe
hand_controller.py
```

So you do not need to launch the game and controller separately.

### Manual

You can also run them individually:

```bash
main.exe
```

and:

```bash
python hand_controller.py
```

## 🕹️ Game Features

- Player spaceship movement
- Player shooting
- Enemy spawning
- Enemy shooting
- Bullet collision detection
- Enemy-player collision
- HP system
- Game-over screen
- Restart system

The C++ game runs in a `1080 × 720` window and continuously updates enemies, bullets, collisions, and rendering. fileciteturn0file0L5-L20 fileciteturn0file0L45-L65

## 🔧 Troubleshooting

**Webcam not working:** Make sure your camera is connected and available to Python.

**Textures not loading:** Run the game from the project directory so the relative `assets/...` paths are correct.

**Gesture controls not working:** Make sure `hand_controller.py` is running and the game window can receive keyboard input.

## 🔮 Future Improvements

- Add score and high-score system
- Add more enemy types
- Add sound effects and music
- Add more gestures
- Improve gesture detection
- Add increasing difficulty
- Add power-ups

---

## 📌 Tech Stack

**C++ · raylib · Python · OpenCV · MediaPipe · PyAutoGUI**
