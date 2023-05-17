#include "ViewManager.h"
#include "GameBoard.h"
#include "ChessPiece.h"
#include "Vector2i.h"
using namespace std;

int ViewManager::MainMenu() {
	system("cls");
	int choice = 0;
	cout << "��ܼҦ�\n"
		<< "1:���a�缾�a\n"
		<< "2:���a��q��\n"
		<< "3:���}�C��\n";
	cin >> choice;
	while (choice < 1 || choice > 3) {
		system("cls");
		cout << "���~�ﶵ\n";
		system("pause");
		system("cls");
		cout << "��ܼҦ�\n"
			<< "1:���a�缾�a\n"
			<< "2:���a��q��\n"
			<< "3:���}�C��\n";
		cin >> choice;
	}
	return choice;
}


int ViewManager::GameMenu() {
	system("cls");
	cout << "�аݭn�i��s�C���άO���J�C������?\n"
		<< "1: �s�C��\n"
		<< "2: ���J�C��\n"
		<< "3: ���JFEN�N�X\n";

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
		cout << "�դ�^�X\n";
	}
	else if (current_player == Team::Black) {
		cout << "�¤�^�X\n";
	}
	else {
		cout << endl;
	}
	cout << "�뭰�п�J\"surrender\"" << endl << "���X�����C���п�J\"exit\"" << endl;
	if (check != 0) {
		cout << "�N�x!!\n";
	}
	cout << "\\ x ���������\n";
	cout << "y   ----------------\n";


	for (int i = 0; i < 8; i++) {
		SetColor(FOREGROUND_INTENSITY);
		cout << "|  ";
		for (int j = 0; j < 8; j++) {
			const ChessPiece* chess = board.GetPiece(Vector2i(j, i));
			
			if (chess == nullptr && (i + j) % 2 == 1) {
				SetColor(111);
				cout << "�@";
			}
			else if (chess == nullptr && (i + j) % 2 == 0) {
				SetColor(143);
				cout << "�@";
			}
			else if (chess->GetTeam() == White && (i + j) % 2 == 1) {
				SetColor(111); // �զr����
				cout << chess->GetType();
			}
			else if (chess->GetTeam() == White && (i + j) % 2 == 0) {
				SetColor(143); //�զr�ǩ�
				cout << chess->GetType();
			}
			else if (chess->GetTeam() == Black && (i + j) % 2 == 1) {
				SetColor(96); // �¦r����
				cout << chess->GetType();
			}
			else if (chess->GetTeam() == Black && (i + j) % 2 == 0) {
				SetColor(128); // �¦r�ǩ�
				cout << chess->GetType();
			}
			
			
			
		}
		cout << endl;
	}
}

void ViewManager::showBoard_moveChess(GameBoard board, Team current_player)
{
}
