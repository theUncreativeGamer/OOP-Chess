#pragma once
#include "ChessPiece.h"
class Knight :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
    Knight(GameBoard* board, const Vector2i& position, const Team& team);
};

