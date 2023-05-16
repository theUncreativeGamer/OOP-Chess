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
				if (option == 1) {	//新遊戲
					/*record.push_back(gm);
					record_name.push_back(tmp);
					current_game = record.size() - 1;
					record[record.size() - 1].setChess();*/
					system("cls");
					cout << "選擇黑或白先手\n"
						<< "1: 黑先\n"
						<< "2: 白先\n";
					cin >> option;
					if (option == 1) {
						//record[current_game].setCurrent_player(0);
					}
					break;
				}
				else if (option == 2) {	//載入遊戲

					/*if (record.size() == 0) {
						system("cls");
						cout << "目前無遊戲資料\n"
							<< "請進行新遊戲\n"
							<< "輸入任意按鍵以繼續......\n";
						getchar();
						getchar();
						continue;
					}
					current_game = showRecord(record, record_name) - 1;*/
				}
				else if (option == 3)
				{
					cout << "請輸入FEN代碼\n";
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
			if (choice == 1) {	//投降
				system("cls");
				if (record[current_game].getCurrent_player() == 1) {
					cout << "黑方獲勝!!\n"
						<< "輸入任意按鍵以繼續......\n";
					getchar();
					getchar();
					record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//刪除此局遊戲
					record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
					break;
				}
				else {
					cout << "白方獲勝!!\n"
						<< "輸入任意按鍵以繼續......\n";
					getchar();
					getchar();
					record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//刪除此局遊戲
					record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
					break;
				}
			}
			else if (choice == 2) {	//跳 game
				system("cls");
				cout << "輸入遊戲欲儲存的檔名:\n";
				getchar();
				getline(cin, tmp);
				//cin >> tmp;
				record_name[current_game] = tmp;
				break;
			}
			if (record[current_game].isOver() == 2) {
				cout << "黑方獲勝!!\n"
					<< "輸入任意按鍵以繼續......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//刪除此局遊戲
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			else if (record[current_game].isOver() == 3) {
				cout << "白方獲勝!!\n"
					<< "輸入任意按鍵以繼續......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//刪除此局遊戲
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			else if (record[current_game].isOver() == 1) {
				cout << "平手!!\n"
					<< "輸入任意按鍵以繼續......\n";
				getchar();
				getchar();
				record.erase(record.begin() + current_game, record.begin() + current_game + 1);	//刪除此局遊戲
				record_name.erase(record_name.begin() + current_game, record_name.begin() + current_game + 1);
				break;
			}
			record[current_game].whichNeedPromote();
			record[current_game].showBoard();
		}
	}
}
}
