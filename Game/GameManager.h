#pragma once
#include "GameBoard.h"
#include "ChessPiece.h"
#include "ViewManager.h"
#include <iostream>

enum class GameState
{
	Preparing,
	Ready,
	InGame,
	Finished
};

bool LoadBoard(GameBoard& board, const std::string& fen);

class GameManager
{
private:
	GameBoard board;
	std::istream& input = std::cin;
	std::ostream& logger = std::cout;

	GameState state = GameState::Preparing;
	Team winningTeam = Team::Undefined;

	static const std::string defaultFEN;

	bool RoundRoutine();

	Vector2i StringToCoordinate(const std::string& str);
public:
	GameManager();

	bool Load(const std::string& fen = defaultFEN);

	bool Run();

	const GameState& State();
};

