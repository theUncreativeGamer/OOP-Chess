#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "Vector2i.h"
class GameBoard;
class ChessPiece;
enum Team;


class ViewManager {
public:
	//顯示棋盤
	void ShowBoard(const GameBoard& board, bool check = false);
	//顯示一個棋子的可移動範圍
	std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece);
	//Promote時顯示的畫面
	void showPromoteBoard(const std::vector<ChessPiece*>& chess, int target);

private:
	std::ostream& output = std::cout;
	std::istream& input = std::cin;

	//設定輸出顏色 111白字黃底 143白字灰底 96黑字黃底 128黑字灰底 192黑字紅底 207白字紅底 236紅字黃底
	// 7 白字黑底
	void SetColor(int color);
};


