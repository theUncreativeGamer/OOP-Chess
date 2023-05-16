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
    bool hasMoved = false; 
    void GeneratePossibleMoves();
public:
    static const std::string type;
    Pawn() {};
    Pawn(const Vector2i& position, const Team& team);
    const std::string& GetType();
};

