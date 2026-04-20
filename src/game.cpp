#include "Game.h"
#include "displayUI.h"
#include <limits>
#include <iomanip>
using namespace std;

Game::Game()
{
    currentState = MENU; // gamealways star at menu
    isrunning = true;    // Engine is on
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
    // 1. print a welcome title
   bool isValidInput = false;
    while (!isValidInput){
        system("cls");
        MenuBox battleMenu(2); // Reduced padding to match your image style

        battleMenu.setTitle("FlavorTown RPG");
        
        battleMenu.addSeparator(); 
        battleMenu.addOption("[1] START THE GAME!");
        battleMenu.addOption("[2] QUIT!");
        
        // Pass 'true' to tell the box not to add spacing at the bottom yet
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
            cin.ignore();
        }
    }
}

void Game::playturn() {
    system("cls"); //clear current screen
    MenuBox playBox(6);
    playBox.setTitle("Battle System Commencin...");
    playBox.addEmptyLine();
    playBox.setSubtitle("(Imagine an Epic battle with a Goblin!)");
    playBox.draw(true);
    playBox.systemPause("Press [Enter] to flee to the menu...");


    currentState = MENU;
}

void Game::showGameOver() {
     system("cls"); //clear current screen
      MenuBox playBox(6);
    playBox.setTitle("GAME OVER!");
    playBox.addEmptyLine();
    playBox.setSubtitle("(Please come back!)");
    playBox.draw(true);
    playBox.systemPause("Press [Enter] to flee to the continue...");

    
    
    isrunning = false;
}