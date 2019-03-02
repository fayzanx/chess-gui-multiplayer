#pragma once
#include "Chess.h"
#include "Blank.cpp"
#include"Piece.h"
#include <iostream>
using namespace std;

class King :public Piece
{
public:
	King(bool c) : Piece(c, 6) // Moves are set to zero when a piece is constructed
	{
		PieceImage.setTextureRect(IntRect(ImageSize * 3, ExtractColor(color) * ImageSize, ImageSize, ImageSize));
	}
	bool isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8])
	{
		if (Piece::isValid(xfrom, yfrom, xto, yto, b))
			if ((abs(yfrom - yto) == 1 && abs(xfrom - xto) == 0) || (abs(yfrom - yto) == 0 && abs(xfrom - xto) == 1) || abs(xfrom - xto) == 1 && abs(yfrom - yto) == 1)
			{
				move = true; // The piece has moved so castling is not possible
				return true;
			}
		return false;
	}
	void Print(int x, int y)
	{
		PieceImage.setPosition(ImageSize*x, ImageSize*y);
		cout << (color ? 'W' : 'B') << 'K';
	}

};