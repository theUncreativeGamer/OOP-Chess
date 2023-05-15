#pragma once
#pragma once
#include "ChessPiece.h"
class Castle :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
    Castle(GameBoard* board, const Vector2i& position, const Team& team);
};

