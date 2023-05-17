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
			Vector2i destination = position + moveDirs[i] * j;
			if (!board->PositionIsInBounds(destination)) break; // �X��

			ChessPiece* target = board->GetPiece(destination);
			if (target == nullptr) // �Ů�
			{
				allPossibleMoves.push_back(ChessMove(destination));
			}
			else if (target->GetTeam() != team) // �Ĥ�Ѥl��m
			{
				allPossibleMoves.push_back(ChessMove(destination));
				break;
			}
			else break; // ���a�Ѥl��m
		}
	}
}

Rook::Rook(const Vector2i& position, const Team& team)
	: ChessPiece(position, team)
{
}

const std::string Rook::type = "��";

const std::string& Rook::GetType() const
{
	return type;
}
