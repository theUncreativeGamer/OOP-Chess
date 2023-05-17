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
};

struct CastlingMove
    : ChessMove
{
    ChessPiece& targetRook;
    bool isQueenSide;
    //bool DoSpecialThing(GameBoard& board, const Vector2i& position, ChessPiece& piece, void* param = nullptr);
};
