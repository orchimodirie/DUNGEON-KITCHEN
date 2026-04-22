# Flavortown RPG

> "Winner Winner Chicken Dinner."

**Flavortown RPG** is a text-based C++ roguelike adventure where you battle through infinite procedural kitchens, fight food-based monsters, and loot legendary ingredients.

## Features
* **Infinite Dungeons:** No two runs are the same. The menu changes every night.
* **Turn-Based Combat:** Strategic battles against *Spicy Goblins* and *Sous-Chef Skeletons*.
* **Loot System:** Find equipment like the *Stale Baguette* or the *Saucepan of Truth*.
* **Progression:** Level up your chef and gain stats to survive longer services.

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
