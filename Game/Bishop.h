#pragma once
#include "ChessPiece.h"
class Bishop :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[4];
    static const std::string type;
    void GeneratePossibleMoves();
public:
    Bishop(GameBoard* board, const Vector2i& position, const Team& team);
    const std::string& GetType();
};

