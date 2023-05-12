#include "ChessPiece.h"

void ChessPiece::GeneratePossibleMoves()
{
}

ChessPiece::ChessPiece(GameBoard* board, const std::string& name)
	: board(board), type(name)
{
	
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

bool ChessMove::DoSpecialThing(void* param)
{
	return true;
}

ChessMove::ChessMove(Vector2i destination) : destination(destination)
{
}
