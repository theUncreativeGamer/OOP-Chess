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

Rook::Rook(const Vector2i& position, const Team& team, GameBoard* board)
	: ChessPiece(position, team, board)
{
}

const std::string Rook::type = "��";

const std::string& Rook::GetType() const
{
	return type;
}

Rook* Rook::clone(GameBoard* anotherBoard) const
{
	Rook* result = new Rook(position, team, anotherBoard);
	return result;
}
