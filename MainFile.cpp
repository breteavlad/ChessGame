//Using SDL and standard IO
#include <SDL3/SDL.h>
#include <stdio.h>
#include "ChessGame.h"


int main(int argc, char* args[])
{

    ChessGame game;



    if (!game.init()) {
        return -1;
    }
  
    game.run();
    return 0;
}