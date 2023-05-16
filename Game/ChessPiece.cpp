#include "ChessPiece.h"

void ChessPiece::GeneratePossibleMoves()
{
}

ChessPiece::ChessPiece(const Vector2i& position, const Team& team)
	: position(position), team(team)
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



void ChessMove::DoCommonThing(GameBoard& board, const Vector2i& position)
{
	ChessPiece* piece = board.GetPiece(position);
	if (piece == nullptr)
		throw(std::invalid_argument("Something is wrong with the \"position\" parameter."));
	piece->isMoved = true;
	board.eppp = { -1,-1 };
}

bool ChessMove::DoSpecialThing(GameBoard& board, const Vector2i& position, void* param)
{
	return true;
}

ChessMove::ChessMove() : destination(-1,-1)
{
}

ChessMove::ChessMove(Vector2i destination) : destination(destination)
{
}
