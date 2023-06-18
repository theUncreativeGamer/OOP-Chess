#include "ViewManager.h"
#include "GameBoard.h"
#include "ChessPiece.h"
#include <set>

int ViewManager::MainMenu() {
	system("cls");
	int choice = 0;
	output << "選擇模式\n"
		<< "1:玩家對玩家\n"
		<< "2:離開遊戲\n";
	input >> choice;
	while (choice < 1 || choice > 3) {
		system("cls");
		output << "錯誤選項\n";
		system("pause");
		system("cls");
		output << "選擇模式\n"
			<< "1:玩家對玩家\n"
			<< "2:離開遊戲\n";
		input >> choice;
	}
	return choice;
}


int ViewManager::GameMenu() {
	system("cls");
	output << "請問要進行新遊戲或是載入遊戲紀錄?\n"
		<< "1: 新遊戲\n"
		<< "2: 載入FEN代碼\n";

	int option;
	input >> option;
	return option;
}

void ViewManager::SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void ViewManager::ShowBoard(const GameBoard& board, bool check)
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
		output << i+1 << "|  ";
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


std::string ViewManager::ShowSelectedPiece(const GameBoard& board, ChessPiece* piece)
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
		destinations.insert(stuff->destination);
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


