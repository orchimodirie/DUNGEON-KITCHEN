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
    do {
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
        }
        else {
            isValidInput = true;
            switch (option)
            {
            case 1:
                currentState = PLAYING;
                break;
            case 2:
                currentState = GAMEOVER;
                break;
            }
        }
    } while(!isValidInput);
}

void Game::playturn() {
    system("cls"); //clear current screen

    cout << "\n\n\n";
    cout << "          ==================================================          " << endl;
    cout << "          |                                                |          " << endl;
    cout << "          |           BATTLE SYSTEM COMMENCING...          |          " << endl;
    cout << "          |                                                |          " << endl;
    cout << "          |    (Imagine an epic battle with a Goblin!)     |          " << endl;
    cout << "          |                                                |          " << endl;
    cout << "          ==================================================          " << endl;
    cout << "\n\n";
    cout << "                   Press [Enter] to flee to the menu...                 " << endl;
    
    // We use cin.ignore() and cin.get() to wait for an Enter key press.
    // cin.ignore() clears out the 'Enter' key you pressed during the main menu.
    cin.ignore(1000, '\n'); 
    cin.get(); 

    // 4. Change the state so the engine routes us back to the start!
    currentState = MENU;
}

void Game::showGameOver() {
     system("cls"); //clear current screen

    cout << "\n\n\n";
    cout << "          ==================================================          " << endl;
    cout << "          |                                                |          " << endl;
    cout << "          |           GAME OVER   ---   THANK YOU          |          " << endl;
    cout << "          |                                                |          " << endl;
    cout << "          |                                                |          " << endl;
    cout << "          |                                                |          " << endl;
    cout << "          ==================================================          " << endl;
    cout << "\n\n";
    
    isrunning = false;
}