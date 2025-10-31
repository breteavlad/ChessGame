#pragma once
#include "Board.h"
#include "Renderer.h"
#include "InputHandler.h"

class ChessGame {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    Renderer drawer;
    Board board;
    InputHandler input;
    bool running;


public:
    ChessGame();
        bool init();
        void run();
        void handleEvents();
        void update();
        void render();
        void cleanup();


};