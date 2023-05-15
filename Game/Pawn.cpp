#include <iostream>
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"

void Pawn::GeneratePossibleMoves()
{
	if (this->team == White) // 白方，向上走
	{
		Vector2i destination = position + moveDirs[0];
		if (board->PositionIsInBounds(destination)) {
			ChessPiece* target = board->GetPiece(destination);
			if (target == nullptr || target->GetTeam() != team)
			{
				allPossibleMoves.push_back(ChessMove(destination));
			}
		}
		if (!isMoved) // 還沒動過，可走兩格
		{
			destination = position + moveDirs[0] * 2;
			if (board->PositionIsInBounds(destination)) {
				ChessPiece* target = board->GetPiece(destination);
				if (target == nullptr || target->GetTeam() != team)
				{
					allPossibleMoves.push_back(ChessMove(destination));
				}
			}
		}
	}
	else // 黑方，向下走
	{
		Vector2i destination = position + moveDirs[1];
		if (board->PositionIsInBounds(destination)) {
			ChessPiece* target = board->GetPiece(destination);
			if (target == nullptr || target->GetTeam() != team)
			{
				allPossibleMoves.push_back(ChessMove(destination));
			}
		}
		if (!isMoved) // 還沒動過，可走兩格
		{
			destination = position + moveDirs[1] * 2;
			if (board->PositionIsInBounds(destination)) {
				ChessPiece* target = board->GetPiece(destination);
				if (target == nullptr || target->GetTeam() != team)
				{
					allPossibleMoves.push_back(ChessMove(destination));
				}
			}
		}
	}
}
void Pawn::Promote()
{
	std::cout << "選擇要升變成的棋子:\n1.皇后\n2.主教\n3.城堡\n4.騎士" << std::endl;
	int choice;
	std::cin >> choice;
	if (choice == 1) {
		Queen(board, this->position, this->team);
	}
	else if (choice == 2) {
		Bishop(board, this->position, this->team);
	}
	else if (choice == 3) {
		Rook(board, this->position, this->team);
	}
	else if (choice == 4) {
		Knight(board, this->position, this->team);
	}
	delete this;
}

Pawn::Pawn(GameBoard* board, const Vector2i& position, const Team& team)
	: ChessPiece(board, position, team, "Pawn")
{
}


