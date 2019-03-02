#pragma once
#include <iostream>
#include "Chess.h"
#include"Accounts.h"
#include"Splash.h"
#pragma once
using namespace std;
class Menu
{
	Database data;
	int White;//This will store the index in which the player playing is stored in Database
	int Black;
	Splash welcomeScreen;
public:
	void Welcome();//Display Splash window
	void AddAcount();
	int Login();
	void ShowMenu();
	Menu();
	~Menu();
};

