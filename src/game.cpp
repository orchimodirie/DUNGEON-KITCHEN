#include "Game.h"
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
    system("cls");

    int option;
    string TITLE = "FlavorTown RPG";
    const int BoxspaceAfterBefore = 4;
    int boxPadding = TITLE.length() + BoxspaceAfterBefore*2;
    const int Xres = 80;
    const int Yres = 24;
    const int textline = 7;
    const int emptyline = (Yres - textline)/2;
    int spaceBeforeBox = (Xres/2) - (boxPadding/2);
    
    for(int i = 0; i<emptyline; i++) cout<<endl;
    cout<<setw(spaceBeforeBox)<<" "; for(int i = 0; i<boxPadding; i++) cout <<"="; cout<<endl;
    cout<<setw(spaceBeforeBox)<<" "; cout<<"|"<<setw(BoxspaceAfterBefore-1)<<" "; cout<<TITLE<<setw(BoxspaceAfterBefore-1)<<" "<<"|"<<endl;
    cout<<setw(spaceBeforeBox)<<" "; for(int i = 0; i<boxPadding; i++) cout <<"="; cout<<endl;
    cout<<setw(spaceBeforeBox)<<" "<<"[1] START THE GAME!"<<endl;
    cout<<setw(spaceBeforeBox)<<" "<<"[2] QUIT!"<<endl;
    cout<<setw(spaceBeforeBox)<<" "; for(int i = 0; i<boxPadding; i++) cout <<"="; cout<<endl;
    cout<<setw(spaceBeforeBox)<<" "; cout<<"Choice: ";
    cin >> option;
    for(int i = 0; i<emptyline; i++) cout<<endl;
    

    switch (option)
    {
    case 1:
       currentState = PLAYING;
        break;
    case 2:
        currentState = GAMEOVER;
        break;
    default:
        break;
    }
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


