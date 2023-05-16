#include "ChessPiece.h"
#include "GameBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>

const std::string defaultFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

int main()
{
	GameBoard board;
	board.AddPiece(Knight::type, { 0,0 }, Team::White);
	board.RemovePiece({ 0,0 });
	LoadBoard(board, defaultFEN);
}
