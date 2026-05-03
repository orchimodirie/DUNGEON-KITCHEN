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
        system("cls");
        MenuBox battleMenu(2); // Reduced padding to match your image style

        battleMenu.setTitle("FlavorTown RPG");
        
        battleMenu.addSeparator(); 
        battleMenu.addOption("[1] START THE GAME!");
        battleMenu.addOption("[2] QUIT!");
        
        // Pass true to tell the box not to add spacing at the bottom yet
        battleMenu.draw(true); 
        // Call our new method to get input
        int option = battleMenu.getUserInput("Choice: ");

        if(option != 1 && option != 2)
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
            }
            isValidInput = true;
        }
    }
}

void Game::playturn() {    
    Enemy goblin("Spicy Goblin", 50, 15, 120); //first enemy

    while(myPlayer->isAlive() && goblin.isAlive()) {
        
        system("cls"); //clear screenW

        MenuBox battleUI(2);
        battleUI.setTitle(" BATTLE ---");
        battleUI.setSubtitle("A wild " + goblin.name + " appears!");
        battleUI.addEmptyLine();
        //
        battleUI.addOption("Level: " + to_string(myPlayer->level) + " " + myPlayer->name + " HP: " + to_string(myPlayer->health) + "/" + to_string(myPlayer->maxHealth));

        // Display dynamic stats (using to_string to convert integers to text)
        battleUI.addOption("EXP: " + to_string(myPlayer->exp) + "/" + to_string(myPlayer->expToNextLevel)  + "  |  Potions: " + to_string(myPlayer->potions));
        
        
        battleUI.addEmptyLine();
        battleUI.addOption(goblin.name + " HP: " + to_string(goblin.health));
        battleUI.addSeparator();
        
        // Options
        battleUI.addOption("[1] Attack with Spatula");
        battleUI.addOption("[2] Drink Heal Potion");

        battleUI.draw(true);
        int option = battleUI.getUserInput();
        
        if(option == 1) {
            system("cls");
            goblin.takeDamage(myPlayer->damage);
            //draw box for the feedback
            MenuBox hitbox(2);
            hitbox.setTitle("Bam! Bam! Bam!");
            hitbox.addOption("You hit " + goblin.name + " for " + to_string(myPlayer->damage) + " damage!");
            hitbox.draw(false);
            hitbox.systemPause("Press [Enter] to continue...");
        } else if (option == 2) {
            system("cls");
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
            system("cls");
            MenuBox hitbox(2);
            myPlayer->takeDamage(goblin.damage);

            hitbox.setTitle("Slash! Slash! Slash!");
            hitbox.addOption(goblin.name + " attacked you for " + to_string(goblin.damage) + " damage!");
            hitbox.draw(false);
            hitbox.systemPause("Press [Enter] to continue...");
        }
    }

    //after the loop exit
    system("cls");
    MenuBox resultbox(2);
    if(myPlayer->isAlive()) {
        // player won, grant exp
        myPlayer->exp += goblin.expDrop;

        resultbox.setTitle("VICTORY!");
        resultbox.addOption("You cooked the " + goblin.name + "!");
        resultbox.addOption("Gained " + to_string(goblin.expDrop) + " EXP!");
        resultbox.draw(true);
        resultbox.systemPause("Press [Enter] to continue...");
        

        if(myPlayer->exp >= myPlayer->expToNextLevel) {
            myPlayer->levelUp();
            //level up

            system("cls");
            MenuBox levelbox(2);
            resultbox.setTitle("VICTORY!");
            resultbox.addOption("You leveled up! Level: " + to_string(myPlayer->level));
            resultbox.addOption("You cooked the " + goblin.name + "!"); 
            resultbox.draw(true);
            resultbox.systemPause("Press [Enter] to continue...");
                
        } else {

            resultbox.setTitle("VICTORY!");
            resultbox.addOption("You cooked the " + goblin.name + "!");
            resultbox.draw(true);
            resultbox.systemPause("Press [Enter] to continue...");
        }
        
        currentState = MENU;
    } else {
        resultbox.setTitle("DEFEATED!");
        resultbox.addOption("Cooked by " + goblin.name + "!");
        resultbox.draw(true);
        resultbox.systemPause("Press [Enter] to continue...");

        currentState = GAMEOVER;
    }   
}

void Game::showGameOver() {

    system("cls"); //clear current screeen
    MenuBox playBox(6);
    playBox.setTitle("GAME OVER!");
    playBox.addEmptyLine();
    playBox.setSubtitle("(Please come back!)");
    playBox.draw(true);
    playBox.systemPause("Press [Enter] to flee to exit...");

    isrunning = false;
}