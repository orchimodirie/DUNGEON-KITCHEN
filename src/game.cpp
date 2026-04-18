#include "Game.h"
#include <iomanip>
using namespace std;

Game::Game()
{
    currentState = MENU; // gamealways star at menu
    isrunning = true;    // Engine is on
}

void Game::run()
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
    int option;
    string TITLE = "HOIASDLKAHSDLHASDLKAHSLDK";
    const int BoxspaceAfterBefore = 4;
    int boxPadding = TITLE.length() + BoxspaceAfterBefore*2;
    const int Xres = 80;
    const int Yres = 24;
    const int textline = 7;
    const int emptyline = (Yres - textline)/2;
    int spaceBeforeBox = (Xres/2) - (boxPadding/2);
    
    for(int i = 0; i<emptyline; i++) cout<<endl;
    cout<<setw(spaceBeforeBox)<<" "; for(int i = 0; i<boxPadding; i++) cout <<"="; cout<<endl;
    cout<<setw(spaceBeforeBox)<<" "; cout<<"="<<setw(BoxspaceAfterBefore-1)<<" "; cout<<TITLE<<setw(BoxspaceAfterBefore-1)<<" "<<"="<<endl;
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
    cout<<"The Game is currently Running!"<<endl;
    currentState = GAMEOVER;
}

void Game::showGameOver() {
    cout<<" GAME OVER!"<<endl;
    isrunning = false;
}


