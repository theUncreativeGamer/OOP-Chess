#pragma once
#include "ChessPiece.h"
class Knight :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
};

