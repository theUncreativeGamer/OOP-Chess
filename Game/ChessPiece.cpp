#include "ChessPiece.h"

void ChessPiece::GeneratePossibleMoves()
{
}

void ChessPiece::AddCommonMove(const Vector2i& destination)
{
	allPossibleMoves.push_back(ChessMove(destination, board, this));
}

ChessPiece::ChessPiece(const Vector2i& position, const Team& team, GameBoard* board)
	: position(position), team(team), board(board)
{
	lastUpdateRound = 0;
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

const Team& ChessPiece::GetTeam() const
{
	return team;
}

bool ChessPiece::MoveTo(const Vector2i& destination)
{
	if (!(board->PositionIsInBounds(destination)))
		return false;
	if (board->GetPiece(destination) != nullptr)
		return false;
	board->grid[destination.y][destination.x] = this;
	board->grid[position.y][position.x] = nullptr;
	position = destination;
}



void ChessMove::MoveThePiece()
{
	piece->isMoved = true;
	board->eppp = { -1,-1 };
	board->RemovePiece(destination);
	piece->MoveTo(destination);
}

bool ChessMove::DoSpecialThing()
{
	return true;
}

ChessMove::ChessMove() : destination(-1,-1), board(nullptr), piece(nullptr)
{
}

ChessMove::ChessMove(const Vector2i& destination, GameBoard* board, ChessPiece* piece) 
	: destination(destination), board(board), piece(piece)
{
}
