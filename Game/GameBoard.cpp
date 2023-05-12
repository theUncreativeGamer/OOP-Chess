#include "GameBoard.h"

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

bool GameBoard::PositionIsInBounds(Vector2i position) const
{
	if (position.x < 0 || position.y < 0 || position.x >= width || position.y >= height)
		return false;
	return true;
}

ChessPiece* GameBoard::GetPiece(Vector2i position)
{
	if (!PositionIsInBounds(position))
		return nullptr;
	return grid[position.y][position.x];
}
