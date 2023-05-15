#pragma once
#include "ChessPiece.h"
class Rook :
    public ChessPiece
{
protected:
    const Vector2i moveDirs[4];
    void GeneratePossibleMoves();
public:
    Rook(GameBoard* board, const Vector2i& position, const Team& team);
};

