# Flavortown RPG

> "Winner Winner Chicken Dinner."

**Flavortown RPG** is a text-based C++ roguelike adventure where you battle through infinite procedural kitchens, fight food-based monsters, and loot legendary ingredients.

## Features
* **Turn-Based Combat:** Strategic battles against randomly generated food-based monsters with attack and healing mechanics.
* **Linked-List Inventory System:** Loot drops are stored in a custom-built, dynamically managed singly linked list. View and equip items like the *Stale Baguette* to increase your damage.
* **Progression:** Gain EXP from defeating enemies, level up your chef, and increase stats to survive longer services.
* **Custom UI Engine:** A dynamically sizing terminal UI (`MenuBox`) that centers itself and handles inputs cleanly.
* **Procedural Encounters:** Infinite random enemy encounters with varied stats and loot drops.

## Future Features
* **Save/Load System:** Persistent progression so you don't lose your stats and inventory between sessions.
* **Dungeon Crawler Exploration:** Expanding the game loop to allow players to explore rooms instead of straight random encounters.
* **Expanded Loot:** More weapon types, armor slots, and different consumable items.
* **Boss Battles:** Special, high-difficulty encounters with unique mechanics.

## How to Build & Run
You need a C++ compiler (GCC/Clang/MSVC) and CMake.

```bash
# 1. Clone the repository
git clone [https://github.com/orchimodirie/flavortown-rpg.git](https://github.com/orchimodirie/flavortown-rpg.git)

# 2. Navigate to the folder
cd flavortown-rpg

# 3. Create a build directory
mkdir build && cd build

# 4. Compile the game
cmake ..
make

# 5. Run!
./FlavortownRPG
