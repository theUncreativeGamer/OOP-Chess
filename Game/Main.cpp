#include "ChessPiece.h"
#include "GameBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "ViewManager.h"
#include "GameManager.h"
#include <iostream>



int main()
{
	ViewManager::instance = std::make_unique<ConsoleView>();
	GameManager gameManager;
	std::string in = "";
	std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	while (true)
	{
		if (in == "")
		{
			std::cout << "是否使用FEN代碼？(y/n)" << std::endl;
			std::getline(std::cin, in);
		}
		if (in.size() > 0 && (in[0] == 'y' || in[0] == 'Y'))
		{
			std::cout << "請輸入FEN代碼：" << std::endl;
			std::getline(std::cin, fen);
		}
		
		gameManager.Load(fen);
		if (gameManager.State() != GameState::Ready)
		{
			std::cout << "您輸入的FEN代碼有誤，請再試一次。" << std::endl;
			continue;
		}

		gameManager.Run();
		std::cout << "是否要再進行一場遊戲？(y/n)" << std::endl;
		std::getline(std::cin, in);
		if (in.size() > 0 && (in[0] == 'y' || in[0] == 'Y'))
		{
			in = "";
			continue;
		}
		else
		{
			break;
		}
	}
}
