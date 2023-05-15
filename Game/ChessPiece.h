#pragma once
#include "GameBoard.h"
#include "Vector2i.h"
#include <string>
#include <list>
#include <stdexcept>

enum Team
{
	White,
	Black
};

// This struct describes how a valid move in the game of chess could be.
struct ChessMove
{
	// The absolute coordinate of the destination the chess piece is moving into.
	Vector2i destination;

	// Things that are applied during every chess move.
	void DoCommonThing(GameBoard& board, const Vector2i& position);

	// Please override this function if the chess piece does something special after moving.
	// For example, en passent, promotion and castling.
	virtual bool DoSpecialThing(GameBoard& board, const Vector2i& position, void* param = nullptr);

	ChessMove(Vector2i destination);
};

class ChessPiece
{
protected:
	friend ChessMove;

	// Pointer to the board this object is on.
	GameBoard* board;

	// The identifier for what type of piece this object is.
	std::string type;

	// The position of this object on the board.
	Vector2i position;

	// The team this object is on.
	Team team;

	// The last round allPossibleMoves is updated.
	size_t lastUpdateRound;

	// Every viable move this chess piece can make in the current round.
	std::list<ChessMove> allPossibleMoves;

	// True if this piece is moved. Important for pawns' first move and castling.
	bool isMoved = false;

	// Please override this function.
	// This function finds every possible move the chess piece could make and store them in allPossibleMoves.
	virtual void GeneratePossibleMoves();
public:
	ChessPiece(GameBoard* board, const Vector2i& position, const Team& team, const std::string& name = "NewObject");

	// This function gets every possible move the chess piece could make.
	const std::list<ChessMove>& GetAllPossibleMoves();

	// The team this object is on.
	const Team& GetTeam();

};

