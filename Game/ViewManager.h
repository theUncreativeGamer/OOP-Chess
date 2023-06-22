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
	// 當前使用的ViewManager
	static std::unique_ptr<ViewManager> instance;
	//顯示棋盤
	virtual void ShowBoard(const GameBoard& board, bool check = false) = 0;
	//顯示一個棋子的可移動範圍
	virtual std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece) = 0;
	//Promote時顯示的畫面
	virtual void ShowPromoteBoard(const GameBoard& board, ChessPiece* piece) = 0;

};

class ConsoleView 
	: public ViewManager
{
public:
	//顯示棋盤
	void ShowBoard(const GameBoard& board, bool check = false);
	//顯示一個棋子的可移動範圍
	std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece);
	//Promote時顯示的畫面
	void ShowPromoteBoard(const GameBoard& board, ChessPiece* piece);

private:
	std::ostream& logger = std::cout;
	std::istream& input = std::cin;

	//設定輸出顏色 111白字黃底 143白字灰底 96黑字黃底 128黑字灰底 192黑字紅底 207白字紅底 236紅字黃底
	// 7 白字黑底
	void SetColor(int color);
};


