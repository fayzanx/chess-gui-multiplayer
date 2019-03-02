#pragma once
#include "Chess.h"
#include"Piece.h"
#include <iostream>
using namespace std;

class Pawn : public Piece
{
public:

	Pawn(bool c) : Piece(c, 1)
	{
		PieceImage.setTextureRect(IntRect(ImageSize * 5, ExtractColor(color) * ImageSize, ImageSize, ImageSize));
	}

	bool isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8])
	{

		int compensate = (b[yfrom][xfrom]->getColor() ? 1 : -1); //  For compensating for black and white pawns (white pawns can only move forward in grid while black are opposite)
		if (xto - xfrom == 0 && Piece::isValid(xfrom, yfrom, xto, yto, b))
		{


			if (yto - yfrom == compensate)
			{
				if (b[yto][xto]->getValue() == 0) // For cheking if there is piece
				{
					return true;
				}
			}

			if (yto - yfrom == compensate * 2) // For checking whether it is first move
				if (yfrom == 6 && compensate == -1 || yfrom == 1 && compensate == 1)
					if (b[yto][xto]->getValue() == 0) // For cheking if there is piece
						return true;


		}

		if (yfrom - yto == xfrom - xto || yfrom - yto == xto - xfrom) // Pawns can kill in diagonal
		{
			if (yto - yfrom == compensate) // Pawn can only kill in forward diagonal
			{
				if (b[yto][xto]->getValue() != 0) // For cheking if there is piece
					return true;
			}
		}

		return false;
	}

	void Print(int x, int y)
	{
		PieceImage.setPosition(ImageSize*x, ImageSize*y);
		cout << (color ? 'W' : 'B') << 'P';
	}
};
