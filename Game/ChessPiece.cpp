#include "ChessPiece.h"

void ChessPiece::GeneratePossibleMoves()
{
}

void ChessPiece::RemoveInvalidMoves()
{
	for (std::list<std::unique_ptr<ChessMove>>::iterator it = allPossibleMoves.begin(); it != allPossibleMoves.end();)
	{
		GameBoard tempBoard(*board);
		ChessMove tempMove((*it)->destination, &tempBoard, tempBoard.GetPiece(position));
		tempMove.MoveThePiece();

		bool isInvalid = tempBoard.CheckCheckmate(team);
		if (isInvalid) 
		{
			it = allPossibleMoves.erase(it);
			
		}
		else
		{
			it++;
		}
	}
}

void ChessPiece::AddCommonMove(const Vector2i& destination)
{
	allPossibleMoves.push_back(std::unique_ptr<ChessMove>(new ChessMove(destination, board, this)));
}

ChessPiece::ChessPiece()
	: board(nullptr), team(Team::Undefined)
{
}

ChessPiece::ChessPiece(const Vector2i& position, const Team& team, GameBoard* board)
	: position(position), team(team), board(board)
{
}

std::list<std::unique_ptr<ChessMove>> ChessPiece::GetAllPossibleMoves(bool includeInvalidMove)
{
	allPossibleMoves.clear();
	GeneratePossibleMoves();
	if (!includeInvalidMove)RemoveInvalidMoves();
	// Create a new list to store the duplicates
	std::list<std::unique_ptr<ChessMove>> duplicateList = std::move(allPossibleMoves);

	allPossibleMoves.clear();
	return duplicateList;
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
	{
		return false;
	}
		
	board->grid[destination.y][destination.x] = this;
	board->grid[position.y][position.x] = nullptr;
	position = destination;
	return true;
}



void ChessMove::MoveThePiece()
{
	board->eppp = { -1,-1 };
	piece->isMoved = true;
	board->RemovePiece(destination);
	piece->MoveTo(destination);
}

bool ChessMove::DoSpecialThing()
{
	return true;
}

ChessMove* ChessMove::clone()
{
	return new ChessMove(destination, board, piece);
}

ChessMove::ChessMove() : destination(-1,-1), board(nullptr), piece(nullptr)
{
}

ChessMove::ChessMove(const Vector2i& destination, GameBoard* board, ChessPiece* piece) 
	: destination(destination), board(board), piece(piece)
{
}

