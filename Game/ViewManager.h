#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include "Vector2i.h"
class GameBoard;
class ChessPiece;
enum Team;

class ViewManager {
public:
	// ��e�ϥΪ�ViewManager
	static std::unique_ptr<ViewManager> instance;
	//��ܴѽL
	virtual void ShowBoard(const GameBoard& board, bool check = false) = 0;
	// ���o���a��ܪ���m�A�άO�{��Τ���C�����ﶵ
	virtual std::string GetNormalInput() = 0;
	//��ܤ@�ӴѤl���i���ʽd��
	virtual std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece) = 0;
	//Promote����ܪ��e��
	virtual std::string ShowPromoteBoard(const GameBoard& board, ChessPiece* piece) = 0;
	// �C���������e��
	virtual void ShowEndScreen(const Team& winner, const bool& isStopped) = 0;

};

class ConsoleView 
	: public ViewManager
{
public:
	//��ܴѽL
	void ShowBoard(const GameBoard& board, bool check = false) override;
	// ���o���a��ܪ���m�A�άO�{��Τ���C�����ﶵ
	std::string GetNormalInput() override;
	//��ܤ@�ӴѤl���i���ʽd��
	std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece) override;
	//Promote����ܪ��e��
	std::string ShowPromoteBoard(const GameBoard& board, ChessPiece* piece) override;
	// �C���������e��
	void ShowEndScreen(const Team& winner, const bool& isStopped) override;

private:
	std::ostream& output = std::cout;
	std::istream& input = std::cin;

	//�]�w��X�C�� 111�զr���� 143�զr�ǩ� 96�¦r���� 128�¦r�ǩ� 192�¦r���� 207�զr���� 236���r����
	// 7 �զr�©�
	void SetColor(int color = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
};


