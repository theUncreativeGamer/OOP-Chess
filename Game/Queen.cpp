#pragma once
#include "ChessPiece.h"
#include "Queen.h"

const Vector2i Queen::moveDirs[8]=
{
	{1,0},
	{0,-1},
	{0,1},
	{-1,0},
	{1,1},
	{-1,-1},
	{1,-1},
	{-1,1}
};
void Queen::GeneratePossibleMoves() {
	for (int i = 0; i < 8; i++) {
		for (int j = 1; j <= 8; j++) {
			Vector2i moveDestination = position + moveDirs[i] * j;
			if (!board->PositionIsInBounds(moveDestination)) break; // 出界

			ChessPiece* target = board->GetPiece(moveDestination);
			if (target == nullptr) // 空格
			{
				AddCommonMove(moveDestination);
			}
			else if (target->GetTeam() != team) // 敵方棋子位置
			{
				AddCommonMove(moveDestination);
				break;
			}
			else break; // 玩家棋子位置
		}
	}
}

Queen::Queen(const Vector2i& position, const Team& team, GameBoard* board) :
	ChessPiece(position, team, board)
{
}

const std::string Queen::type = "后";

const std::string& Queen::GetType() const
{
	return type;
}

Queen* Queen::clone(GameBoard* anotherBoard) const
{
	Queen* result = new Queen(position, team, anotherBoard);
	return result;
}

