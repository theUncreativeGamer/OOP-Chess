#include "ViewManager.h"
#include "GameBoard.h"
#include "ChessPiece.h"
#include <set>

std::unique_ptr<ViewManager> ViewManager::instance = nullptr;

void ConsoleView::SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void ConsoleView::ShowBoard(const GameBoard& board, bool check)
{
	system("cls");
	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	const Team& current_player = board.GetCurrentPlayer();
	std::cout << "第" << board.GetCurrentRound() << "回合" << std::endl;
	if (current_player == Team::White) {
		logger << "白方回合\n";
	}
	else if (current_player == Team::Black) {
		logger << "黑方回合\n";
	}
	else {
		logger << std::endl;
	}
	

	logger << "\\ x a b c d e f g h \n";
	logger << "y   _ _ _ _ _ _ _ _ \n";
	for (int i = 7; i >= 0; i--) {
		SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		logger << i+1 << "|  ";
		for (int j = 0; j < 8; j++) {
			const ChessPiece* chess = board.GetPiece(Vector2i(j, i));
			int foregroundColor = FOREGROUND_RED;
			int backgroundColor = (i + j) % 2 == 1 ? (BACKGROUND_RED | BACKGROUND_GREEN) : BACKGROUND_INTENSITY;
			std::string str;

			if (chess == nullptr)
			{
				str = "  ";
			}
			else
			{
				str = chess->GetType();
				if (chess->GetTeam() == Team::White)
				{
					foregroundColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
				}
				else
				{
					foregroundColor = 0;
				}
			}
			
			SetColor(foregroundColor | backgroundColor);
			logger << str;
		}
		logger << std::endl;
	}

	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	if (check != 0) {
		logger << "你被將軍了!!\n";
	}
}


std::string ConsoleView::ShowSelectedPiece(const GameBoard& board, ChessPiece* piece)
{
	system("cls");
	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	logger << "第" << board.GetCurrentRound() << "回合\n";

	const Team& current_player = board.GetCurrentPlayer();
	if (current_player == Team::White) {
		logger << "白方回合\n";
	}
	else if (current_player == Team::Black) {
		logger << "黑方回合\n";
	}
	else {
		logger << std::endl;
	}

	Vector2i origin = piece->GetPosition();
	std::set<Vector2i> destinations;
	for (const std::unique_ptr<ChessMove>& stuff : piece->GetAllPossibleMoves())
	{
		destinations.insert(stuff->moveDestination);
	}

	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	logger << "\\ x a b c d e f g h \n";
	logger << "y   _ _ _ _ _ _ _ _ \n";
	for (int i = 7; i >= 0; i--) {
		SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		logger << i + 1 << "|  ";
		for (int j = 0; j < 8; j++) {
			const ChessPiece* chess = board.GetPiece(Vector2i(j, i));
			int foregroundColor = FOREGROUND_RED;
			int backgroundColor = (i + j) % 2 == 1 ? (BACKGROUND_RED | BACKGROUND_GREEN) : BACKGROUND_INTENSITY;
			std::string str;

			if (chess == nullptr)
			{
				str = "  ";
			}
			else
			{
				str = chess->GetType();
				if (chess->GetTeam() == Team::White)
				{
					foregroundColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
				}
				else
				{
					foregroundColor = 0;
				}
			}

			if (Vector2i(j, i) == origin)
			{
				backgroundColor = BACKGROUND_RED | BACKGROUND_BLUE;
			}
			else if (destinations.find(Vector2i(j, i)) != destinations.end())
			{
				backgroundColor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
			}

			SetColor(foregroundColor | backgroundColor);
			logger << str;

		}
		logger << std::endl;
	}


	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	logger << "請選擇您要將棋子移動到的位置：\n";

	std::string result;
	std::getline(input, result);
	return result;
}

void ConsoleView::ShowPromoteBoard(const GameBoard& board, ChessPiece* piece)
{
	system("cls");
	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	logger << "第" << board.GetCurrentRound() << "回合\n";

	const Team& current_player = board.GetCurrentPlayer();
	if (current_player == Team::White) {
		logger << "白方回合\n";
	}
	else if (current_player == Team::Black) {
		logger << "黑方回合\n";
	}
	else {
		logger << std::endl;
	}

	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	logger << "\\ x a b c d e f g h \n";
	logger << "y   _ _ _ _ _ _ _ _ \n";
	for (int i = 7; i >= 0; i--) {
		SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		logger << i + 1 << "|  ";
		for (int j = 0; j < 8; j++) {
			const ChessPiece* chess = board.GetPiece(Vector2i(j, i));
			int foregroundColor = FOREGROUND_RED;
			int backgroundColor = (i + j) % 2 == 1 ? (BACKGROUND_RED | BACKGROUND_GREEN) : BACKGROUND_INTENSITY;
			std::string str;

			if (chess == nullptr)
			{
				str = "  ";
			}
			else
			{
				str = chess->GetType();
				if (chess->GetTeam() == Team::White)
				{
					foregroundColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;
				}
				else
				{
					foregroundColor = 0;
				}
			}

			if (Vector2i(j, i) == piece->GetPosition())
			{
				backgroundColor = BACKGROUND_GREEN | BACKGROUND_BLUE;
			}

			SetColor(foregroundColor | backgroundColor);
			logger << str;

		}
		logger << std::endl;
	}
}




