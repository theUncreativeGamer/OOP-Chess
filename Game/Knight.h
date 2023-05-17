#pragma once
#include "ChessPiece.h"
class Knight :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
    static const std::string type;
    Knight() {};
    Knight(const Vector2i& position, const Team& team, GameBoard* board);
    const std::string& GetType() const;
};

