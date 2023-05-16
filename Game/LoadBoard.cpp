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
	std::stringstream input(fen);
	input >> std::noskipws; // don't skip whitespace
	char nextChar = '\0';
	int index = 0;

	// �B�J1 �N�Ѥl��b��������m�W
	Vector2i nextPiecePosition(0, 0);
	while (ReadNextCharacter(input,nextChar,index))
	{
		// �i�J�U�@�ӨB�J
		if (nextChar == ' ')
		{
			break;
		}

		// ������U�@��
		if (nextChar == '/')
		{
			nextPiecePosition.y += 1;
			nextPiecePosition.x = 0;
			continue;
		}

		// �O�d�Ů�
		if (nextChar >= '1' && nextChar <= '8')
		{
			nextPiecePosition.x += (nextChar - '0');
			continue;
		}

		// �榡���~
		if (nextPiecePosition.x > 8 || nextPiecePosition.y > 8)
		{
			PrintErrorMessage(fen, index);
			return false;
		}

		// �ͦ��Ѥl
		switch (nextChar)
		{
		case 'P':
			// �զ� �p�L
			board.AddPiece(Pawn::type, nextPiecePosition, Team::White);
			break;
		case 'R':
			// �զ� ����
			board.AddPiece(Rook::type, nextPiecePosition, Team::White);
			break;
		case 'N':
			// �զ� �M�h
			board.AddPiece(Knight::type, nextPiecePosition, Team::White);
			break;
		case 'B':
			// �զ� �D��
			board.AddPiece(Bishop::type, nextPiecePosition, Team::White);
			break;
		case 'Q':
			// �զ� �ӦZ
			board.AddPiece(Queen::type, nextPiecePosition, Team::White);
			break;
		case 'K':
			// �զ� ���
			board.AddPiece(King::type, nextPiecePosition, Team::White);
			break;
		case 'p':
			// �¦� �p�L
			board.AddPiece(Pawn::type, nextPiecePosition, Team::Black);
			break;
		case 'r':
			// �¦� ����
			board.AddPiece(Pawn::type, nextPiecePosition, Team::Black);
			break;
		case 'n':
			// �¦� �M�h
			board.AddPiece(Pawn::type, nextPiecePosition, Team::Black);
			break;
		case 'b':
			// �¦� �D��
			board.AddPiece(Pawn::type, nextPiecePosition, Team::Black);
			break;
		case 'q':
			// �¦� �ӦZ
			board.AddPiece(Pawn::type, nextPiecePosition, Team::Black);
			break;
		case 'k':
			// �¦� ���
			board.AddPiece(Pawn::type, nextPiecePosition, Team::Black);
			break;
		default:
			PrintErrorMessage(fen, index);
			return false;
		}
		/*
		cout << "�ͦ��F�@��" << chess.back()->getType() << "���b��m"
			<< "(" << chess.back()->getPos().x << "," << chess.back()->getPos().y << ")\n";
		*/
		nextPiecePosition.x += 1;
	}

	// �B�J2 �M�w��e�����@�Ӫ��a���^�X
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


	// �B�J3 �M�w�J���v��
	{
		ChessPiece* wqr = board.GetPiece({ 0,0 }); // �զ� �a��ӦZ�� ����
		ChessPiece* wkr = board.GetPiece({ 7,0 }); // �զ� �a������ ����
		ChessPiece* bqr = board.GetPiece({ 0,7 }); // �¦� �a��ӦZ�� ����
		ChessPiece* bkr = board.GetPiece({ 7,7 }); // �¦� �a������ ����

		// �Y��쪺�Ѥl���O�����C�⪺�����h����
		if (wqr != nullptr && (!(wqr->GetType() == Rook::type) || !(wqr->team == Team::White)))
			wqr = nullptr;
		if (wkr != nullptr && (!(wkr->GetType() == Rook::type) || !(wkr->team == Team::White)))
			wkr = nullptr;
		if (bqr != nullptr && (!(bqr->GetType() == Rook::type) || !(bqr->team == Team::Black)))
			bqr = nullptr;
		if (bkr != nullptr && (!(bkr->GetType() == Rook::type) || !(bkr->team == Team::Black)))
			bkr = nullptr;

		// �N��쪺�����]���u�w�g���ʹL�v�]�Y�u�L�k�J���v�^
		if (wqr != nullptr) wqr->isMoved = true;
		if (wkr != nullptr) wkr->isMoved = true;
		if (bqr != nullptr) bqr->isMoved = true;
		if (bkr != nullptr) bkr->isMoved = true;

		// ������������]���u�i�H�v
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

	// �B�J4 �M�wEn Passent�v��
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

	// �B�J5 ���JHalfmove����
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
	catch (const std::invalid_argument& e)
	{
		PrintErrorMessage(fen, index);
		return false;
	}
	board.halfmoveClock = halfmoveCount;

	// �B�J6 ���J��e�^�X��
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
	catch (const std::invalid_argument& e)
	{
		PrintErrorMessage(fen, index);
		return false;
	}
	board.currentRound = currRound;

	return true;
}
