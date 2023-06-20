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
			if (!board->PositionIsInBounds(moveDestination)) break; // �X��

			ChessPiece* target = board->GetPiece(moveDestination);
			if (target == nullptr) // �Ů�
			{
				AddCommonMove(moveDestination);
			}
			else if (target->GetTeam() != team) // �Ĥ�Ѥl��m
			{
				AddCommonMove(moveDestination);
				break;
			}
			else break; // ���a�Ѥl��m
		}
	}
}

Queen::Queen(const Vector2i& position, const Team& team, GameBoard* board) :
	ChessPiece(position, team, board)
{
}

const std::string Queen::type = "�Z";

const std::string& Queen::GetType() const
{
	return type;
}

Queen* Queen::clone(GameBoard* anotherBoard) const
{
	Queen* result = new Queen(position, team, anotherBoard);
	return result;
}

