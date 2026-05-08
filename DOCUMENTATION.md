# DUNGEON KITCHEN - Project Documentation & Progress Tracker

## 1. Project Overview
**DUNGEON KITCHEN** is a text-based, turn-based C++ roguelike adventure. The goal of this project is to apply Object-Oriented Programming (OOP) concepts, data structures (like Linked Lists), and basic game loop architecture in C++. 

This document serves as a summary of the progress made so far, explaining the logic, structure, and design decisions behind the code.

---

## 2. Project Structure & Architecture
The project is divided into standard C++ file structures, separating declarations (`.h` files in `include/`) from implementations (`.cpp` files in `src/`).

- **`main.cpp`**: The entry point of the application.
- **`Entity.h`**: Contains the class definitions for the game's characters (Player and Enemies).
- **`Game.h` / `game.cpp`**: The core game engine and state machine.
- **`Inventory.h` / `Inventory.cpp`**: The custom Linked List data structure handling player items.
- **`displayUI.h` / `displayUI.cpp`**: The custom UI rendering system for the terminal.

---

## 3. Core Systems Explained

### A. Entry Point (`main.cpp`)
The main file is intentionally kept clean. 
- **Logic:** It seeds the random number generator using `srand(time(0))` so that every playthrough has unique RNG for enemy encounters, drops, and damage. 
- It then instantiates the `Game` object and calls `game.run()`, handing over control to the game loop.

### B. UI System (`displayUI.h` & `displayUI.cpp`)
Instead of just printing standard `cout` text line by line, I built a `MenuBox` class to create a semi-professional "windowed" look inside the terminal.
- **Attributes:** It stores a title, subtitle, a list of string options, and terminal dimensions (assumed 80x24 by default).
- **Drawing Logic (`draw`):** 
  - It calculates the longest string to determine the box width.
  - It calculates horizontal (`xOffset`) and vertical (`yOffset`) padding to center the box on the screen.
  - Uses special tokens like `<SEPARATOR>` and `<EMPTY>` to render dividing lines or blank spaces nicely inside the box.
- **I/O Handling:** Contains `getUserInput` and `systemPause`. This centralizes input fetching, keeping the main game logic free from `cin.ignore()` boilerplate and visual clutter.

### C. Entity System (`Entity.h`)
This file heavily utilizes **Inheritance**, a core pillar of OOP.
- **`Entity` (Base Class):** Represents any living thing in the game. It holds a `name`, `health`, and `damage`. It also handles universal logic like `isAlive()` and `takeDamage(int dmg)`.
- **`Player` (Derived Class):** Inherits from `Entity`. 
  - **Additions:** Adds `maxHealth`, `potions`, `level`, `exp`, `expToNextLevel`, and an `InventoryList`. It also tracks combat stats via `totalDMG` and an `Item *equipedWeapon` pointer.
  - **Logic:** Handles leveling up (scaling max HP by 20 and multiplying required EXP by 1.5) and potion logic (healing 15 HP without exceeding max HP).
- **`Enemy` (Derived Class):** Inherits from `Entity`.
  - **Additions:** Simply adds an `expDrop` variable so the game knows how much EXP to give the player upon victory.

### D. Inventory System (`Inventory.h` & `Inventory.cpp`)
Instead of using a standard `std::vector` or array, the inventory is built from scratch as a **Singly Linked List**. This is a great academic exercise in dynamic memory management and pointers.
- **`Item` (Node):** Acts as the node in our linked list. Contains `name`, `DamageBonus`, and a `next` pointer.
- **`InventoryList` (List Manager):** Manages `head` and `tail` pointers.
  - **`AddItem`:** Appends a newly dynamically allocated `Item` to the `tail` of the list.
  - **`displayAndEquip`:** Uses the `MenuBox` UI to list items dynamically. Prompts the user to select an item, traverses the list, and returns an `Item*` pointer so the game can equip it.
  - **`dropItem`:** Handles safely traversing the list to find a target item by name, updating the `previous` node's pointer, and `delete`-ing the node to prevent memory leaks.
  - **Destructor:** Iterates through all remaining items when the game closes and deletes them to clean up the heap.

### E. Game Loop & Finite State Machine (`Game.h` & `game.cpp`)
The `Game` class controls the flow of the entire application.
- **State Machine:** Uses an `enum GameState { MENU, PLAYING, GAMEOVER }`. The `run()` method contains a `while(isrunning)` loop and a switch statement. This dictates exactly which screen the player is currently seeing, making it easy to navigate between menus and battles.
- **Cross-platform utility:** `Game.h` includes an inline `clearScreen()` function using preprocessor directives (`#ifdef _WIN32`). This is a much better, modern approach than hardcoding `system("cls")`, allowing the game to compile cleanly on Linux, Mac, and Replit.

#### The `playturn()` Logic (Combat System)
This is the meat of the game right now.
1. **Enemy Generation:** Randomly selects an enemy name from an array and rolls random stats (HP: 30-70, DMG: 5-20, EXP: 40-100).
2. **Battle Loop:** A `while(myPlayer->isAlive() && goblin.isAlive())` loop runs the fight.
3. **Player Turn:** The player is prompted via `MenuBox` to either Attack or Heal.
4. **Enemy Turn:** If the enemy survives the player's attack, it automatically hits back.
5. **Post-Battle:**
   - **Victory:** Player gains EXP. 
   - **Loot Drop:** There is a 25% chance the enemy drops a random weapon. It rolls a random weapon name and random damage bonus (5-19) and adds it to the Linked List inventory.
   - **Level Up:** If EXP exceeds the threshold, `player->levelUp()` triggers.
   - **Defeat:** The state switches to `GAMEOVER`.

### F. Equipment System
Recently implemented, this system bridges the Inventory, Entity, and Game Loop systems:
- **Viewing & Selecting:** The player can access their inventory from the main menu (`Game::showMenu()`, Option 3).
- **Equipping Logic:** Upon selecting an item, a pointer to that `Item` node is returned. The `Player` object stores this in `equipedWeapon` and dynamically updates `totalDMG`.
- **Combat Integration:** The `MenuBox` battle UI dynamically displays the equipped weapon's name and the player's enhanced `totalDMG`, which is directly applied when attacking enemies in `playturn()`.

---

## 4. Current Status & What's Next

### What is working well:
* **UI Rendering:** The `MenuBox` dynamically sizes itself and looks great.
* **Combat Math:** Turn-based hitting and healing works without bugs.
* **Memory Management:** Inventory dynamically allocates and deallocates memory properly.
* **RNG:** Stat generation makes every battle slightly unpredictable.
* **Equipping Items:** Players can successfully equip items from their linked-list inventory to boost their damage.

### Missing Features / To-Do List for Future Updates:
1. **Saving / Loading:** Implementing a way to write the player's level and inventory to a `.txt` or `.json` file so progress isn't lost when closing the terminal.
2. **Expanding the Game Loop:** Right now `playturn()` throws you straight into one battle and puts you back in the menu. We might want a "Dungeon Crawler" state where the player explores rooms.
3. **Fixing Equipment Stacking (Bug):** Currently, equipping weapons continuously adds their `DamageBonus` to `totalDMG` instead of recalculating the base damage. This needs a reset mechanism when swapping weapons.