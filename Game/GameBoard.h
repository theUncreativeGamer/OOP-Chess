#pragma once
#include "Vector2i.h"
#include <memory>
#include <list>
#include <vector>
#include <string>

class ChessPiece;
enum Team;

class GameBoard
{
protected:
	friend class ChessMove;
	friend bool LoadBoard(GameBoard& board, const std::string& fen);
	friend class ChessPiece;

	size_t width;
	size_t height;

	// This starts from 1.
	size_t currentRound;

	// A list of chess pieces on this board. 
	std::list<ChessPiece*> pieces;

	// A grid of pointers stating the position of each chess pieces.
	std::vector<std::vector<ChessPiece*>> grid;

	// En Passent-able Pawn's Position. 可以被「吃過路兵」規則解決掉的小兵的位置。
	// 如果此值為非法值則代表沒有棋子可以被「吃過路兵」規則解決掉。
	Vector2i eppp;

	// How many moves both players have made since the last pawn advance or piece capture.
	// Important for determining of draw.
	size_t halfmoveClock = 0;

	Team currentPlayer;
public:
	GameBoard(const size_t& width = 8, const size_t& height = 8);
	GameBoard(const GameBoard& another, const bool& nextRound = false);
	~GameBoard();
	const size_t& GetWidth() const;
	const size_t& GetHeight() const;
	const size_t& GetCurrentRound() const;

	// Returns true if the coordinate is in bounds.
	bool PositionIsInBounds(const Vector2i& position) const;

	// Get a pointer to the chess piece on a specific tile in the grid.
	ChessPiece* GetPiece(Vector2i position);

	// Get a read-only pointer to the chess piece on a specific tile in the grid.
	const ChessPiece* GetPiece(Vector2i position) const;

	const Team& GetCurrentPlayer() const;

	// Attempt to create a certain type of chess piece on certain position.
	// Returns the pointer to the created ChessPiece if success. Returns nullptr if fail.
	// If there is already a piece on the certain position, this function will fail.
	ChessPiece* AddPiece(const std::string& type, const Vector2i& position, const Team& team);

	// Remove the chess piece on the certain position.
	// Returns true if something is actually removed.
	bool RemovePiece(const Vector2i& position);

	bool CheckCheckmate(const Team& kingTeam);

	void NextRound();

	// Return true if current player can make a move.
	// Useful to determine whether to end the game.
	bool CanMakeAMove();

};

