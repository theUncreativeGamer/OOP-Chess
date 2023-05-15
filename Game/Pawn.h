#pragma once
#include "ChessPiece.h"
class Pawn :
    public ChessPiece
{
protected:
    const Vector2i moveDirs[2] =
    {
        Vector2i(0,  1),
        Vector2i(0,  -1),
    };
    void GeneratePossibleMoves();
public:
    Pawn(GameBoard* board, const Vector2i& position, const Team& team);
    void Promote();
};

