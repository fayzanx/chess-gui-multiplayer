#ifndef Account
#define Accounts
#pragma once
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

//////////////////////////////////////////////////////
class Account
{
public:
	string email;
	string password;
	unsigned int games_played;
	unsigned int wins;
	unsigned int stalemates;

	//Encryption data
	int n_modulus = 3233;
	int e_exponent = 17;
	int d_exponent = 413;

public:
	//Saves account details at the end of file data.dat
	void save();
	//Number encryptor
	int Encrypt(int m);
	//Number decryptor
	int Decrypt(int m);
	//String encryptor
	string Encrypt(string input);
	//String decryptor
	string Decrypt(string input);
};




//All mathematical. Leave it

//////////////////////////////////////////////////////
//Calculates the absolute value
int absolute(float x);
//Calcultes gcd of two arguments passed
int euclidean_algorithm(int a, int b);
//Calcultes modular inverse
int modular_inverse(int a, int m);
//Calculates totient of two primes passed as argument
  int totient(int a, int b);
//Modular exponentian.
long long int modular_exponentiation(int b, int e, int m);
int key(int e, int m);
//////////////////////////////////////////////////////
//Counts number of lines in file data.data
//Used to initialize array in object of type database
int line_count();




//////////////////////////////////////////////////////
class Database
{
private:
	int n;                 //Total number of accounts
	Account* accounts;     //Starting address of array

						   //Encryption variables
	int n_modulus = 3233;  //Modulus
	int e_exponent = 17;
	int d_exponent = 413;

public:
	//Constructor
	Database();
	~Database();
	//Number encryptor
	int Encrypt(int m);
	//Number decryptor
	int Decrypt(int m);
	//String encryptor
	string Encrypt(string input);
	//String decryptor
	string Decrypt(string input);
	//GETTERS
	/////////////////////////////////////
	  int get_number_of_accounts();
	  string get_email(int i);
	  string get_password(int i);
	  int get_games_played(int i);
	//  int get_wins(int i);
	int get_wins(int i);
	  int get_stalemates(int i);
	//Reads data from file into database object after and decrypts
	void read();
	//Searches for a particular email
	//If found returns position in array, else returns -1
	int email_search(string email);
	//Checks password of user at particular index
	//Returns index of user if correct else returns -1
	bool password_check(int n, string password);
	//Saves data onto the file data.dat in encrypted form
	void save();
	//Creates a new account in database object and saves it in file
	void new_account(string ml, string psswrd);

	//INCREMENTORS
	/////////////////////////////////////
	  void increment_wins(unsigned int i);
	  void increment_stalemates(unsigned int i);
	  void increment_games_played(unsigned int i);
};

#endif