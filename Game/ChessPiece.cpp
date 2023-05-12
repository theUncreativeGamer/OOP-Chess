#include "ChessPiece.h"

void ChessPiece::GeneratePossibleMoves()
{
}

ChessPiece::ChessPiece(GameBoard* board, const Vector2i& position, const Team& team, const std::string& name)
	: board(board), type(name), position(position), team(team)
{
	lastUpdateRound = 0;
	allPossibleMoves.clear();
}

const std::list<ChessMove>& ChessPiece::GetAllPossibleMoves()
{
	if (board->GetCurrentRound() == lastUpdateRound)
	{
		return allPossibleMoves;
	}
	allPossibleMoves.clear();
	GeneratePossibleMoves();
	return allPossibleMoves;
}

const Team& ChessPiece::GetTeam()
{
	return team;
}

bool ChessMove::DoSpecialThing(void* param = nullptr)
{
	return true;
}

ChessMove::ChessMove(Vector2i destination) : destination(destination)
{
}
