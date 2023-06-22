#include <iostream>
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "ViewManager.h"

void Pawn::GeneratePossibleMoves()
{
	Vector2i forward = team == White ? Vector2i(0, 1) : Vector2i(0, -1);

	Vector2i moveDestination = position + forward;
	if (board->PositionIsInBounds(moveDestination)) {
		ChessPiece* target = board->GetPiece(moveDestination);
		if (target == nullptr || target->GetTeam() != team)
		{
			allPossibleMoves.push_back(std::make_unique<PawnMove>(PawnMove(moveDestination, board, this, false)));
		}
	}
	if (!isMoved) // 還沒動過，可走兩格
	{
		moveDestination = position + forward * 2;
		if (board->PositionIsInBounds(moveDestination)) {
			ChessPiece* target = board->GetPiece(moveDestination);
			if (target == nullptr || target->GetTeam() != team)
			{
				allPossibleMoves.push_back(std::make_unique<PawnMove>(PawnMove(moveDestination, board, this, true)));
			}
		}
	}

	Vector2i left = position + Vector2i(-1, 0), right = position + Vector2i(1, 0);
	moveDestination = left + forward;

	if (board->PositionIsInBounds(moveDestination))
	{
		if (board->GetPiece(moveDestination) != nullptr && board->GetPiece(moveDestination)->GetTeam() != team)
		{
			allPossibleMoves.push_back(std::make_unique<PawnMove>(PawnMove(moveDestination, board, this, false)));
		}

		if (left == board->GetEPPP() && board->GetPiece(moveDestination) == nullptr)
		{
			allPossibleMoves.push_back(std::make_unique<EnPassentMove>(EnPassentMove(moveDestination, left, board, this)));
		}
	}
	

	moveDestination = right + forward;
	if (board->PositionIsInBounds(moveDestination))
	{
		if (board->GetPiece(moveDestination) != nullptr && board->GetPiece(moveDestination)->GetTeam() != team)
		{
			allPossibleMoves.push_back(std::make_unique<PawnMove>(PawnMove(moveDestination, board, this, false)));
		}

		if (right == board->GetEPPP() && board->GetPiece(moveDestination) == nullptr)
		{
			allPossibleMoves.push_back(std::make_unique<EnPassentMove>(EnPassentMove(moveDestination, right, board, this)));
		}
	}
}

/*
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
*/


Pawn::Pawn(const Vector2i& position, const Team& team, GameBoard* board)
	: ChessPiece(position, team, board)
{
}

const std::string Pawn::type = "兵";

const std::string& Pawn::GetType() const
{
	return type;
}

Pawn* Pawn::clone(GameBoard* anotherBoard) const
{
	Pawn* result = new Pawn(position, team, anotherBoard);
	result->isMoved = isMoved;
	return result;
}

EnPassentMove::EnPassentMove(const Vector2i& moveDestination, const Vector2i& attackTarget, GameBoard* board, ChessPiece* piece)
	: PawnMove(moveDestination, board, piece, false)
{
	this->attackTarget = attackTarget;
}

EnPassentMove* EnPassentMove::clone()
{
	return new EnPassentMove(moveDestination, attackTarget, board, piece);
}

PawnMove::PawnMove(const Vector2i& moveDestination, GameBoard* board, ChessPiece* piece, const bool& isFirstMove)
	: ChessMove(moveDestination, board, piece), isFirstMove(isFirstMove)
{
}

bool PawnMove::DoSpecialThing()
{
	if (isFirstMove)board->eppp = moveDestination;
	return true;
}

PawnMove* PawnMove::clone()
{
	return new PawnMove(moveDestination, board, piece, isFirstMove);
}
