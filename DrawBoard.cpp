//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
//1.add render loop
//2. draw the board grid with alternating colors
//3.add placeholder rendering for pieces
//4. event handling. detect mouse clicks
//5.game logic: movement validation. checkmate detection.

enum TYPEPIECE {
    PAWN = 0,
    QUEEN = 1,
    KING = 2,
    KNIGHT = 3,
    BISHOP = 4,
    ROOK = 5,
    EMPTY = 6
};

enum PIECE_COLOR {
    NONE = 0,
    WHITE = 1,
    BLACK = 2
};


struct ChessPiece {
    TYPEPIECE typePiece;
    PIECE_COLOR pieceColor;
};



class ChessGame {
private:
   SDL_Window* window;
    SDL_Renderer* renderer;
    ChessPiece boardPieces[8][8];
    bool running;
public:
    ChessGame() : window(nullptr), renderer(nullptr), running(false) {}

    bool drawBoard(SDL_Surface* surface, const SDL_PixelFormatDetails* pfd) {
        
        bool done = false;

        SDL_Init(SDL_INIT_VIDEO);
       
        this->window = SDL_CreateWindow("Chess Game", 800, 800, SDL_WINDOW_OPENGL);
        if (this->window == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, " Could not create window: %s \n", SDL_GetError());
            return false;
        }
        this->renderer = SDL_CreateRenderer(this->window, "Chess Renderer");
        
        if (this->renderer == NULL) {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer %s \n", SDL_GetError());
            return false;
        }

        initializeBoard();
        running = true;
        return true;
    }


    void initializeBoard() {
        for (int i = 0;i < 8;i++) {
            boardPieces[1][i].typePiece = PAWN;
            boardPieces[1][i].pieceColor = WHITE;

            boardPieces[6][i].typePiece = PAWN;
            boardPieces[6][i].pieceColor = BLACK;



        }
        boardPieces[0][0].typePiece = ROOK;
        boardPieces[0][7].typePiece = ROOK;
        boardPieces[0][1].typePiece = KNIGHT;
        boardPieces[0][6].typePiece = KNIGHT;
        boardPieces[0][2].typePiece = BISHOP;
        boardPieces[0][5].typePiece = BISHOP;
        boardPieces[0][3].typePiece = QUEEN;
        boardPieces[0][4].typePiece = KING;

        boardPieces[0][0].pieceColor = WHITE;
        boardPieces[0][7].pieceColor = WHITE;
        boardPieces[0][1].pieceColor = WHITE;
        boardPieces[0][6].pieceColor = WHITE;
        boardPieces[0][2].pieceColor = WHITE;
        boardPieces[0][5].pieceColor = WHITE;
        boardPieces[0][3].pieceColor = WHITE;
        boardPieces[0][4].pieceColor = WHITE;


        boardPieces[7][0].typePiece = ROOK;
        boardPieces[7][7].typePiece = ROOK;
        boardPieces[7][1].typePiece = KNIGHT;
        boardPieces[7][6].typePiece = KNIGHT;
        boardPieces[7][2].typePiece = BISHOP;
        boardPieces[7][5].typePiece = BISHOP;
        boardPieces[7][3].typePiece = QUEEN;
        boardPieces[7][4].typePiece = KING;

        boardPieces[7][0].pieceColor = BLACK;
        boardPieces[7][7].pieceColor = BLACK;
        boardPieces[7][1].pieceColor = BLACK;
        boardPieces[7][6].pieceColor = BLACK;
        boardPieces[7][2].pieceColor = BLACK;
        boardPieces[7][5].pieceColor = BLACK;
        boardPieces[7][3].pieceColor = BLACK;
        boardPieces[7][4].pieceColor = BLACK;
        for (int i = 2;i <= 5;i++) {
            for (int j = 0;j <= 7;j++) {
                boardPieces[i][j].typePiece = EMPTY;
                boardPieces[i][j].pieceColor = NONE;
            }

        }
    }






};





int main(int argc, char* args[])
{

    ChessGame();
    //openTestWindow();
  
    return 0;
}