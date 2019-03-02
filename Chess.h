#pragma once
#include "Splash.h"
#include"Piece.h"
#include "Accounts.h"
#define PANEL_TXT_ELEM 4

class Chess
{
private:
	Piece* board[8][8];// The board on which the Chess is played using polymorphism
	bool  turn;// 0 for black turn 1 for white turn
	Piece* temp;
	bool isCheck;// For determining whether the player is in check or not
	bool GameOver;
	int posA[8][8];
	Database alldat;

	//mouse movement controllers
	int moveFromX;
	int moveFromY;
	int moveToX;
	int moveToY;
	bool mouse_move;
	userData allData[2];
public:
	RenderWindow window;
	Text info;

	Sprite boardImage;
	Sprite panel;
	Text panelText[PANEL_TXT_ELEM]; //number of text elements used
	Font fonts[2]; //list of fonts used
	
	Chess();
	void alternateTurn();// for alternating turns
	void Start();
	void Move();
	bool Check();
	bool isGameOver();
	int Result(); // For showing the results
	void PrintBoard();
	void Replace(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8]);
	bool Castling(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8]);
	~Chess();

	//GUI
	bool isInBound(int x, int y);
	void mouseOpDown(Vector2i* pos);
	void mouseOpRelease(Vector2i* posF);
	//void updateLoginData() {
		
	//}
	void updateText(int n = 0, string s = "x", int font = 0, int posX = 5, int posY = 507, int size = 20);
	void updString(int no, string s);
	void Move2(/*int fromI, int fromJ, int toI, int toJ ,Piece* c[8][8]*/);
	bool Check2(int fromI, int fromJ, int toI, int toJ);
	
};

