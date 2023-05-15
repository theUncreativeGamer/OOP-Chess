#pragma once
#include "ChessPiece.h"
class King :
    public ChessPiece
{
protected:
    const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
    King(GameBoard* board, const Vector2i& position, const Team& team);
};

