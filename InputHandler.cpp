#include "InputHandler.h"
#include "Board.h"
#include "SDL.h"
#include "Constants.h"

void InputHandler::pollEvents(bool& running, Board& board) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			running = false;
		}
		else if (e.type==SDL_EVENT_MOUSE_BUTTON_DOWN) {
			int x = e.button.x / SQUARE_SIZE;
			int y = e.button.y / SQUARE_SIZE;
		}
	}

}