#pragma once
#include "GameBoard.h"
#include "Vector2i.h"
#include <string>
#include <list>

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

	// Please override this function if the chess piece does something special after moving.
	// For example, en passent, promotion and castling.
	virtual bool DoSpecialThing(void* param = nullptr);

	ChessMove(Vector2i destination);
};

class ChessPiece
{
protected:
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

	// Please override this function.
	// This function finds every possible move the chess piece could make and store them in allPossibleMoves.
	virtual void GeneratePossibleMoves();
public:
	ChessPiece(GameBoard* board, const Vector2i& position, const Team& team, const std::string& name = "NewObject");

	// This function gets every possible move the chess piece could make.
	const std::list<ChessMove>& GetAllPossibleMoves();

	// The team this object is on.
	const Team& GetTeam();
	
	void setPosition(Vector2i pos) {
		this->position = pos;
	}
	
	Vector2i getPosition() {
		return position;
	}
	
	bool Move(ChessPiece* chess, Vector2i destination, std::list<Vector2i>& validPos);

};

