#include "GameBoard.h"

GameBoard::GameBoard(const size_t& width, const size_t& height)
	: width(width), height(height), currentRound(1), eppp(-1,-1)
{
	pieces.clear();
	grid.resize(height);
	for (std::vector<ChessPiece*> vec : grid)
	{
		vec.resize(width);
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



