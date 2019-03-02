#include "Chess.h"
#include"Piece.h"
#include <iostream>
using namespace std;

Piece::Piece(bool c, int v) : color(c), value(v)
{
	
	AllPiece.loadFromFile("images/figures.png");// To load the image of the piece
	PieceImage.setTexture(AllPiece);
	move = 0;
}

Piece::Piece(int v) : value(0) // For blank object
{
	move = false;
}

Piece::Piece()
{
	move = false;
}

Piece::~Piece()
{
	
}

bool Piece::isValid(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8]) // For checking whether it is valid or invalid move
{


	// If the destination is empty or it does not contain piece of same color(logic of exclusive OR gate)

	if ((b[yto][xto]->value == 0) || (((!(b[yto][xto]->color)) && b[yfrom][xfrom]->color) || (b[yto][xto]->color && (!(b[yfrom][xfrom]->color)))))
	{
		move = true;
		return true;
	}
	else
	{
		//cout << "\nIn base invalid funtion";
		return false;
	}
}

bool Piece::getColor()
{
	return color;
}

int Piece::getValue()
{
	return value;
}

int ExtractColor(int color)
{
	{
		if (color)
			return 0;
		else
			return 1;
	}
}

int Piece::getmove()
{
	return move;
}

void Piece::decrementMove()
{
	move--;
}

void Piece::incrementMove()
{
	move++;
}



