#pragma once
#include "SDL.h"
#include "Board.h"
#include <map>
class Renderer {
private:
	std::map<std::string, SDL_Texture*> pieceTextures;
public:
	bool loadPieceTextures(SDL_Renderer* renderer, const std::string& folderPath);
	void drawBoard(SDL_Renderer* renderer,const Board& board);
	void drawPieces(SDL_Renderer* renderer,const Board& board);
	void highLightSquare(SDL_Renderer* renderer, int row, int col);
	void cleanup();

};