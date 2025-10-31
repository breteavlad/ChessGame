#include "Board.h"



// Initialize board to all EMPTY
void Board::initialize() {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = { Piece::PieceType::EMPTY, Piece::PieceColor::NONE };
}



// Initialize the board to the standard chess starting position
void Board::initStartPosition() {
    initialize();  // Clear the board first

    // White pieces
    board[0][0] = { Piece::ROOK,   Piece::WHITE };
    board[0][1] = { Piece::KNIGHT, Piece::WHITE };
    board[0][2] = { Piece::BISHOP, Piece::WHITE };
    board[0][3] = { Piece::QUEEN,  Piece::WHITE };
    board[0][4] = { Piece::KING,   Piece::WHITE };
    board[0][5] = { Piece::BISHOP, Piece::WHITE };
    board[0][6] = { Piece::KNIGHT, Piece::WHITE };
    board[0][7] = { Piece::ROOK,   Piece::WHITE };
    for (int c = 0; c < 8; ++c)
        board[1][c] = { Piece::PAWN, Piece::WHITE };

    // Black pieces
    board[7][0] = { Piece::ROOK,   Piece::BLACK };
    board[7][1] = { Piece::KNIGHT, Piece::BLACK };
    board[7][2] = { Piece::BISHOP, Piece::BLACK };
    board[7][3] = { Piece::QUEEN,  Piece::BLACK };
    board[7][4] = { Piece::KING,   Piece::BLACK };
    board[7][5] = { Piece::BISHOP, Piece::BLACK };
    board[7][6] = { Piece::KNIGHT, Piece::BLACK };
    board[7][7] = { Piece::ROOK,   Piece::BLACK };
    for (int c = 0; c < 8; ++c)
        board[6][c] = { Piece::PAWN, Piece::BLACK };
}
