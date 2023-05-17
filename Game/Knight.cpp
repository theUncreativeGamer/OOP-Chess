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
		Vector2i destination = position + moveDirs[i];
		if (!board->PositionIsInBounds(destination)) continue;

		ChessPiece* target = board->GetPiece(destination);
		if (target == nullptr || target->GetTeam() != team)
		{
			AddCommonMove(destination);
		}
	}
}

Knight::Knight(const Vector2i& position, const Team& team)
	: ChessPiece(position, team)
{
}

const std::string Knight::type = "�M";

const std::string& Knight::GetType() const
{
	return type;
}


