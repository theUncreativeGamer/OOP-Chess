#pragma once
#include "ChessPiece.h"
#include "Queen.h"

const Vector2i moveDirs[8]=
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
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 8; j++) {
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

Queen::Queen(GameBoard* board, const Vector2i& position, const Team& team) :
	ChessPiece(board, position, team, "Queen")
{
}

