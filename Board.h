#pragma once
#include "Piece.h"

class Board {
private:
    Piece::ChessPiece board[8][8];
public:
    void initialize();           // clear the board
    void initStartPosition();    // set up pieces in starting positions

    Piece::ChessPiece getPiece(int row, int col) const {
        return board[row][col];
    }

    void setPiece(int row, int col, const Piece::ChessPiece& piece) {
        board[row][col] = piece;
    }

    const Piece::ChessPiece(&getBoard() const)[8][8]{
        return board;
    }
};
