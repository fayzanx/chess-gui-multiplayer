#pragma once
#include "Chess.h"
#include"Piece.h"
#include <iostream>
using namespace std;

class Blank : public Piece
{
public:
	Blank() : Piece(0)
	{

	}
	void Print(int x, int y)
	{
		cout << "  ";
	}
};