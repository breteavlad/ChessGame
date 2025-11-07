#include "Board.h"
#include "Piece.h"
#include <iostream>


// Initialize board to all EMPTY
void Board::initialize() {
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            board[r][c] = { Piece::PieceType::EMPTY, Piece::PieceColor::NONE };
}

void Board::printBoard() {
    std::cout << "\n=== Board State ===" << std::endl;
    for (int row = 0; row < 8; row++) {
        std::cout << "Row " << row << ": ";
        for (int col = 0; col < 8; col++) {
            int type = static_cast<int>(board[row][col].type);
            std::cout << type << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "==================\n" << std::endl;
}


void Board::initStartPosition() {
    initialize();  // Clear the board first

    // Black pieces at TOP (row 0)
    board[0][0] = { Piece::ROOK,   Piece::BLACK };
    board[0][1] = { Piece::KNIGHT, Piece::BLACK };
    board[0][2] = { Piece::BISHOP, Piece::BLACK };
    board[0][3] = { Piece::QUEEN,  Piece::BLACK };
    board[0][4] = { Piece::KING,   Piece::BLACK };
    board[0][5] = { Piece::BISHOP, Piece::BLACK };
    board[0][6] = { Piece::KNIGHT, Piece::BLACK };
    board[0][7] = { Piece::ROOK,   Piece::BLACK };
    for (int c = 0; c < 8; ++c)
        board[1][c] = { Piece::PAWN, Piece::BLACK };

    // White pieces at BOTTOM (row 7)
    board[7][0] = { Piece::ROOK,   Piece::WHITE };
    board[7][1] = { Piece::KNIGHT, Piece::WHITE };
    board[7][2] = { Piece::BISHOP, Piece::WHITE };
    board[7][3] = { Piece::QUEEN,  Piece::WHITE };
    board[7][4] = { Piece::KING,   Piece::WHITE };
    board[7][5] = { Piece::BISHOP, Piece::WHITE };
    board[7][6] = { Piece::KNIGHT, Piece::WHITE };
    board[7][7] = { Piece::ROOK,   Piece::WHITE };
    for (int c = 0; c < 8; ++c)
        board[6][c] = { Piece::PAWN, Piece::WHITE };
}


bool Board::isMoveLegal(int fromRow, int fromCol, int toRow, int toCol, Piece::PieceColor color) {
    // Get the moving and target pieces
    Piece::ChessPiece piece = getPiece(fromRow, fromCol);
    Piece::ChessPiece target = getPiece(toRow, toCol);

    // Can't move empty square
    if (piece.type == Piece::PieceType::EMPTY)
        return false;

    // Can't move opponent’s pieces
    if (piece.color != currentTurn)
        return false;

    // Can't capture own piece
    if (target.color == piece.color)
        return false;

    // Dispatch to specific piece rule
    switch (piece.type) {
    case Piece::PieceType::PAWN:
        return isPawnMoveLegal(fromRow, fromCol, toRow, toCol, piece.color);

    case Piece::PieceType::ROOK:
        return isRookMoveLegal(fromRow, fromCol, toRow, toCol);

    case Piece::PieceType::KNIGHT:
        return isKnightMoveLegal(fromRow, fromCol, toRow, toCol);

    case Piece::PieceType::BISHOP:
        return isBishopMoveLegal(fromRow, fromCol, toRow, toCol);

    case Piece::PieceType::QUEEN:
        return isQueenMoveLegal(fromRow, fromCol, toRow, toCol);

    case Piece::PieceType::KING:
        return isKingMoveLegal(fromRow, fromCol, toRow, toCol);

    default:
        return false;
    }

}



bool Board::isPawnMoveLegal(int fromRow, int fromCol, int toRow, int toCol,Piece::PieceColor color) {
    int dir = (color == Piece::PieceColor::WHITE) ? -1 : 1;
    int startRow = (color == Piece::PieceColor::WHITE) ? 6 : 1;
    Piece::ChessPiece target = getPiece(toRow, toCol);

    // Move forward
    if (fromCol == toCol && target.type == Piece::PieceType::EMPTY) {
        if (toRow == fromRow + dir) return true;
        if (fromRow == startRow && toRow == fromRow + 2 * dir && getPiece(fromRow + dir, fromCol).type == Piece::PieceType::EMPTY)
            return true;
    }

    // Capture
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + dir && target.type != Piece::PieceType::EMPTY && target.color != color)
        return true;

    return false;
}
bool Board::isBishopMoveLegal(int fromRow, int fromCol, int toRow, int toCol) {
    if (abs(toRow - fromRow) != abs(toCol - fromCol))
        return false;

    int rowDir = (toRow > fromRow) ? 1 : -1;
    int colDir = (toCol > fromCol) ? 1 : -1;

    int r = fromRow + rowDir;
    int c = fromCol + colDir;
    while (r != toRow && c != toCol) {
        if (getPiece(r, c).type != Piece::PieceType::EMPTY)
            return false;
        r += rowDir;
        c += colDir;
    }
    return true;
}

bool Board::isKnightMoveLegal(int fromRow, int fromCol, int toRow, int toCol) {
    int dr = abs(toRow - fromRow);
    int dc = abs(toCol - fromCol);
    return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

bool Board::isRookMoveLegal(int fromRow, int fromCol, int toRow, int toCol){
    if (fromRow != toRow && fromCol != toCol)
        return false;

    int rowDir = (toRow > fromRow) ? 1 : (toRow < fromRow ? -1 : 0);
    int colDir = (toCol > fromCol) ? 1 : (toCol < fromCol ? -1 : 0);

    int r = fromRow + rowDir;
    int c = fromCol + colDir;
    while (r != toRow || c != toCol) {
        if (getPiece(r, c).type != Piece::PieceType::EMPTY)
            return false;
        r += rowDir;
        c += colDir;
    }
    return true;
}

bool Board::isQueenMoveLegal(int fromRow, int fromCol, int toRow, int toCol) {
    return isRookMoveLegal(fromRow, fromCol, toRow, toCol) ||
        isBishopMoveLegal(fromRow, fromCol, toRow, toCol);
}

bool Board::canCastleWhite(int fromRow, int fromCol, int toRow, int toCol) {
    // White king is on row 7
    if (whiteKingMoved) return false;

    if (toCol == 6) { // King-side castle (O-O)
        if (whiteRookHMoved) return false;
        if (getPiece(7, 5).type != Piece::PieceType::EMPTY) return false;
        if (getPiece(7, 6).type != Piece::PieceType::EMPTY) return false;
        // Optional: check if king passes through check here
        return true;
    }
    else if (toCol == 2) { // Queen-side castle (O-O-O)
        if (whiteRookAMoved) return false;
        if (getPiece(7, 1).type != Piece::PieceType::EMPTY) return false;
        if (getPiece(7, 2).type != Piece::PieceType::EMPTY) return false;
        if (getPiece(7, 3).type != Piece::PieceType::EMPTY) return false;
        // Optional: check if king passes through check
        return true;
    }
    return false;
}

bool Board::canCastleBlack(int fromRow, int fromCol, int toRow, int toCol) {
    // Black king is on row 0
    if (blackKingMoved) return false;

    if (toCol == 6) { // King-side castle (O-O)
        if (blackRookHMoved) return false;
        if (getPiece(0, 5).type != Piece::PieceType::EMPTY) return false;
        if (getPiece(0, 6).type != Piece::PieceType::EMPTY) return false;
        return true;
    }
    else if (toCol == 2) { // Queen-side castle (O-O-O)
        if (blackRookAMoved) return false;
        if (getPiece(0, 1).type != Piece::PieceType::EMPTY) return false;
        if (getPiece(0, 2).type != Piece::PieceType::EMPTY) return false;
        if (getPiece(0, 3).type != Piece::PieceType::EMPTY) return false;
        return true;
    }
    return false;
}


bool Board::isKingMoveLegal(int fromRow, int fromCol, int toRow, int toCol) {
    int dr = abs(toRow - fromRow);
    int dc = abs(toCol - fromCol);

    // Normal 1-square move
    if (dr <= 1 && dc <= 1)
        return true;

    // Castling (2-square horizontal move)
    if (dr == 0 && dc == 2) {
        Piece::ChessPiece king = getPiece(fromRow, fromCol);
        if (king.color == Piece::WHITE)
            return canCastleWhite(fromRow, fromCol, toRow, toCol);
        else
            return canCastleBlack(fromRow, fromCol, toRow, toCol);
    }

    return false;
}
void Board::switchTurn() {
    currentTurn = (currentTurn == Piece::PieceColor::WHITE)
        ? Piece::PieceColor::BLACK
        : Piece::PieceColor::WHITE;
}


void Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    Piece::ChessPiece piece = getPiece(fromRow, fromCol);

    // Check move legality first
    if (!isMoveLegal(fromRow, fromCol, toRow, toCol, currentTurn)) {
        std::cout << "Illegal move!\n";
        return;
    }

    // NEW: Check if this move would leave/put own king in check
    if (wouldBeInCheckAfterMove(fromRow, fromCol, toRow, toCol)) {
        std::cout << "Illegal move! Your king would be in check.\n";
        return;
    }

    // === Special Case: Castling ===
    if (piece.type == Piece::PieceType::KING && abs(toCol - fromCol) == 2) {
        // NEW: Can't castle out of, through, or into check
        if (isKingInCheck(piece.color)) {
            std::cout << "Cannot castle while in check!\n";
            return;
        }

        // Check if king passes through check
        int middleCol = (fromCol + toCol) / 2;
        if (isSquareUnderAttack(fromRow, middleCol,
            piece.color == Piece::WHITE ? Piece::BLACK : Piece::WHITE)) {
            std::cout << "Cannot castle through check!\n";
            return;
        }

        if (piece.color == Piece::PieceColor::WHITE) {
            if (toCol == 6) {
                setPiece(7, 5, getPiece(7, 7));
                setPiece(7, 7, { Piece::PieceType::EMPTY, Piece::PieceColor::NONE });
            }
            else if (toCol == 2) {
                setPiece(7, 3, getPiece(7, 0));
                setPiece(7, 0, { Piece::PieceType::EMPTY, Piece::PieceColor::NONE });
            }
            whiteKingMoved = true;
        }
        else if (piece.color == Piece::PieceColor::BLACK) {
            if (toCol == 6) {
                setPiece(0, 5, getPiece(0, 7));
                setPiece(0, 7, { Piece::PieceType::EMPTY, Piece::PieceColor::NONE });
            }
            else if (toCol == 2) {
                setPiece(0, 3, getPiece(0, 0));
                setPiece(0, 0, { Piece::PieceType::EMPTY, Piece::PieceColor::NONE });
            }
            blackKingMoved = true;
        }
    }

    // Move the piece
    setPiece(toRow, toCol, piece);
    setPiece(fromRow, fromCol, { Piece::PieceType::EMPTY, Piece::PieceColor::NONE });

    // Update moved flags
    if (piece.type == Piece::PieceType::ROOK) {
        if (piece.color == Piece::PieceColor::WHITE) {
            if (fromRow == 7 && fromCol == 0) whiteRookAMoved = true;
            if (fromRow == 7 && fromCol == 7) whiteRookHMoved = true;
        }
        else {
            if (fromRow == 0 && fromCol == 0) blackRookAMoved = true;
            if (fromRow == 0 && fromCol == 7) blackRookHMoved = true;
        }
    }
    else if (piece.type == Piece::PieceType::KING) {
        if (piece.color == Piece::PieceColor::WHITE) whiteKingMoved = true;
        else blackKingMoved = true;
    }

    // Switch turn
    switchTurn();

    // NEW: Check for checkmate or stalemate
    if (isCheckmate(currentTurn)) {
        std::cout << "\n*** CHECKMATE! "
            << (currentTurn == Piece::WHITE ? "Black" : "White")
            << " wins! ***\n";
    }
    else if (isKingInCheck(currentTurn)) {
        std::cout << "\n*** CHECK! ***\n";
    }
    else if (isStalemate(currentTurn)) {
        std::cout << "\n*** STALEMATE! Draw! ***\n";
    }
}

std::pair<int, int> Board::findKing(Piece::PieceColor color) {
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece::ChessPiece piece = getPiece(r, c);
            if (piece.type == Piece::PieceType::KING && piece.color == color) {
                return { r, c };
            }
        }
    }
    return { -1, -1 }; // Should never happen in a valid game
}

bool Board::isSquareUnderAttack(int row, int col, Piece::PieceColor attackerColor) {
    // Check if any piece of attackerColor can attack this square
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            Piece::ChessPiece piece = getPiece(r, c);
            if (piece.color == attackerColor && piece.type != Piece::PieceType::EMPTY) {
                // Temporarily check if this piece could move to the target square
                // We need to bypass the turn check and check-validation
                switch (piece.type) {
                case Piece::PieceType::PAWN:
                    if (isPawnMoveLegal(r, c, row, col, piece.color)) {
                        // For pawns, only diagonal captures threaten squares
                        if (c != col) return true;
                    }
                    break;
                case Piece::PieceType::ROOK:
                    if (isRookMoveLegal(r, c, row, col)) return true;
                    break;
                case Piece::PieceType::KNIGHT:
                    if (isKnightMoveLegal(r, c, row, col)) return true;
                    break;
                case Piece::PieceType::BISHOP:
                    if (isBishopMoveLegal(r, c, row, col)) return true;
                    break;
                case Piece::PieceType::QUEEN:
                    if (isQueenMoveLegal(r, c, row, col)) return true;
                    break;
                case Piece::PieceType::KING:
                    // King threatens adjacent squares
                    if (abs(row - r) <= 1 && abs(col - c) <= 1) return true;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return false;
}


bool Board::isKingInCheck(Piece::PieceColor kingColor) {
    std::pair<int, int> kingPos = findKing(kingColor);
    int kingRow = kingPos.first;
    int kingCol = kingPos.second;

    if (kingRow == -1) return false; // No king found

    Piece::PieceColor opponentColor = (kingColor == Piece::PieceColor::WHITE)
        ? Piece::PieceColor::BLACK
        : Piece::PieceColor::WHITE;

    return isSquareUnderAttack(kingRow, kingCol, opponentColor);
}


bool Board::wouldBeInCheckAfterMove(int fromRow, int fromCol, int toRow, int toCol) {
    // Save the current state
    Piece::ChessPiece movingPiece = getPiece(fromRow, fromCol);
    Piece::ChessPiece targetPiece = getPiece(toRow, toCol);

    // Temporarily make the move
    setPiece(toRow, toCol, movingPiece);
    setPiece(fromRow, fromCol, { Piece::PieceType::EMPTY, Piece::PieceColor::NONE });

    // Check if king is in check
    bool inCheck = isKingInCheck(movingPiece.color);

    // Undo the move
    setPiece(fromRow, fromCol, movingPiece);
    setPiece(toRow, toCol, targetPiece);

    return inCheck;
}

bool Board::hasAnyLegalMoves(Piece::PieceColor color) {
    // Try every possible move for this color
    for (int fromR = 0; fromR < 8; ++fromR) {
        for (int fromC = 0; fromC < 8; ++fromC) {
            Piece::ChessPiece piece = getPiece(fromR, fromC);
            if (piece.color != color) continue;

            // Try all destination squares
            for (int toR = 0; toR < 8; ++toR) {
                for (int toC = 0; toC < 8; ++toC) {
                    // Save current turn
                    Piece::PieceColor savedTurn = currentTurn;
                    currentTurn = color;

                    if (isMoveLegal(fromR, fromC, toR, toC, color)) {
                        if (!wouldBeInCheckAfterMove(fromR, fromC, toR, toC)) {
                            currentTurn = savedTurn;
                            return true; // Found a legal move
                        }
                    }

                    currentTurn = savedTurn;
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(Piece::PieceColor color) {
    return isKingInCheck(color) && !hasAnyLegalMoves(color);
}

bool Board::isStalemate(Piece::PieceColor color) {
    return !isKingInCheck(color) && !hasAnyLegalMoves(color);
}