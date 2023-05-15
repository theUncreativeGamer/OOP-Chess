#pragma once
#include "ChessPiece.h"
#include <memory>
#include <list>
#include <vector>
class GameBoard
{
protected:
	friend ChessMove;

	size_t width;
	size_t height;

	// This starts from 1.
	size_t currentRound;

	// A list of chess pieces on this board. 
	std::list<ChessPiece> pieces;

	// A grid of pointers stating the position of each chess pieces.
	std::vector<std::vector<ChessPiece*>> grid;
public:
	GameBoard(const size_t& width = 8, const size_t& height = 8);
	const size_t& GetWidth() const;
	const size_t& GetHeight() const;
	const size_t& GetCurrentRound() const;

	// Returns true if the coordinate is in bounds.
	bool PositionIsInBounds(Vector2i position) const;

	// Get a pointer to the chess piece on a specific tile in the grid.
	ChessPiece* GetPiece(Vector2i position);

	// Get a read-only pointer to the chess piece on a specific tile in the grid.
	const ChessPiece* GetPiece(Vector2i position) const;

};

