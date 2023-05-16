#pragma once
#include "GameBoard.h"
#include "ChessPiece.h"
#include <iostream>
#include <windows.h>
#include <vector>

class ViewManager {
public:
	int MainMenu();
	int GameMenu();
	//��ܴѽL
	void showBoard_selectChess(GameBoard board, Team current_player, int check);
	//��ܴѽL 
	void showBoard_moveChess(GameBoard board, Team current_player);
	//��ܩҦ��i����|
	void showAllPath(std::vector<ChessPiece*> chess, const std::vector<Vector2i>& posssible);
	//Promote����ܪ��e��
	void showPromoteBoard(const std::vector<ChessPiece*>& chess, int target);
	//��ܰʵe
	//void showWalkAni(char board[8][8],)
private:
	//�]�w��X�C�� 111�զr���� 143�զr�ǩ� 96�¦r���� 128�¦r�ǩ� 192�¦r���� 207�զr���� 236���r����
	void SetColor(int color);
};


