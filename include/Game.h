#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Entity.h"

inline void clearScreen() {
    #ifdef _WIN32
        system("cls");   // If compiling on Windows, use cls
    #else
        system("clear"); // If compiling on Linux/Mac/Replit, use clear
    #endif
}

enum GameState {
    MENU,
    PLAYING,
    GAMEOVER
};


class Game {
private:
    GameState currentState;
    bool isrunning;

    Player *myPlayer;
    // private helper functions;
    void showMenu();
    void playturn();
    void showGameOver();
public:

    Game();
    ~Game();
    void run();
};



#endif