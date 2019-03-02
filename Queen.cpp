#pragma once
#include "Chess.h"
#include"Piece.h"
#include"Bishop.cpp"
#include"Rook.cpp"
#include <iostream>
using namespace std;

class Queen : public Bishop, public Rook // Virtual Inheritance from Bishoop and Rook
{

public:

	Queen(bool c) : Piece(c, 5)
	{
		PieceImage.setTextureRect(IntRect(ImageSize * 4, ExtractColor(color) * ImageSize, ImageSize, ImageSize));
	}

	bool isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8])
	{
		if (Piece::isValid(xfrom, yfrom, xto, yto, b))
			if (Bishop::isValid(xfrom, yfrom, xto, yto, b) || Rook::isValid(xfrom, yfrom, xto, yto, b))
				return true;

		return false;
	}

	void Print(int x, int y)
	{
		PieceImage.setPosition(ImageSize*x, ImageSize*y);
		cout << (color ? 'W' : 'B') << 'Q';
	}
};