#pragma once
#include <string>

class Piece {
public:
    enum PieceType {
        PAWN = 0,
        QUEEN = 1,
        KING = 2,
        KNIGHT = 3,
        BISHOP = 4,
        ROOK = 5,
        EMPTY = 6
    };

    enum PieceColor {
        NONE = 0,
        WHITE = 1,
        BLACK = 2
    };


    struct ChessPiece {
        PieceType type;
        PieceColor color;
    };

private:

    std::string pieceToString(const ChessPiece& piece);

   
   

};