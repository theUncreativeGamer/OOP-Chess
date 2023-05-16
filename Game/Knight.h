#pragma once
#include "ChessPiece.h"
class Knight :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[8];
    static const std::string type;
    void GeneratePossibleMoves();
public:
    Knight(GameBoard* board, const Vector2i& position, const Team& team);
    const std::string& GetType();
};

