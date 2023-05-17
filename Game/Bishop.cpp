#include "Bishop.h"

const Vector2i Bishop::moveDirs[4]=
{
	{1,1},
	{-1,-1},
	{1,-1},
	{-1,1}
};
void Bishop::GeneratePossibleMoves() {
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 7; j++) {
			Vector2i destination = position + moveDirs[i] * j;
			if (!board->PositionIsInBounds(destination)) break; // 出界

			ChessPiece* target = board->GetPiece(destination);
			if (target == nullptr) // 空格
			{
				AddCommonMove(destination);
			}
			else if (target->GetTeam() != team) // 敵方棋子位置
			{
				AddCommonMove(destination);
				break;
			}
			else break; // 玩家棋子位置
		}
	}
}

Bishop::Bishop(const Vector2i& position, const Team& team, GameBoard* board) :
	ChessPiece(position, team, board)
{
}

const std::string Bishop::type = "教";

const std::string& Bishop::GetType() const
{
	return type;
}


