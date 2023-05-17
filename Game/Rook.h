#pragma once
#include "ChessPiece.h"
class Rook :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[4];
    void GeneratePossibleMoves();
public:
    static const std::string type;
    Rook() {};
    Rook(const Vector2i& position, const Team& team, GameBoard* board);
    const std::string& GetType() const;
};

