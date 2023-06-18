#include "GameBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>

GameBoard::GameBoard(const size_t& width, const size_t& height)
	: width(width), height(height), currentRound(1), eppp(-1,-1), currentPlayer(Team::White)
{
	pieces.clear();
	grid.resize(height);
	for (int i = 0; i < height; i++)
	{
		grid[i].resize(width);
	}
	//std::cout << "height is " << grid.size() << std::endl;
	//std::cout << "width is " << grid[0].size() << std::endl;
}

GameBoard::GameBoard(const GameBoard& another, const bool& nextRound)
	: width(another.width), height(another.height), currentRound(another.currentRound + nextRound?1:0),
	currentPlayer(another.currentPlayer), halfmoveClock(another.halfmoveClock), eppp(another.eppp)
{
	for (const ChessPiece* p : another.pieces)
	{
		pieces.push_back(p->clone(this));
	}

	grid.resize(height);
	for (std::vector<ChessPiece*>& v : grid)
	{
		v.resize(width);
	}

	for (ChessPiece* p : pieces)
	{
		grid[p->GetPosition().y][p->GetPosition().x] = p;
	}
}

const size_t& GameBoard::GetWidth() const
{
	return width;
}

const size_t& GameBoard::GetHeight() const
{
	return height;
}

const size_t& GameBoard::GetCurrentRound() const
{
	return currentRound;
}

bool GameBoard::PositionIsInBounds(const Vector2i& position) const
{
	if (position.x < 0 || position.y < 0 || position.x >= width || position.y >= height)
		return false;
	return true;
}

GameBoard::~GameBoard()
{
	for (ChessPiece* p : pieces)
	{
		delete p;
	}
}

ChessPiece* GameBoard::GetPiece(Vector2i position)
{
	if (!PositionIsInBounds(position))
		return nullptr;
	return grid[position.y][position.x];
}

const ChessPiece* GameBoard::GetPiece(Vector2i position) const
{
	if (!PositionIsInBounds(position))
		return nullptr;
	return grid[position.y][position.x];
}

const Team& GameBoard::GetCurrentPlayer() const
{
	return currentPlayer;
}

ChessPiece* GameBoard::AddPiece(const std::string& type, const Vector2i& position, const Team& team)
{
	if (GetPiece(position) != nullptr)
		return nullptr;

	if (type == Pawn::type)
	{
		pieces.push_back(new Pawn(position, team, this));
	}
	else if (type == Rook::type)
	{
		pieces.push_back(new Rook(position, team, this));
	}
	else if (type == Knight::type)
	{
		pieces.push_back(new Knight(position, team, this));
	}
	else if (type == Bishop::type)
	{
		pieces.push_back(new Bishop(position, team, this));
	}
	else if (type == Queen::type)
	{
		pieces.push_back(new Queen(position, team, this));
	}
	else if (type == King::type)
	{
		pieces.push_back(new King(position, team, this));
	}
	else
	{
		return nullptr;
	}

	grid[position.y][position.x] = pieces.back();
	return pieces.back();
}

bool GameBoard::RemovePiece(const Vector2i& position)
{
	if (GetPiece(position) == nullptr)
		return false;
	grid[position.y][position.x] = nullptr;
	for (std::list<ChessPiece*>::iterator it = pieces.begin(); it != pieces.end(); it++)
	{
		if ((*it)->GetPosition() == position)
		{
			delete (*it);
			pieces.erase(it);
			return true;
		}
	}

	return false;
}

bool GameBoard::CheckCheckmate(const Team& kingTeam)
{
	if (kingTeam == Team::Undefined)return false;

	// Get the king(s)
	std::vector<ChessPiece*> kings;
	for (ChessPiece* p : pieces)
	{
		if (p->GetType() == King::type && p->GetTeam() == kingTeam)
		{
			kings.push_back(p);
		}
	}
	if (kings.size() == 0)return false;


	for (ChessPiece* king : kings)
	{
		// Get all possible moves of every opposing piece
		Team opposingTeam = kingTeam == Team::Black ? Team::White : Team::Black;
		for (ChessPiece* p : pieces)
		{
			if (p->GetTeam() == opposingTeam)
			{
				
				for (const std::unique_ptr<ChessMove>& m : p->GetAllPossibleMoves(true))
				{
					if (m->destination == king->GetPosition())return true;
				}
			}
		}
	}
	
	return false;
}

void GameBoard::NextRound()
{
	currentRound++;
	currentPlayer = currentPlayer == Team::Black ? Team::White : Team::Black;
}

bool GameBoard::CanMakeAMove()
{
	for (ChessPiece* p : pieces)
	{
		if (p->GetTeam() == currentPlayer && p->GetAllPossibleMoves().size() > 0)
			return true;
	}
	return false;
}




