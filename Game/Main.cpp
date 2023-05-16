#include "GameBoard.h"
#include "ChessPiece.h"
#include "ViewManager.h"
#include "GameManager.h"
#include <iostream>

void main()
{
	GameBoard board;
	ViewManager ViewM;
	//GameManager GameM;
	while (true) {
		int option = ViewM.MainMenu();
		if (option == 1 || option == 2) {
			while (true) {
				option = ViewM.GameMenu();
				if (option == 1) {	//�s�C��
					/*record.push_back(gm);
					record_name.push_back(tmp);
					current_game = record.size() - 1;
					record[record.size() - 1].setChess();*/
					system("cls");
					cout << "��ܶ©Υե���\n"
						<< "1: �¥�\n"
						<< "2: �ե�\n";
					cin >> option;
					if (option == 1) {
						//record[current_game].setCurrent_player(0);
					}
					break;
				}
				else if (option == 2) {	//���J�C��

					/*if (record.size() == 0) {
						system("cls");
						cout << "�ثe�L�C�����\n"
							<< "�жi��s�C��\n"
							<< "��J���N����H�~��......\n";
						getchar();
						getchar();
						continue;
					}
					current_game = showRecord(record, record_name) - 1;*/
				}
				else if (option == 3)
				{
					cout << "�п�JFEN�N�X\n";
					string fen;
					getline(cin, fen);
					getline(cin, fen);
					/*record.push_back(gm);
					record_name.push_back(tmp);
					current_game = record.size() - 1;
					record[record.size() - 1].setChess(fen);*/
					break;
				}
			}
		}
		else if (option == 3) {
			break;
		}
		record[current_game].showBoard();
		while (record[current_game].isOver() == 0) {
			choice = record[current_game].moveChess();
			if (choice == 1) {	//�뭰
				system("cls");
				if (record[current_game].getCurrent_player() == 1) {
					cout << "�¤����!!\n"
						<< "��J���N����H�~��......\n";
					getchar();
					getchar();
					record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
					record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
					break;
				}
				else {
					cout << "�դ����!!\n"
						<< "��J���N����H�~��......\n";
					getchar();
					getchar();
					record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
					record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
					break;
				}
			}
			else if (choice == 2) {	//�� game
				system("cls");
				cout << "��J�C�����x�s���ɦW:\n";
				getchar();
				getline(cin, tmp);
				//cin >> tmp;
				record_name[current_game] = tmp;
				break;
			}
			if (record[current_game].isOver() == 2) {
				cout << "�¤����!!\n"
					<< "��J���N����H�~��......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			else if (record[current_game].isOver() == 3) {
				cout << "�դ����!!\n"
					<< "��J���N����H�~��......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			else if (record[current_game].isOver() == 1) {
				cout << "����!!\n"
					<< "��J���N����H�~��......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//�R�������C��
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			record[current_game].whichNeedPromote();
			record[current_game].showBoard();
		}
	}
}
}
