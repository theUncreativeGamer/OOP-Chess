#include <iostream>
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"

void Pawn::GeneratePossibleMoves()
{
	if (this->team == White) // �դ�A�V�W��
	{
		Vector2i destination = position + moveDirs[0];
		if (board->PositionIsInBounds(destination)) {
			ChessPiece* target = board->GetPiece(destination);
			if (target == nullptr || target->GetTeam() != team)
			{
				allPossibleMoves.push_back(ChessMove(destination));
			}
		}
		if (!hasMoved) // �٨S�ʹL�A�i�����
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
	else // �¤�A�V�U��
	{
		Vector2i destination = position + moveDirs[1];
		if (board->PositionIsInBounds(destination)) {
			ChessPiece* target = board->GetPiece(destination);
			if (target == nullptr || target->GetTeam() != team)
			{
				allPossibleMoves.push_back(ChessMove(destination));
			}
		}
		if (!hasMoved) // �٨S�ʹL�A�i�����
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
	std::cout << "��ܭn���ܦ����Ѥl:\n1.�ӦZ\n2.�D��\n3.����\n4.�M�h" << std::endl;
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
	: ChessPiece(board, position, team)
{
}

const std::string Pawn::type = "Pawn";

const std::string& Pawn::GetType()
{
	// TODO: �󦹳B���J return ���z��
}


