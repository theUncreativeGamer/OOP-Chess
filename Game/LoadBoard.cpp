#include "GameBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <sstream>
#include <iostream>
#include <stdexcept>



static inline bool ReadNextCharacter(std::stringstream& input, char& nextChar, int& index)
{
	if (!(input >> nextChar))return false;
	index++;
	return true;
}

static inline void IgnoreNextCharacter(std::stringstream& input, int& index)
{
	input.ignore();
	index++;
}

static inline void PrintErrorMessage(const std::string& fen, const int& index)
{
	std::cout << "Failed to load board state with this code: " << fen << std::endl;
	std::cout << "Something went wrong when trying to read the " << index << "th character" << std::endl;
}

// Load the board state form FEN code.
bool LoadBoard(GameBoard& board, const std::string& fen)
{
	board.Clear();

	std::stringstream input(fen);
	input >> std::noskipws; // don't skip whitespace
	char nextChar = '\0';
	int index = 0;

	// 步驟1 將棋子放在對應的位置上
	Vector2i nextPiecePosition(0, 7);
	while (ReadNextCharacter(input,nextChar,index))
	{
		// 進入下一個步驟
		if (nextChar == ' ')
		{
			break;
		}

		// 切換到下一行
		if (nextChar == '/')
		{
			nextPiecePosition.y -= 1;
			nextPiecePosition.x = 0;
			continue;
		}

		// 保留空格
		if (nextChar >= '1' && nextChar <= '8')
		{
			nextPiecePosition.x += (nextChar - '0');
			continue;
		}

		// 格式錯誤
		if (nextPiecePosition.x > 8 || nextPiecePosition.y < 0)
		{
			PrintErrorMessage(fen, index);
			return false;
		}

		ChessPiece* tempPiece;
		// 生成棋子
		switch (nextChar)
		{
		case 'P':
			// 白色 小兵
			tempPiece = board.AddPiece(Pawn::type, nextPiecePosition, Team::White);
			if (nextPiecePosition.y != 1)tempPiece->isMoved = true;
			break;
		case 'R':
			// 白色 城堡
			board.AddPiece(Rook::type, nextPiecePosition, Team::White);
			break;
		case 'N':
			// 白色 騎士
			board.AddPiece(Knight::type, nextPiecePosition, Team::White);
			break;
		case 'B':
			// 白色 主教
			board.AddPiece(Bishop::type, nextPiecePosition, Team::White);
			break;
		case 'Q':
			// 白色 皇后
			board.AddPiece(Queen::type, nextPiecePosition, Team::White);
			break;
		case 'K':
			// 白色 國王
			board.AddPiece(King::type, nextPiecePosition, Team::White);
			break;
		case 'p':
			// 黑色 小兵
			tempPiece = board.AddPiece(Pawn::type, nextPiecePosition, Team::Black);
			if (nextPiecePosition.y != 6)tempPiece->isMoved = true;
			break;
		case 'r':
			// 黑色 城堡
			board.AddPiece(Rook::type, nextPiecePosition, Team::Black);
			break;
		case 'n':
			// 黑色 騎士
			board.AddPiece(Knight::type, nextPiecePosition, Team::Black);
			break;
		case 'b':
			// 黑色 主教
			board.AddPiece(Bishop::type, nextPiecePosition, Team::Black);
			break;
		case 'q':
			// 黑色 皇后
			board.AddPiece(Queen::type, nextPiecePosition, Team::Black);
			break;
		case 'k':
			// 黑色 國王
			board.AddPiece(King::type, nextPiecePosition, Team::Black);
			break;
		default:
			PrintErrorMessage(fen, index);
			return false;
		}
		/*
		cout << "生成了一個" << chess.back()->getType() << "號在位置"
			<< "(" << chess.back()->getPos().x << "," << chess.back()->getPos().y << ")\n";
		*/
		nextPiecePosition.x += 1;
	}

	// 步驟2 決定當前為哪一個玩家的回合
	{
		ReadNextCharacter(input,nextChar,index);
		switch (nextChar)
		{
		case 'b':
			board.currentPlayer = Team::Black;
			break;
		case 'w':
			board.currentPlayer = Team::White;
			break;
		default:
			PrintErrorMessage(fen, index);
			return false;
		}
		IgnoreNextCharacter(input, index);
	}


	// 步驟3 決定入堡權限
	{
		ChessPiece* wqr = board.GetPiece({ 0,0 }); // 白色 靠近皇后的 城堡
		ChessPiece* wkr = board.GetPiece({ 7,0 }); // 白色 靠近國王的 城堡
		ChessPiece* bqr = board.GetPiece({ 0,7 }); // 黑色 靠近皇后的 城堡
		ChessPiece* bkr = board.GetPiece({ 7,7 }); // 黑色 靠近國王的 城堡

		// 若找到的棋子不是對應顏色的城堡則忽略
		if (wqr != nullptr && (!(wqr->GetType() == Rook::type) || !(wqr->team == Team::White)))
			wqr = nullptr;
		if (wkr != nullptr && (!(wkr->GetType() == Rook::type) || !(wkr->team == Team::White)))
			wkr = nullptr;
		if (bqr != nullptr && (!(bqr->GetType() == Rook::type) || !(bqr->team == Team::Black)))
			bqr = nullptr;
		if (bkr != nullptr && (!(bkr->GetType() == Rook::type) || !(bkr->team == Team::Black)))
			bkr = nullptr;

		// 將找到的城堡設為「已經移動過」（即「無法入堡」）
		if (wqr != nullptr) wqr->isMoved = true;
		if (wkr != nullptr) wkr->isMoved = true;
		if (bqr != nullptr) bqr->isMoved = true;
		if (bkr != nullptr) bkr->isMoved = true;

		// 把對應的城堡設為「可以」
		for (bool endLoop = false; ReadNextCharacter(input,nextChar,index);)
		{
			switch (nextChar)
			{
			case ' ':
			case '-':
				endLoop = true;
				break;
			case 'Q':
				if (wqr != nullptr) wqr->isMoved = false;
				break;
			case 'K':
				if (wkr != nullptr) wkr->isMoved = false;
				break;
			case 'q':
				if (bqr != nullptr) bqr->isMoved = false;
				break;
			case 'k':
				if (bkr != nullptr) bkr->isMoved = false;
				break;
			default:
				PrintErrorMessage(fen, index);
				return false;
			}
			if (endLoop) break;
		}

		if (input.peek() == ' ')IgnoreNextCharacter(input, index);
	}

	// 步驟4 決定En Passent權限
	ReadNextCharacter(input,nextChar,index);
	if (nextChar != '-')
	{
		char tempChar;
		input >> tempChar;
		if (nextChar < 'a' || nextChar>'h' || !(tempChar == '3' || tempChar == '6'))
		{
			PrintErrorMessage(fen, index);
			return false;
		}
		Vector2i enPassentPosition(nextChar - 'a', tempChar - '1');
		if (enPassentPosition.y == 2) enPassentPosition.y += 1;
		else enPassentPosition.y -= 1;
		board.eppp = enPassentPosition;
	}
	if (input.peek() == ' ')
		IgnoreNextCharacter(input, index);

	// 步驟5 載入Halfmove次數
	std::string halfmoveCountText = "";
	while (ReadNextCharacter(input, nextChar, index))
	{
		if (nextChar == ' ') break;
		halfmoveCountText += nextChar;
	}
	int halfmoveCount;
	try
	{
		halfmoveCount = std::stoi(halfmoveCountText);
	}
	catch (const std::invalid_argument&)
	{
		PrintErrorMessage(fen, index);
		return false;
	}
	board.halfmoveClock = halfmoveCount;

	// 步驟6 載入當前回合數
	std::string currRoundText = "";
	while (ReadNextCharacter(input, nextChar, index))
	{
		if (nextChar == ' ') break;
		currRoundText += nextChar;
	}
	int currRound;
	try
	{
		currRound = std::stoi(currRoundText);
	}
	catch (const std::invalid_argument&)
	{
		PrintErrorMessage(fen, index);
		return false;
	}
	board.currentRound = currRound;

	return true;
}

static inline char GetPieceTypeAsSingleChar(const ChessPiece* piece)
{
	std::string type = piece->GetType();
	Team team = piece->GetTeam();
	
	if (team == Team::White)
	{
		if (type == Pawn::type)
		{
			return 'P';
		}
		else if (type == Rook::type)
		{
			return 'R';
		}
		else if(type == Knight::type)
		{
			return 'N';
		}
		else if(type == Bishop::type)
		{
			return 'B';
		}
		else if(type == Queen::type)
		{
			return 'Q';
		}
		else if(type == King::type)
		{
			return 'K';
		}
		
	}
	else if (team == Team::Black)
	{
		if (type == Pawn::type)
		{
			return 'p';
		}
		else if (type == Rook::type)
		{
			return 'r';
		}
		else if (type == Knight::type)
		{
			return 'n';
		}
		else if (type == Bishop::type)
		{
			return 'b';
		}
		else if (type == Queen::type)
		{
			return 'q';
		}
		else if (type == King::type)
		{
			return 'k';
		}
	}
	else
	{
		return '?';
	}
}

// Save the current board state as a FEN code and return as a string.
// Return empty string if something went wrong.
std::string SaveBoardAsFEN(const GameBoard& board)
{
	if (board.width != 8 || board.height != 8)return "";
	std::string result = "";

	// 步驟1 將棋子放在對應的位置上
	{
		int emptySpaceCount = 0;
		for (int y = 7; y >= 0; y--)
		{
			for (int x = 0; x < 8; x++)
			{
				const ChessPiece* curr = board.GetPiece(Vector2i(x, y));
				if (curr == nullptr)
					emptySpaceCount++;
				else
				{
					if (emptySpaceCount != 0)
					{
						result += std::to_string(emptySpaceCount);
						emptySpaceCount = 0;
					}
					result += GetPieceTypeAsSingleChar(curr);
				}
			}
			if (emptySpaceCount != 0)
			{
				result += std::to_string(emptySpaceCount);
				emptySpaceCount = 0;
			}
			if (y > 0)result += '/';
		}
	}
	result += " ";
	// 步驟2 決定當前為哪一個玩家的回合
	{
		if (board.currentPlayer == Team::Black)
			result += "b";
		else if (board.currentPlayer == Team::White)
			result += "w";
		else
			return "";
	}
	result += " ";
	// 步驟3 決定入堡權限
	{
		const ChessPiece* whiteKing = board.GetPiece({ 4,0 });
		const ChessPiece* blackKing = board.GetPiece({ 4,7 });
		const ChessPiece* wqr = board.GetPiece({ 0,0 }); // 白色 靠近皇后的 城堡
		const ChessPiece* wkr = board.GetPiece({ 7,0 }); // 白色 靠近國王的 城堡
		const ChessPiece* bqr = board.GetPiece({ 0,7 }); // 黑色 靠近皇后的 城堡
		const ChessPiece* bkr = board.GetPiece({ 7,7 }); // 黑色 靠近國王的 城堡

		bool wq = false, wk = false, bq = false, bk = false;
		if (whiteKing != nullptr && whiteKing->GetType() == King::type && whiteKing->GetTeam() == Team::White)
		{
			if (wqr != nullptr && wqr->GetType() == Rook::type && wqr->GetTeam() == Team::White)
			{
				wq = true;
			}
			if (wkr != nullptr && wkr->GetType() == Rook::type && wkr->GetTeam() == Team::White)
			{
				wk = true;
			}
		}
		if (blackKing != nullptr && blackKing->GetType() == King::type && blackKing->GetTeam() == Team::Black)
		{
			if (bqr != nullptr && bqr->GetType() == Rook::type && bqr->GetTeam() == Team::Black)
			{
				bq = true;
			}
			if (bkr != nullptr && bkr->GetType() == Rook::type && bkr->GetTeam() == Team::Black)
			{
				bk = true;
			}
		}

		std::string concantenation = "";
		if (wk)concantenation += "K";
		if (wq)concantenation += "Q";
		if (bk)concantenation += "k";
		if (bq)concantenation += "q";

		if (concantenation == "")concantenation = "-";
		result += concantenation;
	}
	result += " ";
	// 步驟4 決定En Passent權限
	{
		Vector2i enPass = board.eppp;
		if (board.PositionIsInBounds(enPass))
		{
			if (enPass.y <= 3)enPass.y--;
			else enPass.y++;

			result += 'a' + enPass.x;
			result += '1' + enPass.y;
		}
		else
		{
			result += "-";
		}

	}
	result += " ";
	// 步驟5 Halfmove次數
	result += std::to_string(board.halfmoveClock);
	result += " ";
	// 步驟6 當前回合數
	result += std::to_string(board.currentRound);

	return result;
}
