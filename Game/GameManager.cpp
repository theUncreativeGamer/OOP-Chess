#include "GameManager.h"

const std::string GameManager::defaultFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

bool GameManager::Load(const std::string& fen)
{
	if (state != GameState::Preparing && state != GameState::Ready)
		return false;
	if (LoadBoard(board, fen))
	{
		state = GameState::Ready;
		return true;
	}
	return false;
}

bool GameManager::Run()
{
	if (state != GameState::Ready)
		return false;
	state = GameState::InGame;
	while (state == GameState::InGame)
	{
		RoundRoutine();
	}
	ViewManager::instance->ShowEndScreen(winningTeam, !(state == GameState::Finished));
	state = GameState::Preparing;
	return true;
}

const GameState& GameManager::State()
{
	return state;
}

bool GameManager::RoundRoutine()
{
	// ShowBoard
	bool checkMate = board.CheckCheckmate(board.GetCurrentPlayer());
	ViewManager::instance->ShowBoard(board, checkMate);

	if (!board.CanMakeAMove())
	{
		if (checkMate)
		{
			winningTeam = board.GetCurrentPlayer() == Team::Black ? Team::White : Team::Black;
		}
		else
		{
			winningTeam = Team::Undefined;
		}

		state = GameState::Finished;
		return true;
	}

	std::string str = ViewManager::instance->GetNormalInput();

	if (str == "resign")
	{
		logger << ((board.GetCurrentPlayer() == Team::Black) ? "黑方" : "白方") << "已投降\n";
		winningTeam = board.GetCurrentPlayer() == Team::Black ? Team::White : Team::Black;
		state = GameState::Preparing;
		return true;
	}
	else if (str == "exit")
	{
		winningTeam = Team::Undefined;
		state = GameState::Preparing;
		return true;
	}

	ChessPiece* selected = board.GetPiece(StringToCoordinate(str));
	if (selected == nullptr || selected->GetTeam() != board.GetCurrentPlayer())
	{
		logger << "輸入錯誤！請重試" << std::endl;
		system("pause");
		return false;
	}

	// ShowSelectedPiece
	str = ViewManager::instance->ShowSelectedPiece(board, selected);
	Vector2i moveDestination = StringToCoordinate(str);
	if (!moveDestination.InBounds())
	{
		logger << "輸入錯誤！請重試" << std::endl;
		system("pause");
		return false;
	}

	std::unique_ptr<ChessMove> move = nullptr;
	for (std::unique_ptr<ChessMove>& m : selected->GetAllPossibleMoves())
		if (m->moveDestination == moveDestination)
		{
			move = std::move(m);
		}
			

	if (move == nullptr)
	{
		logger << "輸入錯誤！請重試" << std::endl;
		system("pause");
		return false;
	}


	move->MoveThePiece();
	move->DoSpecialThing();
	board.NextRound();

	return true;
}

GameManager::GameManager()
	: board()
{
}
