#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include <string>
#include "Accounts.h"
using namespace std;
using namespace sf;
#define SPLASH_BG_LOCATION "images/bgbig.jpg"
#define SPLASH_ATTR VideoMode(750, 750), "Choose", Style::None
#define MENU_ELEMENTS 7 //numberof elements
//bool splash_closed = true; // checking existence of splash window

struct userData {
	unsigned int games_played;
	unsigned int wins;
	unsigned int stalemates;
	string mail;
	string pass;
	string side;
	unsigned int index;
};

class Splash
{
private:
	//main window
	Texture img;
	Sprite paintBG;
	RenderWindow splash;
	//fonts and texts
	Text allText[MENU_ELEMENTS];
	//String textContent[MENU_ELEMENTS];
	Font a_gc;
	Font b_et;
	//Buttons
	Texture btnTexture;
	Sprite btnActive[MENU_ELEMENTS];
	Sprite btnInactive[MENU_ELEMENTS];
	//Button b[MENU_ELEMENTS];
	//counter
	static int n;
	//ACCOUNTS
	Database data;
	string dataEntryE[4];
	userData all[2];
	int playingSideIndex[2]; //0 white 1 brown
public:
	bool dead; 
	bool userLoggedIn;
	void setText(int no, string in, Font* ft, int posX = 25, int posY = 25, int size = 10);
	void updText(int no, string in);
	void loadAssets();
	void buttonAnimations();
	void submitBtn();
	//login validation
	void loginPressed(int& clicks);
	void validate(int &hits);
	void signup(int &hits);
	void accountDecision(int &hits, bool flag, bool &flag2);
	userData getData(int n) {
		return all[n];
	}
	Splash();
	~Splash();
};