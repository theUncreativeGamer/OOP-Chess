#include "Knight.h"

const Vector2i Knight::moveDirs[8] =
{
	Vector2i(  1,  2),
	Vector2i(  2,  1),
	Vector2i( -1,  2),
	Vector2i( -2,  1),
	Vector2i(  1, -2),
	Vector2i(  2, -1),
	Vector2i( -1, -2),
	Vector2i( -2, -1)
};

void Knight::GeneratePossibleMoves()
{
	for (int i = 0; i < 8; i++)
	{
		Vector2i moveDestination = position + moveDirs[i];
		if (!board->PositionIsInBounds(moveDestination)) continue;

		ChessPiece* target = board->GetPiece(moveDestination);
		if (target == nullptr || target->GetTeam() != team)
		{
			AddCommonMove(moveDestination);
		}
	}
}

Knight::Knight(const Vector2i& position, const Team& team, GameBoard* board)
	: ChessPiece(position, team, board)
{
}

const std::string Knight::type = "ÃM";

const std::string& Knight::GetType() const
{
	return type;
}

Knight* Knight::clone(GameBoard* anotherBoard) const
{
	Knight* result = new Knight(position, team, anotherBoard);
	return result;
}


