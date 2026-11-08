
# Snake Xenzia (C++ Console Game)

A classic **Snake Xenzia** arcade game built from scratch in C++ for the Windows console environment. This implementation features custom maze rendering, dynamic speed scaling, a multi-level progression system, and Windows API integration for console colors and smooth keyboard handling.

---

## Game Features & Specifications
* **Grid & Maze:** Built on a $24 \times 84$ console grid with custom border walls (`*#*`) and internal obstacles (`|`, `%`).
* **Level Progression & Speed Scaling:**
  * **Level 1:** Standard speed (`Delay: 150ms`)
  * **Level 2:** Unlocked at **200 points** (`Delay: 100ms`)
  * **Level 3:** Unlocked at **400 points** (`Delay: 60ms`)
* **Lives & Scoring System:** Starts with **3 lives** and awards **50 points** for every food item (`&`) consumed. The snake grows longer with each meal.
* **Console Styling:** Utilizes Windows API (`windows.h`) and `HANDLE` for real-time text coloring and smooth rendering.

---

## Controls
Use the keyboard **Arrow Keys** to navigate the snake:
* **Up Arrow** (`↑`) - Move Up
* **Down Arrow** (`↓`) - Move Down
* **Left Arrow** (`←`) - Move Left
* **Right Arrow** (`→`) - Move Right

---

## How to Compile and Run

1. Clone the repository:
   ```bash
   git clone [https://github.com/NoorulHudaImran209/Snake-Xenzia.git](https://github.com/NoorulHudaImran209/Snake-Xenzia.git)
