#include "Bishop.h"

const Vector2i Bishop::moveDirs[4]=
{
	{1,1},
	{-1,-1},
	{1,-1},
	{-1,1}
};
void Bishop::GeneratePossibleMoves() {
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

Bishop::Bishop(GameBoard* board, const Vector2i& position, const Team& team) :
	ChessPiece(board, position, team)
{
}

const std::string Bishop::type = "Bishop";

const std::string& Bishop::GetType()
{
	return type;
}


