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
		output << "白方回合\n";
	}
	else if (current_player == Team::Black) {
		output << "黑方回合\n";
	}
	else {
		output << std::endl;
	}
	

	output << "\\ x a b c d e f g h \n";
	output << "y   _ _ _ _ _ _ _ _ \n";
	for (int i = 7; i >= 0; i--) {
		SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		output << i + 1 << "|  ";
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
			output << str;
		}
		output << std::endl;
	}

	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	if (check != 0) {
		output << "你被將軍了!!\n";
	}
}

std::string ConsoleView::GetNormalInput()
{
	output << "認輸請輸入\"resign\"" << std::endl << "跳出此局遊戲請輸入\"exit\"" << std::endl;
	std::string str;
	std::getline(input, str);
	return str;
}


std::string ConsoleView::ShowSelectedPiece(const GameBoard& board, ChessPiece* piece)
{
	system("cls");
	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	output << "第" << board.GetCurrentRound() << "回合\n";

	const Team& current_player = board.GetCurrentPlayer();
	if (current_player == Team::White) {
		output << "白方回合\n";
	}
	else if (current_player == Team::Black) {
		output << "黑方回合\n";
	}
	else {
		output << std::endl;
	}

	Vector2i origin = piece->GetPosition();
	std::set<Vector2i> destinations;
	for (const std::unique_ptr<ChessMove>& stuff : piece->GetAllPossibleMoves())
	{
		destinations.insert(stuff->moveDestination);
	}

	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	output << "\\ x a b c d e f g h \n";
	output << "y   _ _ _ _ _ _ _ _ \n";
	for (int i = 7; i >= 0; i--) {
		SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		output << i + 1 << "|  ";
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
			output << str;

		}
		output << std::endl;
	}


	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	output << "請選擇您要將棋子移動到的位置：\n";

	std::string result;
	std::getline(input, result);
	return result;
}

std::string ConsoleView::ShowPromoteBoard(const GameBoard& board, ChessPiece* piece)
{
	system("cls");
	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	output << "第" << board.GetCurrentRound() << "回合\n";

	const Team& current_player = board.GetCurrentPlayer();
	if (current_player == Team::White) {
		output << "白方回合\n";
	}
	else if (current_player == Team::Black) {
		output << "黑方回合\n";
	}
	else {
		output << std::endl;
	}

	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	output << "\\ x a b c d e f g h \n";
	output << "y   _ _ _ _ _ _ _ _ \n";
	for (int i = 7; i >= 0; i--) {
		SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		output << i + 1 << "|  ";
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
			output << str;

		}
		output << std::endl;
	}

	output << "達陣！！您的小兵將要晉升為更強大的棋子。" << std::endl;
	output << "請選擇您要讓此小兵晉升而成的目標：" << std::endl;
	output << "Q: 皇后" << std::endl;
	output << "N: 騎士" << std::endl;
	output << "B: 主教" << std::endl;
	output << "R: 城堡" << std::endl;

	std::string result;
	std::getline(input, result);
	return result;
}

void ConsoleView::ShowEndScreen(const Team& winner, const bool& isStopped)
{
	if (!isStopped)output << "沒有合法的行動！" << std::endl;
	else output << "遊戲已被中止" << std::endl;

	if (winner == Team::Black)
	{
		output << "黑方獲勝" << std::endl;
	}
	else if (winner == Team::White)
	{
		output << "白方獲勝" << std::endl;
	}
	else
	{
		output << "無人獲勝" << std::endl;
	}
}




