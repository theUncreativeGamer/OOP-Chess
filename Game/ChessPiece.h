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

enum ChessMoveType 
{
	Displace,
	Attack,
	AttackAndDisplace
};

struct ChessMove
{
	Vector2i destination;
	virtual bool DoSpecialThing(void* param);
	ChessMove(Vector2i destination);
};

class ChessPiece
{
protected:
	GameBoard* board;
	std::string type;
	Vector2i position;
	Team team;
	size_t lastUpdateRound;
	std::list<ChessMove> allPossibleMoves;

	virtual void GeneratePossibleMoves();
public:
	ChessPiece(GameBoard* board, const std::string& name = "NewObject");
	const std::list<ChessMove>& GetAllPossibleMoves();
	const Team& GetTeam();

};

