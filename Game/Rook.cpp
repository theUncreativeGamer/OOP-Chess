#pragma once
#include "ChessPiece.h"
#include "Rook.h"

const Vector2i moveDirs[4]{
	Vector2i(1,0),
	Vector2i(0,-1),
	Vector2i(0,1),
	Vector2i(-1,0)
};
void Rook::GeneratePossibleMoves() {
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 4; j++) {
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
			else if (target->GetTeam() == team) break; // ���a�Ѥl��m
		}
	}
}
Rook::Rook(GameBoard* board, const Vector2i& position, const Team& team) :
	ChessPiece(board, position, team, "Rook")
{
}

