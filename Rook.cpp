#pragma once
#include "Chess.h"
#include"Piece.h"
#include <iostream>
using namespace std;

class Rook :virtual public Piece
{

public:
	Rook(bool c) : Piece(c, 4)  // Moves are set to zero when a piece is constructed
	{
		PieceImage.setTextureRect(IntRect(ImageSize * 0, ExtractColor(color) * ImageSize, ImageSize, ImageSize));
	}
	Rook() {};
	bool isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8])
	{
		if (Piece::isValid(xfrom, yfrom, xto, yto, b))
		{

			if (xto - xfrom == 0) // Move in a vertical line
			{

				int col_change = (yfrom < yto ? 1 : -1);
				// For moving forward in the board
				for (int i = yfrom + col_change; i != yto; i += col_change) // If there is no obstacle in the way
				{

					if (b[i][xfrom]->getValue() != 0)
					{
						return false;
					}
				}
				move = true; // The piece has moved so castling is not possible
				return true;
			}
			if (yto - yfrom == 0) // Move in a horizontal line
			{
				int row_change = (xfrom < xto ? 1 : -1);
				// For moving forward in the board
				for (int i = (xfrom)+row_change; i < (xto); i += row_change) // If there is no obstacle in the way
				{
					if (b[yfrom][i]->getValue() != 0)
					{
						return false;
					}
				}
				move = true; // The piece has moved so castling is not possible
				return true;
			}
		}
		return false;
	}

	void Print(int x, int y)
	{
		PieceImage.setPosition(ImageSize*x, ImageSize*y);
		cout << (color ? 'W' : 'B') << 'R';
	}

};