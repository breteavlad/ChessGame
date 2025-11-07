#pragma once
#include "Piece.h"

class Board {
private:
    Piece::ChessPiece board[8][8];
    Piece::PieceColor currentTurn = Piece::PieceColor::WHITE; // White starts

    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookAMoved = false; // a1 rook
    bool whiteRookHMoved = false; // h1 rook
    bool blackRookAMoved = false; // a8 rook
    bool blackRookHMoved = false; // h8 rook
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
        Piece::PieceColor getCurrentTurn() {
        return this->currentTurn;
    }

    void setCurrentTurn() {
        this->currentTurn = currentTurn;
    }
    void printBoard();
    
    bool isMoveLegal(int fromRow, int fromCol, int toRow, int toCol, Piece::PieceColor color);
    bool isPawnMoveLegal(int fromRow, int fromCol, int toRow, int toCol, Piece::PieceColor color);
    bool isRookMoveLegal(int fromRow, int fromCol, int toRow, int toCol);
    bool isKnightMoveLegal(int fromRow, int fromCol, int toRow, int toCol);
    bool isBishopMoveLegal(int fromRow, int fromCol, int toRow, int toCol);
    bool isKingMoveLegal(int fromRow, int fromCol, int toRow, int toCol);
    bool isQueenMoveLegal(int fromRow, int fromCol, int toRow, int toCol);
    bool canCastleWhite(int fromRow, int fromCol, int toRow, int toCol);
    bool canCastleBlack(int fromRow, int fromCol, int toRow, int toCol);
    void switchTurn();
    void movePiece(int fromRow, int fromCol, int toRow, int toCol);
    bool isSquareUnderAttack(int row, int col, Piece::PieceColor attackerColor);
    bool isKingInCheck(Piece::PieceColor kingColor);
    bool wouldBeInCheckAfterMove(int fromRow, int fromCol, int toRow, int toCol);
    bool hasAnyLegalMoves(Piece::PieceColor color);
    bool isCheckmate(Piece::PieceColor color);
    bool isStalemate(Piece::PieceColor color);
    std::pair<int, int> findKing(Piece::PieceColor color);
};
