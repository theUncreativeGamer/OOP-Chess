#include "GameManager.h"

const std::string GameManager::defaultFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

bool GameManager::Load(const std::string& fen)
{
	if (state != GameState::Preparing && state != GameState::Ready)
		return false;
	if (LoadBoard(board, fen))
	{
		startingRound = board.GetCurrentRound();
		boardStates.clear();
		boardStates.push_back(SaveBoardAsFEN(board));
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
	else if (str == "save")
	{
		ViewManager::instance->PrintFEN(board);
		return true;
	}
	else if (str == "undo")
	{
		int lastRoundIndex = board.GetCurrentRound() - startingRound - 1;
		if (lastRoundIndex < 0)
		{
			logger << "沒辦法再復原了..." << std::endl;
			system("pause");
			return false;
		}
		LoadBoard(board, boardStates[lastRoundIndex]);
		return true;
	}
	else if (str == "redo")
	{
		int nextRoundIndex = board.GetCurrentRound() - startingRound + 1;
		if (nextRoundIndex >= boardStates.size())
		{
			logger << "沒辦法再重做了..." << std::endl;
			system("pause");
			return false;
		}
		LoadBoard(board, boardStates[nextRoundIndex]);
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
	boardStates.erase(boardStates.begin() + (board.GetCurrentRound() - startingRound), boardStates.end());
	boardStates.push_back(SaveBoardAsFEN(board));

	return true;
}

GameManager::GameManager()
	: board(), startingRound(1)
{
}
