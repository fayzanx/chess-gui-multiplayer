#include "Menu.h"
#include <iostream>
#include "Chess.h"
#include"Accounts.h"
#pragma once
using namespace std;


Menu::Menu()
{
}

void Menu::AddAcount()
{
	string mail, password;
	cout << "\nPlease enter email: ";
	getline(cin, mail);
	cout << "\nPlease enter password: ";
	getline(cin, password);
	data.new_account(mail, password);
}

int Menu::Login()
{
	string mail, password;
	int indexOfMail;
	bool login=false;
	do {
		cout << "\nPlease enter email: ";
		getline(cin, mail);
		 indexOfMail = data.email_search(mail);// For storing the index of email
		if (indexOfMail == -1)
		{
			cout << "\nEmail Not found!!";
		}

		else
		{
			cout << "\nPlease enter Password: ";
			getline(cin, password);
			if (data.password_check(indexOfMail, password))
			{	
				login = true;
				cout << "\nLogin Sucessful!";
			}
			else
			{
				cout << "\nWrong Password;";
			}
		}
	} while (login);
	return indexOfMail;
}

void Menu::ShowMenu()
{

	// Please add appropriate menu
	int choice;
	cin >> choice;
	switch (choice)
	{
	//For login
	case 1:
		cout << "\nPlease enter account information for White:" << endl;
		White = Login();
		cout << "\nPlease enter account information for Black:" << endl;
		Black = Login();
		break;

		//New Account
	case 2:
		AddAcount();
		break;

		// For exiting the program
	case 3:
		exit(1);
		break;

	default:
		break;
	}
}
Menu::~Menu()
{
}
