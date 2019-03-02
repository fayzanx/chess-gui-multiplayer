#include <iostream>
#include"Accounts.h"
#pragma once
using namespace std;

//All mathematical. Leave it

//////////////////////////////////////////////////////
//Calculates the absolute value
int absolute(float x)
{
	int y;
	y = x;
	return y;
}

//Calcultes gcd of two arguments passed
int euclidean_algorithm(int a, int b)
{
	int r;

	do
	{
		r = a % b;
		a = b;
		b = r;
	} while (b != 0);

	return a;
}

//Calcultes modular inverse
int modular_inverse(int a, int m)
{
	float y = 1;
	while (1)
	{
		if ((1 + m * y) / a == absolute((1 + m * y) / a))
			break;
		else
			y++;
	}

	return (1 + m * y) / a;
}

//Calculates totient of two primes passed as argument
int totient(int a, int b)
{
	return (a - 1)*(b - 1);
}

//Modular exponentian.
long long int modular_exponentiation(int b, int e, int m)
{
	int counter = 1;
	long long int c = b;
	while (counter<e) {
		c *= b;
		c = c % m;
		counter++;
	}
	return c;
}

int key(int e, int m)
{
	return modular_inverse(e, m);
}

//////////////////////////////////////////////////////
//Counts number of lines in file data.data
//Used to initialize array in object of type database

int line_count()
{
	int number_of_lines = 0;
	string line;
	ifstream myfile("data.dat");

	while (getline(myfile, line))
		++number_of_lines;
	return number_of_lines;
}









///////////////////////////////////
///////ACCOUNTS DEFINITIONS////////
///////////////////////////////////
void Account::save()
{
	ofstream outfile;
	outfile.open("data.dat", std::ios_base::app);

	//sets cursor at the end of file
	outfile.seekp(0, ios::end);

	outfile << Encrypt(password) << " "
		<< Encrypt(games_played) << " "
		<< Encrypt(wins) << " "
		<< Encrypt(stalemates) << " "
		<< Encrypt(email) << "\n";

	outfile.close();
}

//Number encryptor
int Account::Encrypt(int m)
{
	return modular_exponentiation(m, e_exponent, n_modulus);
}

//Number decryptor
int Account::Decrypt(int m)
{
	return modular_exponentiation(m, d_exponent, n_modulus);
}

//String encryptor
string Account::Encrypt(string input)
{
	int n = input.length();

	char* c = new char[n + 1];
	c[n] = '\0';

	for (int i = 0; i<n; i++)
	{
		c[i] = input.at(i) + i;
	}

	string output = c;
	return output;
}

//String decryptor
string Account::Decrypt(string input)
{
	int n = input.length();

	char* c = new char[n + 1];
	c[n] = '\0';

	for (int i = 0; i<n; i++)
	{
		c[i] = input.at(i) - i;
	}

	string output = c;
	return output;
}



/////////////////////////////////////
///////// DATABASE /////////////////
////////////////////////////////////

Database::Database() : n(line_count())
{
	//Creates an array of appropriate size
	accounts = new Account[n];

	//Reads data in the array
	read();
}

Database::~Database()
{
	//Saves data before destroying database object
	save();
}

//Number encryptor
int Database::Encrypt(int m)
{
	return modular_exponentiation(m, e_exponent, n_modulus);
}

//Number decryptor
int Database::Decrypt(int m)
{
	return modular_exponentiation(m, d_exponent, n_modulus);
}

//String encryptor
string Database::Encrypt(string input)
{
	int n = input.length();

	char* c = new char[n + 1];
	c[n] = '\0';

	for (int i = 0; i<n; i++)
	{
		c[i] = input.at(i) + i;
	}

	string output = c;
	return output;
}

//String decryptor
string Database::Decrypt(string input)
{
	int n = input.length();

	char* c = new char[n + 1];
	c[n] = '\0';

	for (int i = 0; i<n; i++)
	{
		c[i] = input.at(i) - i;
	}

	string output = c;
	return output;
}

//GETTERS
/////////////////////////////////////
int Database::get_number_of_accounts()
{
	return n;
}

string Database::get_email(int i)
{
	return accounts[i].email;
}

string Database::get_password(int i)
{
	return accounts[i].password;
}

int Database::get_games_played(int i)
{
	return accounts[i].games_played;
}

int Database::get_wins(int i)
{
	return accounts[i].wins;
}

int Database::get_stalemates(int i)
{
	return accounts[i].stalemates;
}
/////////////////////////////////////

//Reads data from file into database object after and decrypts
void Database::read()
{
	ifstream infile;
	infile.open("data.dat");
	cout << "input";
	for (int i = 0; i<n; ++i)
	{
		infile >> accounts[i].password
			>> accounts[i].games_played
			>> accounts[i].wins
			>> accounts[i].stalemates
			>> accounts[i].email;

		accounts[i].email = Decrypt(accounts[i].email);
		accounts[i].password = Decrypt(accounts[i].password);
		accounts[i].games_played = Decrypt(accounts[i].games_played);
		accounts[i].wins = Decrypt(accounts[i].wins);
		accounts[i].stalemates = Decrypt(accounts[i].stalemates);

		infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	infile.close();
}

//Searches for a particular email
//If found returns position in array, else returns -1
int Database::email_search(string email)
{
	for (int i = 0; i<n; i++)
	{
		if (email == accounts[i].email)
			return i;
	}
	return -1;
}

//Checks password of user at particular index
//Returns index of user if correct else returns -1
bool Database::password_check(int n, string password)
{
	if (password == accounts[n].password)
		return true;
	else
		return false;
}

//Saves data onto the file data.dat in encrypted form
void Database::save()
{
	ofstream outfile;
	outfile.open("data.dat");
	for (int i = 0; i<n; i++)
	{
		outfile << Encrypt(accounts[i].password) << " "
			<< Encrypt(accounts[i].games_played) << " "
			<< Encrypt(accounts[i].wins) << " "
			<< Encrypt(accounts[i].stalemates) << " "
			<< Encrypt(accounts[i].email) << "\n";
	}
	outfile.close();
}

//Creates a new account in database object and saves it in file
void Database::new_account(string ml, string psswrd)
{
	Account* a;
	a = new Account;
	a->email = ml;
	a->password = psswrd;
	a->wins = 0;
	a->stalemates = 0;
	a->games_played = 0;
	a->save();
	delete a;
	accounts = new Account[++n];
	read();
}

//INCREMENTORS
/////////////////////////////////////
void Database::increment_wins(unsigned int i)
{
	accounts[i].wins++;
	save();
}

void Database::increment_stalemates(unsigned int i)
{
	accounts[i].stalemates++;
	save();
}

void Database::increment_games_played(unsigned int i)
{
	accounts[i].games_played++;
	save();
}