#pragma once
#include "Piece.h"
#include "Board.h"
class InputHandler {
private:
	bool pieceSelected;
	int selectedRow = -1;
	int selectedCol = -1;
	void handleSquareClick(int row, int col, Board& board);
	void movePiece(int fromRow, int fromCol, int toRow, int toCol, Board& board);
public:
	void pollEvents(bool& running, Board& board);
	bool getPieceSelected() {
		return this->pieceSelected;
	}
	void setPieceSelected(bool selectPiece) {
		this->pieceSelected = selectPiece;
	}
	
};
