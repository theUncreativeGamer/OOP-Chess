#pragma once
#include "ChessPiece.h"
#include <memory>
#include <list>
#include <vector>
class GameBoard
{
protected:

	size_t width;
	size_t height;

	size_t currentRound;

	// A list of game objects on this board. 
	std::list<ChessPiece> gameObjects;
	std::vector<std::vector<ChessPiece*>> grid;
public:
	GameBoard(const size_t& width = 8, const size_t& height = 8);
	const size_t& GetWidth() const;
	const size_t& GetHeight() const;
	const size_t& GetCurrentRound() const;

	bool PositionIsInBounds(Vector2i position) const;
	ChessPiece* GetPiece(Vector2i position);
};

