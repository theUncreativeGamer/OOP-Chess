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
			std::cout << "�O�_�ϥ�FEN�N�X�H(y/n)" << std::endl;
			std::getline(std::cin, in);
		}
		if (in.size() > 0 && (in[0] == 'y' || in[0] == 'Y'))
		{
			std::cout << "�п�JFEN�N�X�G" << std::endl;
			std::getline(std::cin, fen);
		}
		
		gameManager.Load(fen);
		if (gameManager.State() != GameState::Ready)
		{
			std::cout << "�z��J��FEN�N�X���~�A�ЦA�դ@���C" << std::endl;
			continue;
		}

		gameManager.Run();
		std::cout << "�O�_�n�A�i��@���C���H(y/n)" << std::endl;
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
