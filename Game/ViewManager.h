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
	//��ܴѽL
	void ShowBoard(const GameBoard& board, bool check = false);
	//��ܤ@�ӴѤl���i���ʽd��
	std::string ShowSelectedPiece(const GameBoard& board, ChessPiece* piece);
	//Promote����ܪ��e��
	void showPromoteBoard(const std::vector<ChessPiece*>& chess, int target);

private:
	std::ostream& output = std::cout;
	std::istream& input = std::cin;

	//�]�w��X�C�� 111�զr���� 143�զr�ǩ� 96�¦r���� 128�¦r�ǩ� 192�¦r���� 207�զr���� 236���r����
	// 7 �զr�©�
	void SetColor(int color);
};


