#include "King.h"

const Vector2i moveDirs[8] =
{
	Vector2i(1,  1),
	Vector2i(1,  0),
	Vector2i(1,  -1),
	Vector2i(0,  1),
	Vector2i(0,  -1),
	Vector2i(-1, 1),
	Vector2i(-1, 0),
	Vector2i(-1, -1)
};

void King::GeneratePossibleMoves()
{
	for (int i = 0; i < 8; i++)
	{
		Vector2i destination = position + moveDirs[i];
		if (!board->PositionIsInBounds(destination)) continue;

		ChessPiece* target = board->GetPiece(destination);
		if (target == nullptr || target->GetTeam() != team)
		{
			allPossibleMoves.push_back(ChessMove(destination));
		}
	}
}

King::King(GameBoard* board, const Vector2i& position, const Team& team)
	: ChessPiece(board, position, team, "King")
{
}


