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
	//顯示棋盤
	void showBoard_selectChess(GameBoard board, Team current_player, int check);
	//顯示棋盤 
	void showBoard_moveChess(GameBoard board, Team current_player);
	//顯示所有可能路徑
	void showAllPath(std::vector<ChessPiece*> chess, const std::vector<Vector2i>& posssible);
	//Promote時顯示的畫面
	void showPromoteBoard(const std::vector<ChessPiece*>& chess, int target);
	//顯示動畫
	//void showWalkAni(char board[8][8],)
private:
	//設定輸出顏色 111白字黃底 143白字灰底 96黑字黃底 128黑字灰底 192黑字紅底 207白字紅底 236紅字黃底
	void SetColor(int color);
};


