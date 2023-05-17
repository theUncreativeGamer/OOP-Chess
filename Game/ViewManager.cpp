#include "ViewManager.h"
#include "GameBoard.h"
#include "ChessPiece.h"
#include "Vector2i.h"
using namespace std;

int ViewManager::MainMenu() {
	system("cls");
	int choice = 0;
	cout << "選擇模式\n"
		<< "1:玩家對玩家\n"
		<< "2:玩家對電腦\n"
		<< "3:離開遊戲\n";
	cin >> choice;
	while (choice < 1 || choice > 3) {
		system("cls");
		cout << "錯誤選項\n";
		system("pause");
		system("cls");
		cout << "選擇模式\n"
			<< "1:玩家對玩家\n"
			<< "2:玩家對電腦\n"
			<< "3:離開遊戲\n";
		cin >> choice;
	}
	return choice;
}


int ViewManager::GameMenu() {
	system("cls");
	cout << "請問要進行新遊戲或是載入遊戲紀錄?\n"
		<< "1: 新遊戲\n"
		<< "2: 載入遊戲\n"
		<< "3: 載入FEN代碼\n";

	int option;
	cin >> option;
	return option;
}

void ViewManager::SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void ViewManager::showBoard_selectChess(const GameBoard& board, const Team& current_player, int check)
{
	system("cls");
	if (current_player == Team::White) {
		cout << "白方回合\n";
	}
	else if (current_player == Team::Black) {
		cout << "黑方回合\n";
	}
	else {
		cout << endl;
	}
	cout << "投降請輸入\"surrender\"" << endl << "跳出此局遊戲請輸入\"exit\"" << endl;
	if (check != 0) {
		cout << "將軍!!\n";
	}
	cout << "\\ x ａｂｃｄｅｆｇｈ\n";
	cout << "y   ----------------\n";


	for (int i = 0; i < 8; i++) {
		SetColor(FOREGROUND_INTENSITY);
		cout << "|  ";
		for (int j = 0; j < 8; j++) {
			const ChessPiece* chess = board.GetPiece(Vector2i(j, i));
			
			if (chess == nullptr && (i + j) % 2 == 1) {
				SetColor(111);
				cout << "　";
			}
			else if (chess == nullptr && (i + j) % 2 == 0) {
				SetColor(143);
				cout << "　";
			}
			else if (chess->GetTeam() == White && (i + j) % 2 == 1) {
				SetColor(111); // 白字黃底
				cout << chess->GetType();
			}
			else if (chess->GetTeam() == White && (i + j) % 2 == 0) {
				SetColor(143); //白字灰底
				cout << chess->GetType();
			}
			else if (chess->GetTeam() == Black && (i + j) % 2 == 1) {
				SetColor(96); // 黑字黃底
				cout << chess->GetType();
			}
			else if (chess->GetTeam() == Black && (i + j) % 2 == 0) {
				SetColor(128); // 黑字灰底
				cout << chess->GetType();
			}
			
			
			
		}
		cout << endl;
	}
}

void ViewManager::showBoard_moveChess(GameBoard board, Team current_player)
{
}
