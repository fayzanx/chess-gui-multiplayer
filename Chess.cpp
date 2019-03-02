#include "Chess.h"
#include "Piece.h"

#include "Bishop.cpp"
#include "Rook.cpp"
#include "Pawn.cpp"
#include "Knight.cpp"
#include "Queen.cpp"
#include "King.cpp"
#include "Blank.cpp"
#include <Windows.h>
#include <iostream>
#include <string>
#include<SFML/Graphics.hpp> //Graphics library
using namespace sf;
using namespace std;

string txt = "Welcome";
Clock clock1;
#define WIN_TITLE "Chess"
#define WIN_ATTR (Style::None)
#define WIN_WID 505
#define WIN_HGT 555
#define OFFSET 25
bool splash_flag = false;

//Testing Boudaries
bool Chess::isInBound(int x, int y) {
	
	if ((x < 0 || x < 0) || (x >(WIN_WID - 2 * OFFSET) || y >(WIN_WID - 2 * OFFSET))) {
		//txt = "Invalid Coordinates";
		updateText(3, "INVALID", 1, 350, 515, 12);
		return false;

	}
	else {
		//txt = "Position : " + to_string(x) + " | " + to_string(y);
		updateText(3, "at " + to_string(x) + "," + to_string(y), 1, 350, 515, 12);
		return true;
	}
}

//Moving in GUI
bool Chess::Check2(int fromI, int fromJ, int toI, int toJ) {
	cout << txt;
	int xto, yto, xfrom, yfrom;
	bool isValidMove = false;
	bool returnval = false;

		//txt +=  " From: ";
		yfrom = fromI;	xfrom = fromJ;
		cout << "\n\nTurn " << turn << endl;
		cout << "\From " << (xfrom+1) << "," << (yfrom+1) << endl;

		xto = toI; 		yto = toJ;
		cout << "To   " << (xto+1) << "," << (yto+1) << endl;
		
			//For checking if is in bound
			if (xfrom >= 0 && xfrom <= 7 && yfrom >= 0 && yfrom <= 7 && xto >= 0 && xto <= 7 && yto >= 0 && yto <= 7)
			{
				if (board[yfrom][xfrom]->getColor() == turn)
				{
					if (board[yfrom][xfrom]->isValid(xfrom, yfrom, xto, yto, board))  // Virtually calls the invalid funtion
					{
						Replace(xfrom, yfrom, xto, yto, board); // For replacing the piece with space
						returnval = true;
						// For checking whether it is a check after the move
						isValidMove = !Check();
						if (!isValidMove)
						{
							returnval = false;
							board[yfrom][xfrom] = board[yto][xto];
							board[yto][xto] = temp; // For restoring the piece if move is invalid due to check
							board[yfrom][xfrom]->decrementMove();
	
						}
					}
					//Castling(xfrom, yfrom, xto, yto, board);
					else if (board[yfrom][xfrom]->getValue() == 6 && yfrom - yto == 0)
					{
						cout << "\nBefore Castiling";
						Sleep(500);
						isValidMove = Castling(xfrom, yfrom, xto, yto, board);
					}
				}
				else
					isValidMove = false;
			}
			if (!isValidMove)
			{
				returnval = false;
				txt = "Invalid Move!";
				panelText[0].setFillColor(sf::Color::Red);
				return returnval;
			}

		if (returnval) {
			txt = "DONE";
			panelText[0].setFillColor(sf::Color::White);
		}
		/*else {
			
		}*/

		return returnval;

}

void Chess::Move2(/*int fromI, int fromJ, int toI, int toJ ,Piece* c[8][8]*/) {
	
	//if (Check2(fromI, fromJ, toI, toJ)) {
		//if (fromI != toI || fromJ != toJ) {
			//board[toI][toJ] = board[fromI][fromJ];
			//board[fromI][fromJ] = new Blank();
		//}
	//}
	
	if (Check2(moveFromX, moveFromY, moveToX, moveToY)) {
		//cout << Check2(moveFromX, moveFromY, moveToX, moveToY, 1);
		alternateTurn();
		return;
	}
	
}

// Constructor
Chess::Chess() : turn(1), isCheck(false),//, window(VideoMode(505, 505), WIN_TITLE, WIN_ATTR) // White turn is first and there is no check at the start of the game
		moveFromX(0), moveFromY(0), moveToX(0), moveToY(0), mouse_move(false)
{
	//Welcome Screem
	Splash welcomeScreen;
	if (welcomeScreen.userLoggedIn)
		for (int i = 0; i < 2; i++) {
			allData[i] = welcomeScreen.getData(i);
			cout << endl << endl;
			cout << "side " << allData[i].side << endl;
			cout << "wins " << allData[i].wins << endl;
			cout << "mail " << allData[i].mail << endl;
			cout << "stalemates " << allData[i].stalemates << endl;
			cout << "index " << allData[i].index << endl;
			system("pause");
		}
	

	if (welcomeScreen.dead) {
		window.create(VideoMode(WIN_WID, WIN_HGT), WIN_TITLE, WIN_ATTR);
	}

	//initializing play screen
	Texture backgroundImage;
	backgroundImage.loadFromFile("images/board.png");
	boardImage.setTexture(backgroundImage);
	//initializing info panel
	Texture panelImage;
	panelImage.loadFromFile("images/info_back.png");
	panel.setTexture(panelImage);
	//fonts init
	fonts[1].loadFromFile("fonts/a_gc.ttf"); //default font
	fonts[0].loadFromFile("fonts/b_et.ttf"); //alternate font

	splash_flag = welcomeScreen.dead;

	// Allocation for white
	for (int i = 0; i < 8; i++)
	board[1][i] = new Pawn(1);
	board[0][7] = new Rook(1);
	board[0][0] = new Rook(1);
	board[0][6] = new Knight(1);
	board[0][1] = new Knight(1);
	board[0][5] = new Bishop(1);
	board[0][2] = new Bishop(1);
	board[0][4] = new Queen(1);
	board[0][3] = new King(1);

	// Allocation for black
	for (int i = 0; i < 8; i++)
	board[6][i] = new Pawn(0);

	board[7][7] = new Rook(0);
	board[7][0] = new Rook(0);
	board[7][6] = new Knight(0);
	board[7][1] = new Knight(0);
	board[7][5] = new Bishop(0);
	board[7][2] = new Bishop(0);
	board[7][4] = new Queen(0);
	board[7][3] = new King(0);

	//For initializing blank space
	for (int i = 2; i < 6; i++)
		for (int j = 0; j < 8; j++)
			board[i][j] = new Blank;

	// For starting new Chess
	Start();
}

// For changing turns
void Chess::alternateTurn()
{
	// If it was black's turn then white and vice versa
	turn = (turn ? false : true);
}

// For starting the game
void Chess::Start()
{
	bool evflag = true;
	//int k = 0;
	//float dy = 0, dx = 0;
	//Vector2f initialPos, finalPos;

	while(window.isOpen()) {
		
		do {
			
			Event ev;
			while (window.pollEvent(ev)) {
				
				PrintBoard();
				//if (isGameOver())
				//	break;

				//Move();
				//alternateTurn();
	

				///// MAIN EVENT HANDLER /////
				switch (ev.type) {
				case Event::Closed:
				case Event::Resized:
					window.close();
					evflag = false;
					break;
				//closing window in case it is resized or pressed X
				default:
					break;
				}

				if (evflag) {
					//k++;
					//if (k % 50 == 0) {
						string txturn = (turn ? "BROWN" : "WHITE");
						updateText(1, txturn, 1, 5, 530, 12);
						
						
					//}
					//mouse tracking
					Vector2i mousePos = Mouse::getPosition(window);
					//cout << mousePos.x << "," << mousePos.y << endl;
					mousePos.x -= OFFSET; //removing boundaries
					mousePos.y -= OFFSET;
					//cout << mousePos.x << "," << mousePos.y;
					bool a = isInBound(mousePos.x, mousePos.y);
						

						
					/////DRAG AND DROP MOVES//////////////////////////
					//when mouse is held
					if (ev.type == Event::MouseButtonPressed && ev.key.code == Mouse::Left){

						mouseOpDown(&mousePos);
						
					}
						

					//When mouse button is released
					if (ev.type == Event::MouseButtonReleased && ev.key.code == Mouse::Left) {

						mouseOpRelease(&mousePos);
						
					}
				}
				if (isGameOver())
				{
					break;
				}
			}
		} while (!GameOver);
		if (GameOver)
			break;
	} 

	std::system("cls");
	PrintBoard();
	Result();
	system("pause");
	exit(1);
}

void Chess::mouseOpDown(Vector2i* pos) {
	moveFromX = moveFromY = 0;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			if (board[i][j]->PieceImage.getGlobalBounds().contains(pos->x, pos->y))
			{
				mouse_move	= true;
				moveFromX	= i; 
				moveFromY	= j;
				//dx = mousePos.x - board[i][j]->PieceImage.getPosition().x;
				//dy = mousePos.y - board[i][j]->PieceImage.getPosition().y;
				//initialPos = board[i][j]->PieceImage.getPosition();
				cout << "\nMouse Down on (" << moveFromX << " , " << moveFromY << ")";

			}
		}
	}
}

void Chess::mouseOpRelease(Vector2i* posF) {
	moveToX = moveToY = 0;
	/*
	cout << "\nReleased at (" << moveFromX << " , " << moveFromY << ")";
	//Vector2f pos = board[m][n]->PieceImage.getPosition() + Vector2f(ImageSize / 2, ImageSize / 2);
	//finalPos = Vector2f(2+ ImageSize * int(pos.x / ImageSize), 2 + ImageSize * int(pos.y / ImageSize));
	//board[m][n]->PieceImage.setPosition(finalPos);
	//Vector2f posf = Vector2f(100, 100);
	//board[m][n]->PieceImage.setPosition(posf);
	cout << " at " << mousePos.x/ImageSize << "," << mousePos.y/ImageSize;
	//Vector2f posf = Vector2f(ImageSize * int(mousePos.x / ImageSize), ImageSize * int(mousePos.y / ImageSize));

	p = mousePos.y / ImageSize;
	q = mousePos.x / ImageSize;	*/

	moveToX = posF->x / ImageSize;
	moveToY = posF->y / ImageSize;

	if (splash_flag && mouse_move && isInBound(posF->x, posF->y)) {
		Move2();
		mouse_move = false;
		//return;
	}
	else {
		cout << "\nX" << endl;
	}
}

// For determining the winner or draw
int Chess::Result()
{
	if (isCheck == true)
	{
		cout << "\n\nThe game is won by: " << (!turn ? "White" : "Black") << endl;
		updString(1, "game won by" + turn);
		//system("pause");
		if (!turn)
			return 1;
		else
			return 0;
	}
	else
	{
		alldat.increment_stalemates(allData[0].index);
		alldat.increment_stalemates(allData[1].index);
		updString(0, "Stalemate");
		cout << "\n\nThe game results in stalemate" << endl;
	}
	if (!turn)
	{
		alldat.increment_wins(allData[0].index);
		alldat.increment_games_played(allData[0].index);
		alldat.increment_games_played(allData[1].index);
		updString(0, "Wins of " + allData[0].side + " increased");
	}
	else
	{
		alldat.increment_wins(allData[1].index);
		updString(0, "Wins of " + allData[1].side + " increased");
	}
}

void Chess::Move()
{
	char x, y;// For taking input in character
	int xto, yto, xfrom, yfrom;
	bool isValidMove = false;
	do
	{
		cout << "\n\n" << (turn ? "White's turn: " : "Black's turn: ");
		cout << "From: ";
		fflush(stdin); // For ignoring any garbage value
		cin >> y >> x;
		if (cin.eof() == true) // For checking if the user has entered EOF file
		{
			exit(1);
		}
		xfrom = x - 49; yfrom = y - 49; //In order to convert character to integer using ASCII code 
		cout << "To: ";
		cin >> y >> x;
		xto = x - 49; yto = y - 49; //In order to convert character to integer using ASCII code 
									// For cheking whether the piece lies on the board or not
		if (xfrom >= 0 && xfrom <= 7 && yfrom >= 0 && yfrom <= 7 && xto >= 0 && xto <= 7 && yto >= 0 && yto <= 7)
		{
			if (board[yfrom][xfrom]->getColor() == turn)
			{
				if (board[yfrom][xfrom]->isValid(xfrom, yfrom, xto, yto, board))  // Virtually calls the invalid funtion
				{
					Replace(xfrom, yfrom, xto, yto, board); // For replacing the piece with space
															// For checking whether it is a check after the move
					isValidMove = !Check();
					if (!isValidMove)
					{
						board[yfrom][xfrom] = board[yto][xto];
						board[yto][xto] = temp; // For restoring the piece if move is invalid due to check
						board[yfrom][xfrom]->decrementMove();
					}
				}
				else if (board[yfrom][xfrom]->getValue() == 6 /*&& board[yfrom][xfrom]->getmove() == 0*/ && yfrom - yto == 0)
				{
					isValidMove = Castling(xfrom, yfrom, xto, yto, board);
				}
			}


			else
				isValidMove = false;
		}
		if (!isValidMove)
		{
			cout << "\nInvalid Input!!";
		}
	} while (!isValidMove);

}

//For checking whether the player is in check
bool Chess::Check() // for cheking whether the player is cheked or not
{
	// Co-ordinates of king
	int x = 0, y = 0;
	for (int i = 0; i<8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->getValue() == 6 && board[i][j]->getColor() == turn)
			{
				x = j;
				y = i;

			}
		}
	//	cout << "\nX:" << x << "\nY: " << y;
	for (int i = 0; i<8; i++)
		for (int j = 0; j < 8; j++)
		{
			//if(board[i][j]->getColor() == turn)
			if (board[i][j]->getValue() != 0 && board[i][j]->getColor() == !turn)
			{
				//cout << "\nAfter get value";
				if (board[i][j]->isValid(j, i, x, y, board))
				{

					/*cout << "\nChecked! by:";
					board[i][j]->Print(i,j);*/
					isCheck = true;
					return true;
				}
			}

		}
	//cout << "\nFalse in check";
	isCheck = false;
	return false;

}

void Chess::PrintBoard() // For printing the board polymorphically
{
	cout << endl;
	window.clear();
	system("cls");

	for (int i = 0; i<8; i++) // For printing refrence row numbers
		cout << "   " << i + 1;

	for (int i = 0; i < 8; i++)
	{
		cout << endl;

		for (int j = 0; j < 9; j++)
		{
			if (j == 0)
				cout << i + 1 << " "; // For printing refrence column numbers
			else
			{
				board[i][j - 1]->Print(j - 1, i); // For printing the piece
				cout << "  ";
			}

		}
		cout << endl;
	}
	
	window.draw(boardImage);

	for (int i = 0; i<8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j]->getValue() != 0)
			{
				//view coordinates
				/*float a = board[i][j]->PieceImage.getPosition().x;
				float b = board[i][j]->PieceImage.getPosition().y;
				cout << a << "\t[" << (i+1) << "," << (j+1) << "] = " << a << " , " << b;*/

				board[i][j]->PieceImage.move(28, 28);
				window.draw(board[i][j]->PieceImage);
				board[i][j]->PieceImage.move(-28, -28);
			}
		}

	//panel update
	panel.setPosition(0, 505);
	window.draw(panel);
	//panel.move(0, -505);
	

	////[text]////////////////////////////
	//info text
	updateText(0, txt);
	//updateText(1, "Faizan", 1, 5, 523);

	//timer
	Time time1 = clock1.getElapsedTime();
	updateText(2, "T: " + to_string(time1.asSeconds()).substr(0, 5) + "s", 1, 350, 527, 15);
	
	//text.setFillColor(sf::Color::Red);
	//printing all text
	for (int i = 0; i < PANEL_TXT_ELEM; i++)	window.draw(panelText[i]);
	window.display();
	return;
}

void Chess::updateText(int n, string text, int font, int posX, int posY, int size){
	panelText[n].setFont(fonts[font]);
	panelText[n].setString(text);
	panelText[n].setCharacterSize(size);
	//panelText[n].move(posX, posY);
	panelText[n].setPosition(int(posX), int(posY));
	//window.draw(panelText[n]);
}

void Chess::updString(int n, string text) {
	
	panelText[n].setString(text);
	
}

void Chess::Replace(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8]) // For the replacing the piece after a move
{
	b[yfrom][xfrom]->incrementMove();
	temp = b[yto][xto]; // For temporary storing the value in case the piece is checked
	b[yto][xto] = b[yfrom][xfrom];
	b[yfrom][xfrom] = new Blank;
	// For pawn promotion
	if (b[yto][xto]->getValue() == 1 && (yto == 7 || yto == 0))
	{
		int choice;
		cout << "\nWhich piece do you want to choose? [1 for Queen,2 for Rook,3 for Knight,4 for Bishop]: ";
		fflush(stdin);
		cin >> choice;
		if (cin.eof())// If it encounter  end of file
			exit(1);
		switch (choice)
		{
		case 1:
			b[yto][xto] = new Queen(turn);
			break;

		case 2:
			b[yto][xto] = new Rook(turn);
			break;

		case 3:
			b[yto][xto] = new Knight(turn);
			break;

		case 4:
			b[yto][xto] = new Bishop(turn);
			break;

		default:
			b[yto][xto] = new Queen(turn);
		}

	}
}

// For checking whether it is a checkmate or stalemate
bool Chess::isGameOver()
{
	// For checking for each and every piece whether it has a valid
	for (int i = 0; i<8; i++)
		for (int j = 0; j < 8; j++)
		{
			// For checking whether it is a piece and it is its turn
			if (board[i][j]->getColor() == turn && board[i][j]->getValue() != 0)
			{
				for (int k = 0; k<8; k++)
					for (int l = 0; l < 8; l++)
					{
						if (board[i][j]->isValid(j, i, l, k, board))
						{
							// for replacing the piece
							Replace(j, i, l, k, board);
							if (!Check()) // If there is no check after replacemet than it is not checkmate
							{
								//cout << "\nPiece :" << board[k][l]->getValue();
								//board[k][l]->Print();
								/*cout << "  can move from:" << i << j << " to " << k << l;
								cout << "\nNot Checkmate!!";*/
								board[i][j] = board[k][l];
								board[k][l] = temp; // For restoring the piece
								GameOver = false;
								return false;
							}
							else
							{
								board[i][j] = board[k][l];
								board[k][l] = temp; // For restoring the piece
							}
						}
					}
			}
		}
	cout << "\n\nGame is Over";
	GameOver = true;
	return true; // The game is over and pieces can not move
}

// Destructor
Chess::~Chess()
{
	for (int i = 0; i<8; i++)
		delete[] * board[i];
}

// For checking for castling
bool Chess::Castling(int xfrom, int yfrom, int xto, int yto, Piece* b[8][8])
{
	cout << "\nIn castiling";
	Sleep(500);
	
	if (xfrom - xto == 2)
	{
		cout << "\n1In castiling";
		Sleep(500);
		if (b[yfrom][xfrom - 3]->getValue() == 4)// && b[yfrom][xfrom - 3]->getmove() == 0) 
		{
			cout << "\n2In castiling";
			Sleep(500);
			if (b[yfrom][xfrom - 2]->getValue() == 0 && b[yfrom][xfrom - 1]->getValue() == 0)
			{
				cout << "\n3In castiling";
				Sleep(500);
				b[yfrom][xfrom - 2] = b[yfrom][xfrom];
				b[yfrom][xfrom] = new Blank;
				//b[yfrom][xfrom - 2]->setPosition(yfrom, xfrom - 2);
				b[yfrom][xfrom - 1] = b[yfrom][xfrom - 3];
				b[yfrom][xfrom - 3] = new Blank;
				return true;
			}
		}
	}
	else if (xfrom - xto == -2)
	{
		if (b[yfrom][xfrom + 4]->getValue() == 4 )//&& b[yfrom][xfrom]->getmove() == 0)
			if (b[yfrom][xfrom + 1]->getValue() == 0 && b[yfrom][xfrom + 2]->getValue() == 0 && b[yfrom][xfrom + 3]->getValue() == 0)
			{
				b[yfrom][xfrom + 2] = b[yfrom][xfrom];
				b[yfrom][xfrom] = new Blank;
				b[yfrom][xfrom + 1] = b[yfrom][xfrom + 4];
				b[yfrom][xfrom + 4] = new Blank;
				return true;
			}
	}
	cout << "\nNO castiling";
	Sleep(500); 
	return false;
}

