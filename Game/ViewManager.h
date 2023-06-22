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
	// 取得玩家選擇的位置，或是認輸或中止遊戲的選項
	virtual std::string GetNormalInput() = 0;
	//顯示一個棋子的可移動範圍
	virtual std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece) = 0;
	//Promote時顯示的畫面
	virtual std::string ShowPromoteBoard(const GameBoard& board, ChessPiece* piece) = 0;
	// 遊戲結束的畫面
	virtual void ShowEndScreen(const Team& winner, const bool& isStopped) = 0;

};

class ConsoleView 
	: public ViewManager
{
public:
	//顯示棋盤
	void ShowBoard(const GameBoard& board, bool check = false) override;
	// 取得玩家選擇的位置，或是認輸或中止遊戲的選項
	std::string GetNormalInput() override;
	//顯示一個棋子的可移動範圍
	std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece) override;
	//Promote時顯示的畫面
	std::string ShowPromoteBoard(const GameBoard& board, ChessPiece* piece) override;
	// 遊戲結束的畫面
	void ShowEndScreen(const Team& winner, const bool& isStopped) override;

private:
	std::ostream& output = std::cout;
	std::istream& input = std::cin;

	//設定輸出顏色 111白字黃底 143白字灰底 96黑字黃底 128黑字灰底 192黑字紅底 207白字紅底 236紅字黃底
	// 7 白字黑底
	void SetColor(int color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
};


