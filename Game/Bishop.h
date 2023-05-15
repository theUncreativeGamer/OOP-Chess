#pragma once
#include "ChessPiece.h"
class Bishop :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[4];
    void GeneratePossibleMoves();
public:
    Bishop(GameBoard* board, const Vector2i& position, const Team& team);
};

