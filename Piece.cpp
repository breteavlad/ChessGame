#include "Piece.h"
#include <string>

std::string pieceToString(const Piece::ChessPiece& piece) {
    if (piece.type == Piece::PieceType::EMPTY)
        return ".";

    std::string color = (piece.color == Piece::PieceColor::WHITE) ? "W" : "B";
    std::string type;

    switch (piece.type) {
    case Piece::PieceType::PAWN:   type = "P"; break;
    case Piece::PieceType::ROOK:   type = "R"; break;
    case Piece::PieceType::KNIGHT: type = "N"; break;
    case Piece::PieceType::BISHOP: type = "B"; break;
    case Piece::PieceType::QUEEN:  type = "Q"; break;
    case Piece::PieceType::KING:   type = "K"; break;
    default: type = "?"; break;
    }

    return color + type;
}