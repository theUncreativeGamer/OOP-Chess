#pragma once
#include "ChessPiece.h"
class Queen :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
    Queen(GameBoard* board, const Vector2i& position, const Team& team);
};

