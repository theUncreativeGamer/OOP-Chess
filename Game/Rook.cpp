#pragma once
#include "Rook.h"
const Vector2i Rook::moveDirs[4] = {
		{1,0},
		{0,-1},
		{0,1},
		{-1,0}
};

void Rook::GeneratePossibleMoves()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 7; j++) {
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

Rook::Rook(const Vector2i& position, const Team& team, GameBoard* board)
	: ChessPiece(position, team, board)
{
}

const std::string Rook::type = "堡";

const std::string& Rook::GetType() const
{
	return type;
}

Rook* Rook::clone(GameBoard* anotherBoard) const
{
	Rook* result = new Rook(position, team, anotherBoard);
	return result;
}
