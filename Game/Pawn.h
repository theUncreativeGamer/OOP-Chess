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
    void GeneratePossibleMoves();
public:
    static const std::string type;
    Pawn() {};
    Pawn(const Vector2i& position, const Team& team, GameBoard* board);
    const std::string& GetType() const;
    Pawn* clone(GameBoard* anotherBoard) const override;
};

