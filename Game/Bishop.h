#pragma once
#include "ChessPiece.h"
class Bishop :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[4];
    void GeneratePossibleMoves();
public:
    static const std::string type;
    Bishop() {};
    Bishop(const Vector2i& position, const Team& team);
    const std::string& GetType() const;
};

