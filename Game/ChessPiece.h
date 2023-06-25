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
class ChessMove
{
public:

	// The game board this move is performed on.
	GameBoard* board;

	// The chess piece being moved
	ChessPiece* piece;

	// The absolute coordinate of the destination the chess piece is moving into.
	Vector2i moveDestination;

	// The absolute coordinate of the target piece that is going to be removed.
	Vector2i attackTarget;

	// This makes piece move to moveDestination.
	void MoveThePiece();

	// Please override this function if the chess piece does something special after moving.
	// For example, en passent, promotion and castling.
	virtual bool DoSpecialThing();

	virtual ChessMove* clone();

	ChessMove();
	ChessMove(const Vector2i& moveDestination, GameBoard* board, ChessPiece* piece);
	~ChessMove();

};

class ChessPiece
{
protected:
	friend class ChessMove;
	friend bool LoadBoard(GameBoard& board, const std::string& fen);
	friend std::string SaveBoardAsFEN(const GameBoard& board);

	// Pointer to the board this object is on.
	GameBoard* board;

	// The position of this object on the board.
	Vector2i position;

	// The team this object is on.
	Team team;

	// Every viable move this chess piece can make in the current round.
	std::list<std::unique_ptr<ChessMove>> allPossibleMoves;

	// True if this piece is moved. Important for pawns' first move and castling.
	bool isMoved = false;

	// Please override this function.
	// This function finds every possible move the chess piece could make and store them in allPossibleMoves.
	virtual void GeneratePossibleMoves();

	// This function removes any move that will make its own king get checkmated.
	void RemoveInvalidMoves();

	void AddCommonMove(const Vector2i& moveDestination);
public:
	ChessPiece();
	ChessPiece(const Vector2i& position, const Team& team, GameBoard* board);

	// This function gets every possible move the chess piece could make.
	std::list<std::unique_ptr<ChessMove>> GetAllPossibleMoves(bool includeInvalidMove = false);

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
	
	const Vector2i& GetPosition() const 
	{
		return position;
	}


};

