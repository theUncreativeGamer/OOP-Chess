#pragma once
#include "ChessPiece.h"
class Pawn :
    public ChessPiece
{
protected:
    void GeneratePossibleMoves() override;
public:
    static const std::string type;
    Pawn() {};
    Pawn(const Vector2i& position, const Team& team, GameBoard* board);
    const std::string& GetType() const;
    Pawn* clone(GameBoard* anotherBoard) const override;
};

class PawnMove
    : public ChessMove
{
public:
    PawnMove(const Vector2i& moveDestination, GameBoard* board, ChessPiece* piece, const bool& isFirstMove);
    bool isFirstMove;
    bool DoSpecialThing() override;
    virtual PawnMove* clone() override;
};

class EnPassentMove
    : public PawnMove
{
public:
    EnPassentMove(const Vector2i& moveDestination, const Vector2i& attackTarget, GameBoard* board, ChessPiece* piece);
    EnPassentMove* clone() override;
};
