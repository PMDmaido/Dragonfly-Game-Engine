# **README - Shark Tank**

**Copyright Trang Tran and Phuong Mai Do, 2025.**  

This project is inspired by the classic **Feeding Frenzy** game, where larger fish eat smaller fish while avoiding similar-sized or bigger predators. Developed on **Windows** using **Visual Studio**, this game brings an engaging underwater survival challenge.

---

## **2a. PLATFORM**

- **Platform**: Windows  
- **Compilation**:  
  - Build the game, ensuring all dependencies (**SFML, Dragonfly**) are correctly included.  
  - Use **Visual Studio** or another preferred IDE.  
  - After building, the game executable `shark-tank.exe` will be generated.  
- **How to Run**:  
  - Run `shark-tank.exe` in the build directory.  
- **Errors**:  
  - For runtime issues, refer to `sharktank.log` in the game directory.  

---

## **2b. PROJECT INFORMATION**

### **Game Mechanics**

This game features an ecosystem where different shark and fish sizes interact dynamically.

### **1. Shark Evolution System**
- **Small Shark**: Can eat **Little Fish**.
- **Medium Shark**: Can eat **Little Fish** and **Small Fish**.
- **Large Shark**: Can eat **Little Fish**, **Small Fish**, and **Medium Fish**.

### **2. Scoring System**
- **Little Fish**: **+10 Points**
- **Small Fish**: **+30 Points**
- **Medium Fish**: **+50 Points**
- **Special Bubble**: **+15 Points**
- **Pearl**: **+1 Life**
- **Bomb**: **Instant Game Over** (if touched)

### **3. Shark Evolution Progression**
- At **200 points**, **Small Shark evolves** into a **Medium Shark**.
- At **1000 points**, **Medium Shark evolves** into a **Large Shark**.
- At **1200 points**, **Bombs** starts to spawn.
- At **2000 points**, a **Diver appears**, signaling the final challenge.

### **4. Life Mechanic (NEW)**
- The player starts with **1 lives**.
- If **life reaches 0, the game is over**.
- **Eating a Pearl grants +1 life**, allowing the player to extend their survival.

### **5. Endgame Mechanic**
- The **Diver** spawns at **2000 points** as the last target.
- The **Shark must attack the Diver** to **win the game**.

---

## **3. Object System**

### **Sharks & Fish**
- **Three shark sizes**: Small, Medium, Large.
- **Three fish sizes**: Little, Small, Medium.
- **Fish sprites now flip based on movement direction** for more dynamic animations.
- **Increased fish spawn rate** to provide more food opportunities.
- **Adjusted point values for different fish** to balance progression speed.

### **Special Objects**
- **Bubble**: A collectible object granting additional points.
- **Diver**: The final challenge that only spawns when the player reaches **2000 points**.

### **New Objects**
- **Clam**:  
  - Found at the **bottom center of the ocean**.  
  - Opens its mouth **every 30 seconds** to spawn a **Pearl**.  

- **Pearl**:  
  - A collectible object spawned by the **Clam**.  
  - **Grants +1 life** to the shark upon consumption.  

- **Bomb**:  
  - Starts spawning when the player reaches **1200 points**.  
  - **Instantly ends the game** if touched by the shark.  

---

## **4. Audio & Graphics**
- **Sounds**: All audio assets are sourced from **freesound.org**.
- **Sprites**: Custom-designed, inspired by various online resources.

---

## **5. Documentation**
For additional details, refer to the **Dragonfly Game Engine Documentation**:  
👉 **[Dragonfly Tutorial](https://dragonfly.wpi.edu/tutorial/index.html)**

**Happy Coding! 🦈🐟🎮**  

*[Trang Tran]* - [tntran@wpi.edu]  
*[Phuong Mai Do]* - [pdo@wpi.edu]  
