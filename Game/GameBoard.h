#pragma once
#include "Vector2i.h"
#include "ChessPiece.h"
#include <memory>
#include <list>
#include <vector>
#include <string>

class ChessPiece;

class GameBoard
{
protected:
	friend struct ChessMove;
	friend bool LoadBoard(GameBoard& board, const std::string& fen);

	size_t width;
	size_t height;

	// This starts from 1.
	size_t currentRound;

	// A list of chess pieces on this board. 
	std::list<ChessPiece> pieces;

	// A grid of pointers stating the position of each chess pieces.
	std::vector<std::vector<ChessPiece*>> grid;

	// En Passent-able Pawn's Position. 可以被「吃過路兵」規則解決掉的小兵的位置。
	// 如果此值為非法值則代表沒有棋子可以被「吃過路兵」規則解決掉。
	Vector2i eppp;

	// How many moves both players have made since the last pawn advance or piece capture.
	// Important for determining of draw.
	size_t halfmoveClock = 0;
public:
	GameBoard(const size_t& width = 8, const size_t& height = 8);
	const size_t& GetWidth() const;
	const size_t& GetHeight() const;
	const size_t& GetCurrentRound() const;

	// Returns true if the coordinate is in bounds.
	bool PositionIsInBounds(const Vector2i& position) const;

	// Get a pointer to the chess piece on a specific tile in the grid.
	ChessPiece* GetPiece(Vector2i position);

	// Get a read-only pointer to the chess piece on a specific tile in the grid.
	const ChessPiece* GetPiece(Vector2i position) const;

	
};

