#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include "Entity.h"

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