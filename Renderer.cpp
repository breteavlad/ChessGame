#include "Renderer.h"
#include "Board.h"
#include "SDL.h"
#include "Constants.h"
#include "SDL_image.h"
#include <iostream>


void Renderer::drawBoard(SDL_Renderer* renderer, const Board& board) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            bool isLight = (row + col) % 2 == 1;

            if (isLight) {
                // Light square - beige/cream color
                SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255);
            }
            else {
                // Dark square - brown color
                SDL_SetRenderDrawColor(renderer, 181, 136, 99, 255);
            }

            SDL_FRect rect = {
                static_cast<float>(col * SQUARE_SIZE),
                static_cast<float>(row * SQUARE_SIZE),
                static_cast<float>(SQUARE_SIZE),
                static_cast<float>(SQUARE_SIZE)
            };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}


bool Renderer::loadPieceTextures(SDL_Renderer* renderer, const std::string& folderPath) {
    const std::string pieces[] = {
        "WP", "WR", "WN", "WB", "WQ", "WK",
        "BP", "BR", "BN", "BB", "BQ", "BK"
    };

    for (auto& name : pieces) {
        std::string path = folderPath + "/" + name + ".png";
        SDL_Surface* surface = IMG_Load(path.c_str());
        if (!surface) {
            std::cerr << "Failed to load " << path << ": " << SDL_GetError() << std::endl;
            return false;
        }

        // Convert to RGBA format for consistent pixel manipulation
        SDL_Surface* converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA8888);
        SDL_DestroySurface(surface);
        if (!converted) {
            std::cerr << "Failed to convert surface: " << SDL_GetError() << std::endl;
            return false;
        }

        // Get the pixel format details (SDL3 uses SDL_PixelFormatDetails)
        const SDL_PixelFormatDetails* format = SDL_GetPixelFormatDetails(converted->format);

        // Manually process pixels to make white transparent
        SDL_LockSurface(converted);
        Uint32* pixels = (Uint32*)converted->pixels;
        int pixelCount = converted->w * converted->h;

        for (int i = 0; i < pixelCount; i++) {
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixels[i], format, nullptr, &r, &g, &b, &a);

            // If pixel is white (or very close to white), make it transparent
            if (r > 250 && g > 250 && b > 250) {
                pixels[i] = SDL_MapRGBA(format, nullptr, r, g, b, 0); // Set alpha to 0
            }
        }

        SDL_UnlockSurface(converted);

        // Create texture with blend mode for transparency
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, converted);
        SDL_DestroySurface(converted);

        if (!texture) {
            std::cerr << "Failed to create texture for " << name << ": " << SDL_GetError() << std::endl;
            return false;
        }

        // Enable alpha blending on the texture
        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

        pieceTextures[name] = texture;
    }
    return true;
}


void Renderer::drawPieces(SDL_Renderer* renderer, const Board& board) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece::ChessPiece piece = board.getPiece(row, col);
            if (piece.type == Piece::PieceType::EMPTY)
                continue;

            // Build key to lookup texture
            std::string key;
            key += (piece.color == Piece::PieceColor::WHITE) ? "W" : "B";

            switch (piece.type) {
            case Piece::PieceType::PAWN:   key += "P"; break;
            case Piece::PieceType::ROOK:   key += "R"; break;
            case Piece::PieceType::KNIGHT: key += "N"; break;
            case Piece::PieceType::BISHOP: key += "B"; break;
            case Piece::PieceType::QUEEN:  key += "Q"; break;
            case Piece::PieceType::KING:   key += "K"; break;
            default: continue;
            }

            SDL_Texture* texture = pieceTextures[key];
            if (!texture) continue;

            SDL_FRect dstRect = {
                static_cast<float>(col * SQUARE_SIZE),
                static_cast<float>(row * SQUARE_SIZE),
                static_cast<float>(SQUARE_SIZE),
                static_cast<float>(SQUARE_SIZE)
            };

            SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
        }
    }
}