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

Bishop::Bishop(const Vector2i& position, const Team& team, GameBoard* board) :
	ChessPiece(position, team, board)
{
}

const std::string Bishop::type = "��";

const std::string& Bishop::GetType() const
{
	return type;
}

Bishop* Bishop::clone(GameBoard* anotherBoard) const
{
	Bishop* result = new Bishop(position, team, anotherBoard);
	return result;
}


