#include "Game.h"
#include "displayUI.h"
#include <limits>
#include <iomanip>
using namespace std;

Game::Game()
{
    currentState = MENU; // gamealways start at menu
    isrunning = true;    // Engine is on

     myPlayer = new Player("Chef", 100, 15);
}

Game::~Game() {
    delete myPlayer;
}

void Game::run() // main siwtcher of current state
{
    while (isrunning)
    {
        // the fsm router
        switch (currentState)
        {
        case MENU:
            showMenu();
            break;
        case PLAYING:
            playturn();
            break;
        case GAMEOVER:
            showGameOver();
            break;
        }
    }
}

void Game::showMenu()
{
    // print a welcome title
   bool isValidInput = false;
    while (!isValidInput){
        clearScreen();
        MenuBox battleMenu(2); // Reduced padding to match your image style

        battleMenu.setTitle("DUNGEON KITCHEN");
        
        battleMenu.addSeparator(); 
        battleMenu.addOption("[1] START THE GAME!");
        battleMenu.addOption("[2] QUIT!");
        battleMenu.addOption("[3] View Inventory");
        
        // Pass true to tell the box not to add spacing at the bottom yet
        battleMenu.draw(true); 
        // Call our new method to get input
        int option = battleMenu.getUserInput("Choice: ");

        if(option != 1 && option != 2 && option != 3)
        {
            isValidInput = false;
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n' );
        } else {
            switch (option)
            {
            case 1:
                currentState = PLAYING;
                break;
            case 2:
                currentState = GAMEOVER;
                break;
            case 3:
                Item* selectedItem = myPlayer->inventory.displayAndEquip(); // the function will return the node of chosen weapon
                if(selectedItem != nullptr) {
                    myPlayer->equipedWeapon = selectedItem; // equiping the item
                    myPlayer->totalDMG = myPlayer->damage + myPlayer->equipedWeapon->DamageBonus;
                }
                continue;
            }
            isValidInput = true;
        }
    }
}

void Game::playturn() {    

    // list of possible enemies
    string possibleNames[] = {"Spicy Goblin", "Burnt Toast" , "Moldy Cheese", "Sous-Chef Skeleton"};

    // pick a random name (0 through 3)
    int nameIndex = rand() % 4;
    string randomName = possibleNames[nameIndex];

    //generate random stats
    // HP (random number between 30 and 70)
    int randomHP = (rand() % 41) + 30;

    //random damage
    int randomDMG = (rand() % 16 ) + 5;

    //random EXP
    int randomEXP = (rand() % 61 ) + 40;

    Enemy goblin(randomName, randomHP, randomDMG, randomEXP);

    while(myPlayer->isAlive() && goblin.isAlive()) {
        
        clearScreen(); //clear screenW

        MenuBox battleUI(2);
        battleUI.setTitle(" BATTLE ---");
        battleUI.setSubtitle("A wild " + goblin.name + " appears!");
        battleUI.addEmptyLine();
        //
        battleUI.addOption("Level: " + to_string(myPlayer->level) + " " + myPlayer->name + " HP: " + to_string(myPlayer->health) + "/" + to_string(myPlayer->maxHealth));

        // Display dynamic stats (using to_string to convert integers to text)
        battleUI.addOption("EXP: " + to_string(myPlayer->exp) + "/" + to_string(myPlayer->expToNextLevel)  + "  |  Potions: " + to_string(myPlayer->potions));
        
        if(myPlayer->equipedWeapon != nullptr) battleUI.addOption("Weapon " + myPlayer->equipedWeapon->name + " | Total DMG: " + to_string(myPlayer->totalDMG));
        
        battleUI.addEmptyLine();
        battleUI.addOption(goblin.name + " HP: " + to_string(goblin.health));
        battleUI.addSeparator();
        
        // Options
        battleUI.addOption("[1] Attack");
        battleUI.addOption("[2] Drink Heal Potion");

        battleUI.draw(true);
        int option = battleUI.getUserInput();
        
            if(option == 1) {
                clearScreen();
                

                goblin.takeDamage(myPlayer->totalDMG);
                //draw box for the feedback
                MenuBox hitbox(2);
                hitbox.setTitle("Bam! Bam! Bam!");
                hitbox.addOption("You hit " + goblin.name + " for " + to_string(myPlayer->totalDMG) + " damage!");
                hitbox.draw(false);
                hitbox.systemPause("Press [Enter] to continue...");
            } else if (option == 2) {
                clearScreen();
                MenuBox healbox(2);
                healbox.setTitle("Player Healed!");
                healbox.addOption("Last HP: " + to_string(myPlayer->health));
                    myPlayer->heal();
                healbox.addOption("New HP: " + to_string(myPlayer->health));
                healbox.draw(false);
                healbox.systemPause("Press [Enter] to continue... ");

            } else {
                continue; // wrong input choice will restart the looping game
            }

        if (goblin.isAlive()) {
            clearScreen();
            MenuBox hitbox(2);
            myPlayer->takeDamage(goblin.damage);

            hitbox.setTitle("Slash! Slash! Slash!");
            hitbox.addOption(goblin.name + " attacked you for " + to_string(goblin.damage) + " damage!");
            hitbox.draw(false);
            hitbox.systemPause("Press [Enter] to continue...");
        }
    }

    //after the loop exit
    clearScreen();
    MenuBox resultbox(2);
    
    if (myPlayer->isAlive()) {
        // Grant EXP
        myPlayer->exp += goblin.expDrop;

        // Show Victory Screen
        resultbox.setTitle("VICTORY!");
        resultbox.addOption("You cooked the " + goblin.name + "!");
        resultbox.addOption("Gained " + to_string(goblin.expDrop) + " EXP!");
        resultbox.draw(false); 
        resultbox.systemPause("Press [Enter] to continue...");

        int dropChance = rand() % 100;
        if (dropChance < 25) { // 25% drop chance
            clearScreen();
            MenuBox weaponDrop(2);
            string Item[] = {"Stale Baguette", "Iron Skillet" , "Chef's knife", "Golden Spatula"};
            int random_WN = rand() % 4;

            int random_BNS_DMG = (rand() % 15) + 5;
            
            string ItemName = Item[random_WN];
            myPlayer->inventory.AddItem(ItemName, random_BNS_DMG);

            weaponDrop.addOption("The Goblin drop a " + ItemName);
            weaponDrop.draw(true);
            weaponDrop.systemPause("Press [Enter] to continue");
        }
        
        // Check for Level Up (No 'else' needed here!)
        if (myPlayer->exp >= myPlayer->expToNextLevel) {
            myPlayer->levelUp();

            clearScreen();
            MenuBox levelbox(2); // Use the new box!
            levelbox.setTitle("LEVEL UP!");
            levelbox.addEmptyLine();
            levelbox.addOption("You reached Level " + to_string(myPlayer->level) + "!");
            levelbox.addOption("Max HP increased to " + to_string(myPlayer->maxHealth));
            levelbox.addOption("Damage increased to " + to_string(myPlayer->damage));
            levelbox.addEmptyLine();
            levelbox.draw(false);
            levelbox.systemPause("Press [Enter] to claim your power...");
        }
        
        currentState = MENU;

    } else {
        // Defeat Screen (This is the ONLY 'else' we need)
        resultbox.setTitle("DEFEATED!");
        resultbox.addOption("Cooked by " + goblin.name + "!");
        resultbox.draw(false);
        resultbox.systemPause("Press [Enter] to continue...");

        currentState = GAMEOVER;
    }
}

void Game::showGameOver() {

    clearScreen(); //clear current screeen
    MenuBox playBox(6);
    playBox.setTitle("GAME OVER!");
    playBox.addEmptyLine();
    playBox.setSubtitle("(Please come back!)");
    playBox.draw(true);
    playBox.systemPause("Press [Enter] to flee to exit...");

    isrunning = false;
}