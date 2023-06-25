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
	std::ostream& logger = std::cout;

	GameState state = GameState::Preparing;
	Team winningTeam = Team::Undefined;

	int startingRound;
	std::vector<std::string> boardStates;

	static const std::string defaultFEN;

	bool RoundRoutine();
public:
	GameManager();

	bool Load(const std::string& fen = defaultFEN);

	bool Run();

	const GameState& State();
};

