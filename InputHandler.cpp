#include "InputHandler.h"
#include "Board.h"
#include "SDL.h"
#include "Constants.h"
#include <iostream>

void InputHandler::pollEvents(bool& running, Board& board) {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			running = false;
		}
		else if (e.type==SDL_EVENT_MOUSE_BUTTON_DOWN) {
			int col = e.button.x / SQUARE_SIZE;
			int row = e.button.y / SQUARE_SIZE;

			if (row >= 0 && row < 8 && col >= 0 && col < 8) {
				handleSquareClick(row, col, board);
			}
		}
	}

}

void InputHandler::handleSquareClick(int row, int col, Board& board) {
    std::cout << "Click at row=" << row << ", col=" << col << std::endl;
    if (!pieceSelected) {
        Piece::ChessPiece piece = board.getPiece(row, col);
        std::cout << "Piece type: " << static_cast<int>(piece.type) << std::endl;
        if (piece.type != Piece::PieceType::EMPTY) {
            selectedRow = row;
            selectedCol = col;
            pieceSelected = true;
            std::cout << "Piece selected!" << std::endl;
        }
    }
    else {
        std::cout << "Moving from (" << selectedRow << "," << selectedCol
            << ") to (" << row << "," << col << ")" << std::endl;

        // Call Board's movePiece which handles castling, validation, and turn switching
        board.movePiece(selectedRow, selectedCol, row, col);

        pieceSelected = false;
        std::cout << "Move complete!" << std::endl;
    }
}
