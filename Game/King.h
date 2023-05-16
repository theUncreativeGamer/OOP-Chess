#pragma once
#include "ChessPiece.h"
class King :
    public ChessPiece
{
protected:
    const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
    static const std::string type;
    King() {};
    King(const Vector2i& position, const Team& team);
    const std::string& GetType();
};

