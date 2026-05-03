#include <cstdlib>
#include <iostream> 
#include "Entity.h"
#include "Game.h"
#include <ctime>
using namespace std;

int main(){

  srand(time(0));

  
  Game game;
  game.run();
  return 0;
}

