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
	if (state != GameState::Finished)
	{
		output << "�C���w�Q����" << std::endl;
		return false;
	}

	if (winningTeam == Team::Black)
	{
		output << "�¤����" << std::endl;
	}
	else if (winningTeam == Team::White)
	{
		output << "�դ����" << std::endl;
	}
	else
	{
		output << "�L�H���" << std::endl;
	}
	state = GameState::Preparing;
}

const GameState& GameManager::State()
{
	return state;
}


Vector2i GameManager::StringToCoordinate(const std::string& str)
{
	if (str.size() < 2) return Vector2i(-1, -1);
	return Vector2i(str[0] - 'a', str[1] - '1');
}

bool GameManager::RoundRoutine()
{
	// ShowBoard
	bool checkMate = board.CheckCheckmate(board.GetCurrentPlayer());
	view.ShowBoard(board, checkMate);

	if (!board.CanMakeAMove())
	{
		output << "�S���X�k����ʡI" << std::endl;
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

	output << "�{��п�J\"resign\"" << std::endl << "���X�����C���п�J\"exit\"" << std::endl;
	std::string str;
	std::getline(input, str);

	if (str == "resign")
	{
		output << ((board.GetCurrentPlayer() == Team::Black) ? "�¤�" : "�դ�") << "�w�뭰\n";
		winningTeam = board.GetCurrentPlayer() == Team::Black ? Team::White : Team::Black;
		state = GameState::Finished;
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
		output << "��J���~�I�Э���" << std::endl;
		system("pause");
		return false;
	}

	// ShowSelectedPiece
	str = view.ShowSelectedPiece(board, selected);
	Vector2i destination = StringToCoordinate(str);
	if (!destination.InBounds())
	{
		output << "��J���~�I�Э���" << std::endl;
		system("pause");
		return false;
	}

	std::unique_ptr<ChessMove> move = nullptr;
	for (std::unique_ptr<ChessMove>& m : selected->GetAllPossibleMoves())
		if (m->destination == destination)
		{
			move = std::move(m);
		}
			

	if (move == nullptr)
	{
		output << "��J���~�I�Э���" << std::endl;
		system("pause");
		return false;
	}


	move->MoveThePiece();
	move->DoSpecialThing();
	board.NextRound();

	return true;
}

GameManager::GameManager()
	: board(), view()
{
}
