#pragma once
#include<iostream>
#include<vector>
#include<string>
#include "ChessPiece.h"
#include "King.h"
#include "Queen.h"
#include"Bishop.h"
#include"Knight.h"
#include"Rook.h"
#include"Pawn.h"
#include "GameBoard.h"
using namespace std;
enum Team;

class Player {
public:
	int team;
	King K;
	Queen Q;
	Bishop H[2];
	Knight N[2];
	Rook R[2];
	Pawn P[8];

	Player(Team T) {
		team = T;
		if (T) {
			int Y1 = 0, Y2 = 1;
			K.setPosition(Vector2i(4, Y1));
			K.setTeam(T);
			Q.setPosition(Vector2i(3, Y1));
			Q.setTeam(T);
			H[0].setPosition(Vector2i(2, Y1));
			H[0].setTeam(T);
			H[1].setPosition(Vector2i(5, Y1));
			H[1].setTeam(T);
			N[0].setPosition(Vector2i(6, Y1));
			N[0].setTeam(T);
			N[1].setPosition(Vector2i(1, Y1));
			N[1].setTeam(T);
			R[0].setPosition(Vector2i(7, Y1));
			R[0].setTeam(T);
			R[1].setPosition(Vector2i(0, Y1));
			R[1].setTeam(T);
			for (int i = 0; i < 8; ++i) {
				P[i].setPosition(Vector2i(i, Y2));
				P[i].setTeam(T);
			}
		}
		else {
			int Y1 = 7, Y2 = 6;
			K.setPosition(Vector2i(4, Y1));
			K.setTeam(T);
			Q.setPosition(Vector2i(3, Y1));
			Q.setTeam(T);
			H[0].setPosition(Vector2i(2, Y1));
			H[0].setTeam(T);
			H[1].setPosition(Vector2i(5, Y1));
			H[1].setTeam(T);
			N[0].setPosition(Vector2i(6, Y1));
			N[0].setTeam(T);
			N[1].setPosition(Vector2i(1, Y1));
			N[1].setTeam(T);
			R[0].setPosition(Vector2i(7, Y1));
			R[0].setTeam(T);
			R[1].setPosition(Vector2i(0, Y1));
			R[1].setTeam(T);
			for (int i = 0; i < 8; ++i) {
				P[i].setPosition(Vector2i(i, Y2));
				P[i].setTeam(T);
			}
		}
	}
	void MoveChess(string Type,Vector2i from,Vector2i to) {
		if (Type == "King") {
			K.GetAllPossibleMoves();
			
		}
	}
	void castling() {

	}



};