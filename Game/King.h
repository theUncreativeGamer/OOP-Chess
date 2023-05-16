#pragma once
#include "ChessPiece.h"
class King :
    public ChessPiece
{
protected:
    const Vector2i moveDirs[8];
    static const std::string type;
    void GeneratePossibleMoves();
public:
    King(GameBoard* board, const Vector2i& position, const Team& team);
    const std::string& GetType();
};

