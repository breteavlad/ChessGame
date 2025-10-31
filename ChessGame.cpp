#include "ChessGame.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

ChessGame::ChessGame() : window(nullptr),renderer(nullptr),running(false) {}

bool ChessGame::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL wasn't initialized! " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Chess Game", 640, 640, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, nullptr);

    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize the board to starting position
    board.initStartPosition();

    // Load textures once
    if (!drawer.loadPieceTextures(renderer, "C:/Users/Vlad/Desktop/Projects/C++/ChessGame/Pieces")) {
        std::cerr << "Failed to load piece images.\n";
        return false;
    }

    running = true;
    return true;
}



void ChessGame::run() {
	while (running) {
		handleEvents();
		update();
		render();
		SDL_Delay(16);
	}
}

void ChessGame::handleEvents() {
	input.pollEvents(running, board);
}
void ChessGame::update() {

}
void ChessGame::render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	drawer.drawBoard(renderer, board);
	drawer.drawPieces(renderer,board);
    //drawer.loadPieceTextures(renderer, "C:/Users/Vlad/Desktop/Projects/C++/ChessGame/Pieces");

	SDL_RenderPresent(renderer);
}
void ChessGame::cleanup() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}



