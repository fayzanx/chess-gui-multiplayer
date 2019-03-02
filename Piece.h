#pragma once
#include "Chess.h"
#include <iostream>
#include<SFML/Graphics.hpp> //Graphics library
using namespace sf;
using namespace std;
const int ImageSize = 56; // For graphics console

int ExtractColor(int color);


class Piece // abstact base class whose pointer is to be created
{
protected:
	int move;// For cheking whether the piece has moved or not 
	bool color;//1 for white 0 for black
	int value;//0 for space , 1 for pawn , 2 for knigth ,3 for bishop, 4 for rook, 5 for queen, 6 for king

public:
	Texture AllPiece;
	Sprite PieceImage;
	virtual bool isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8]); // Every derived class has its own unique function
	virtual void Print(int x, int y) = 0;//Virtual funtion for printing each piece
	Piece(bool c, int);
	Piece(int);
	Piece();
	bool getColor();
	int getValue();
    int getmove();
	void incrementMove();
	void decrementMove();
	~Piece();
};

//int ExtractImage(int value)
//{
//	switch (value)
//	{
//	case 1:
//		return 5;
//		break;
//
//	case 2:
//		return 1;
//		break;
//
//	case 3:
//		return 2;
//		break;
//
//	case 4:
//		return 0;
//		break;
//
//	case 5:
//		return 4;
//		break;
//
//	case 6:
//		return 3;
//		break;
//
//	default:
//		break;
//	}
//}

