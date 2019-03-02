#pragma once
#include "Chess.h"
#include"Piece.h"
#include <iostream>
#include<SFML/Graphics.hpp> //Graphics library
using namespace std;
using namespace sf;



class Bishop : virtual public Piece
{
public:
	Bishop(bool c) : Piece(c, 3)
	{
		PieceImage.setTextureRect(IntRect(ImageSize * 2, ExtractColor(color) * ImageSize, ImageSize, ImageSize));
	}
	Bishop()
	{
	}
	bool isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8])
	{
		if (Piece::isValid(xfrom, yfrom, xto, yto, b))
		{

			if (xfrom - xto == yfrom - yto || xfrom - xto == yto - yfrom)// Slope = 1 or -1
			{

				int row_change = (xfrom < xto ? 1 : -1);
				int col_change = (yfrom < yto ? 1 : -1);

				for (int i = xfrom + row_change, j = yfrom + col_change; j != yto && i != xto; i += row_change, j += col_change)
				{

					if (b[j][i]->getValue() != 0)
					{
						return false;
					}
				}

				return true;
			}
		}
		return false;
	}

	void Print(int x, int y)
	{
		PieceImage.setPosition(ImageSize*x, ImageSize*y);
		cout << (color ? 'W' : 'B') << 'B';
	}
};