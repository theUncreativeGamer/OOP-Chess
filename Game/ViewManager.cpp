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
	std::cout << "��" << board.GetCurrentRound() << "�^�X" << std::endl;
	if (current_player == Team::White) {
		output << "�դ�^�X\n";
	}
	else if (current_player == Team::Black) {
		output << "�¤�^�X\n";
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
		output << "�A�Q�N�x�F!!\n";
	}
}

std::string ConsoleView::GetNormalInput()
{
	output << "�{��п�J\"resign\"" << std::endl << "���X�����C���п�J\"exit\"" << std::endl;
	std::string str;
	std::getline(input, str);
	return str;
}


std::string ConsoleView::ShowSelectedPiece(const GameBoard& board, ChessPiece* piece)
{
	system("cls");
	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	output << "��" << board.GetCurrentRound() << "�^�X\n";

	const Team& current_player = board.GetCurrentPlayer();
	if (current_player == Team::White) {
		output << "�դ�^�X\n";
	}
	else if (current_player == Team::Black) {
		output << "�¤�^�X\n";
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
	output << "�п�ܱz�n�N�Ѥl���ʨ쪺��m�G\n";

	std::string result;
	std::getline(input, result);
	return result;
}

std::string ConsoleView::ShowPromoteBoard(const GameBoard& board, ChessPiece* piece)
{
	system("cls");
	SetColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	output << "��" << board.GetCurrentRound() << "�^�X\n";

	const Team& current_player = board.GetCurrentPlayer();
	if (current_player == Team::White) {
		output << "�դ�^�X\n";
	}
	else if (current_player == Team::Black) {
		output << "�¤�^�X\n";
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

	output << "�F�}�I�I�z���p�L�N�n�ʤɬ���j�j���Ѥl�C" << std::endl;
	output << "�п�ܱz�n�����p�L�ʤɦӦ����ؼСG" << std::endl;
	output << "Q: �ӦZ" << std::endl;
	output << "N: �M�h" << std::endl;
	output << "B: �D��" << std::endl;
	output << "R: ����" << std::endl;

	std::string result;
	std::getline(input, result);
	return result;
}

void ConsoleView::ShowEndScreen(const Team& winner, const bool& isStopped)
{
	if (!isStopped)output << "�S���X�k����ʡI" << std::endl;
	else output << "�C���w�Q����" << std::endl;

	if (winner == Team::Black)
	{
		output << "�¤����" << std::endl;
	}
	else if (winner == Team::White)
	{
		output << "�դ����" << std::endl;
	}
	else
	{
		output << "�L�H���" << std::endl;
	}
}




