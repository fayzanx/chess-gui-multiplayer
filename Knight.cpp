#pragma once
#include "Chess.h"
#include"Piece.h"
#include <iostream>
#include <cmath>
using namespace std;

class Knight : public Piece
{
public:
	Knight(bool c) : Piece(c, 2) // c indicates whether it is black or white while 2 indicate value of knight
	{
		PieceImage.setTextureRect(IntRect(ImageSize * 1, ExtractColor(color) * ImageSize, ImageSize, ImageSize));
	}
	virtual bool isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8])
	{
		//	cout << "\nIN KINGHT" << b[yfrom][xfrom]->getColor();
		if ((abs(xfrom - xto) == 2 && abs(yfrom - yto) == 1) || (abs(xfrom - xto) == 1 && abs(yfrom - yto) == 2) && Piece::isValid(xfrom, yfrom, xto, yto, b))
			return true;

		return false;
	}
	void Print(int x, int y)
	{
		PieceImage.setPosition(ImageSize*x, ImageSize*y);
		cout << (color ? 'W' : 'B') << 'N';
	}
};

