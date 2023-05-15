#pragma once
#include "ChessPiece.h"
#include "Bishop.h"
class Castle : public ChessPiece
{
protected:
	const Vector2i moveDirs[4]{
		{1,0},
		{0,-1},
		{0,1},
		{-1,0}
	};
	void GeneratePossibleMoves() {
		for (int i = 0; i < 4; i++) {
			for (int j = 1; j <= 4; j++) {
				Vector2i destination = position + moveDirs[i] * j;
				if (!board->PositionIsInBounds(destination)) break; // 出界

				ChessPiece* target = board->GetPiece(destination);
				if (target == nullptr) // 空格
				{
					allPossibleMoves.push_back(ChessMove(destination));
				}
			    else if (target->GetTeam() != team) // 敵方棋子位置
				{
					allPossibleMoves.push_back(ChessMove(destination));
					break;
				}
				else if (target->GetTeam() == team) break; // 玩家棋子位置
			}
		}
	}
public:
	Castle(GameBoard* board, const Vector2i& position, const Team& team) :
		ChessPiece(board, position, team, "Bishop")
	{
	}
};

