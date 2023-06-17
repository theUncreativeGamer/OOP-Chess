#pragma once
#include "GameBoard.h"
#include "Vector2i.h"
#include <string>
#include <list>
#include <stdexcept>

class GameBoard;

enum Team
{
	White,
	Black,
	Undefined
};

// This struct describes how a valid move in the game of chess could be.
struct ChessMove
{
	// The game board this move is performed on.
	GameBoard* board;

	// The chess piece being moved
	ChessPiece* piece;

	// The absolute coordinate of the destination the chess piece is moving into.
	Vector2i destination;

	// This makes piece move to destination.
	void MoveThePiece();

	// Please override this function if the chess piece does something special after moving.
	// For example, en passent, promotion and castling.
	virtual bool DoSpecialThing();

	ChessMove();
	ChessMove(const Vector2i& destination, GameBoard* board, ChessPiece* piece);
	~ChessMove() = default;
};

class ChessPiece
{
protected:
	friend struct ChessMove;
	friend bool LoadBoard(GameBoard& board, const std::string& fen);

	// Pointer to the board this object is on.
	GameBoard* board;

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

	// This function removes any move that will make its own king get checkmated.
	void RemoveInvalidMoves();

	void AddCommonMove(const Vector2i& destination);
public:
	ChessPiece();
	ChessPiece(const Vector2i& position, const Team& team, GameBoard* board);

	// This function gets every possible move the chess piece could make.
	const std::list<ChessMove>& GetAllPossibleMoves();

	// The team this object is on.
	const Team& GetTeam() const;

	// The identifier for what type of piece this object is.
	virtual const std::string& GetType() const = 0;

	virtual ChessPiece* clone(GameBoard* anotherBoard) const = 0;

	// Tries to move this piece to an empty tile.
	// Returns true if succeed.
	bool MoveTo(const Vector2i& pos);
	
	
	void setTeam(Team T) {
		this->team = T;
	}
	
	Vector2i getPosition() {
		return position;
	}
};

