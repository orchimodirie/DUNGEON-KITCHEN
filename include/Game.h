#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Entity.h"

inline void clearScreen() {
    #ifdef _WIN32
        system("cls");   // If compiling on Windows, use cls
    #elif defined(__EMSCRIPTEN__)
        // Web Browser! Print 40 blank lines to push old text up
        for(int i = 0; i < 40; i++) std::cout << std::endl; 
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