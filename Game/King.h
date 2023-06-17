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
    King(const Vector2i& position, const Team& team, GameBoard* board);
    const std::string& GetType() const;
    King* clone(GameBoard* anotherBoard) const override;
};

struct CastlingMove
    : ChessMove
{
    ChessPiece& targetRook;
    bool isQueenSide;
    CastlingMove(const Vector2i& destination, GameBoard* board, ChessPiece* piece, ChessPiece& targetRook, const bool& isQueenSide);
    bool DoSpecialThing();
};
