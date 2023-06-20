#include "King.h"
#include "Rook.h"

const Vector2i King::moveDirs[8] =
{
	Vector2i(1,  1),
	Vector2i(1,  0),
	Vector2i(1,  -1),
	Vector2i(0,  1),
	Vector2i(0,  -1),
	Vector2i(-1, 1),
	Vector2i(-1, 0),
	Vector2i(-1, -1)
};

void King::GeneratePossibleMoves()
{
	for (int i = 0; i < 8; i++)
	{
		Vector2i moveDestination = position + moveDirs[i];
		if (!moveDestination.InBounds()) continue;

		ChessPiece* target = board->GetPiece(moveDestination);
		if (target == nullptr || target->GetTeam() != team)
		{
			AddCommonMove(moveDestination);
		}
	}
	if (isMoved)
		return;
	if (team == Team::White)
	{
		ChessPiece* wqr = board->GetPiece({ 0,0 });
		if (wqr != nullptr && wqr->GetTeam() == Team::White && wqr->GetType() == Rook::type)
		{
			allPossibleMoves.emplace_back(std::make_unique<CastlingMove>(CastlingMove(Vector2i(2, 0), board, dynamic_cast<ChessPiece*>(this), *wqr, true)));
			//allPossibleMoves.back()->DoSpecialThing();
		}
		ChessPiece* wkr = board->GetPiece({ 7,0 });
		if (wkr != nullptr && wkr->GetTeam() == Team::White && wkr->GetType() == Rook::type)
		{
			allPossibleMoves.emplace_back(std::make_unique<CastlingMove>(CastlingMove(Vector2i(6, 0), board, dynamic_cast<ChessPiece*>(this), *wkr, true)));
		}
	}
	else if (team == Team::Black)
	{
		ChessPiece* bqr = board->GetPiece({ 0,7 });
		if (bqr != nullptr && bqr->GetTeam() == Team::Black && bqr->GetType() == Rook::type)
		{
			allPossibleMoves.emplace_back(std::make_unique<CastlingMove>(CastlingMove(Vector2i(2, 7), board, dynamic_cast<ChessPiece*>(this), *bqr, true)));
		}
		ChessPiece* bkr = board->GetPiece({ 7,7 });
		if (bkr != nullptr && bkr->GetTeam() == Team::Black && bkr->GetType() == Rook::type)
		{
			allPossibleMoves.emplace_back(std::make_unique<CastlingMove>(CastlingMove(Vector2i(6, 7), board, dynamic_cast<ChessPiece*>(this), *bkr, true)));
		}
	}
}

King::King(const Vector2i& position, const Team& team, GameBoard* board)
	: ChessPiece(position, team, board)
{
}

const std::string King::type = "¤ý";

const std::string& King::GetType() const
{
	return type;
}

King* King::clone(GameBoard* anotherBoard) const
{
	King* result = new King(position, team, anotherBoard);
	result->isMoved = isMoved;
	return result;
}

CastlingMove::CastlingMove(const Vector2i& moveDestination, GameBoard* board, ChessPiece* piece, ChessPiece& targetRook, const bool& isQueenSide)
	: ChessMove(moveDestination, board, piece), targetRook(targetRook), isQueenSide(isQueenSide)
{
}

bool CastlingMove::DoSpecialThing()
{
	if (isQueenSide)
	{
		targetRook.MoveTo({ moveDestination.x - 1,moveDestination.y });
	}
	else
	{
		targetRook.MoveTo({ moveDestination.x - 1,moveDestination.y });
	}
	return true;
}

CastlingMove* CastlingMove::clone()
{
	return new CastlingMove(moveDestination, board, piece, targetRook, isQueenSide);
}
