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
	for (auto it = pieces.begin(); it != pieces.end(); it++)
	{
		if ((*it)->getPosition() == position)
		{
			delete (*it);
			pieces.erase(it);
			return true;
		}
	}

	return false;
}



