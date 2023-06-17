#pragma once
#include "ChessPiece.h"
class Queen :
    public ChessPiece
{
protected:
    static const Vector2i moveDirs[8];
    void GeneratePossibleMoves();
public:
    static const std::string type;
    Queen() {};
    Queen(const Vector2i& position, const Team& team, GameBoard* board);
    const std::string& GetType() const;
    Queen* clone(GameBoard* anotherBoard) const override;
};

