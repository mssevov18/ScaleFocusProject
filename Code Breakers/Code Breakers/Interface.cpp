//Preprocessor directives, Using, etc     |>-
#include <iostream>
#include "Miscellaneous.h"
#include "Interface.h"
#include "windows.h"

using namespace std;

//Function Definition                     |>-

void printTable(Code sln, Code guess[], unsigned short int lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln, HANDLE  hConsole)
{
	SetConsoleTextAttribute(hConsole, 7); //Black bg; white txt
	wcout << L"                   ┏━━━━━━━━━━━━━━┓\n                   ┃  ";
	SetConsoleTextAttribute(hConsole, 14);
	if (showSln)
		wcout << "?  ?  ?  ?  "; //Represents the solution
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			wcout << char(sln.digits[i]) << L"  "; //If show solution is true -> show the solution
		}
	}
	SetConsoleTextAttribute(hConsole, 7);
	wcout << L"┃\n                   ┗━━━━━━━━━━━━━━┛\n";
	wcout << L"┏━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓\n";
	wcout << L"┃   Guessed    ┃   ┃   Player     ┃   ┃   Guessed    ┃\n";
	wcout << L"┃   Position   ┃   ┃   Two's      ┃   ┃   only       ┃\n";
	wcout << L"┃   & numbers  ┃   ┃   Guesses    ┃   ┃   numbers    ┃\n";
	wcout << L"┣━━━━━━━━━━━━━━┫   ┣━━━━━━━━━━━━━━┫   ┣━━━━━━━━━━━━━━┫\n";
 	for (unsigned short int i = 0; i < 13 - lives; i++) //Maybe add a counter to pl2's guesses?
	{
		wcout << L"┃  ";
		SetConsoleTextAttribute(hConsole, 10);
		for (size_t j = 0; j < 4; j++)
		{
			if(NumAndPos[i][j]) 
				wcout << L"●  ";
			else 
				wcout << "   ";
		}
		SetConsoleTextAttribute(hConsole, 7); 
		wcout << L"┃   ┃  ";
		SetConsoleTextAttribute(hConsole, 11); 
		for (size_t j = 0; j < 4; j++)
		{
			wcout << char(guess[i].digits[j]) << "  ";
		}
		SetConsoleTextAttribute(hConsole, 7); 
		wcout << L"┃   ┃  ";
		SetConsoleTextAttribute(hConsole, 13); //change to red
		for (size_t j = 0; j < 4; j++)
		{
			if(Num[i][j]) 
				wcout << L"■  ";
			else 
				wcout << "   ";
		}
		SetConsoleTextAttribute(hConsole, 7);
		wcout << L"┃\n";
	}
	//Is possible to make the user input appear in the table
	//But in order to do that you would need to delete a few rows (the easy part)
	//And then you would have to reprint them 1x1 (the hard part)
	//Keep the idea!
	wcout << L"┃              ┃   ┃              ┃   ┃              ┃\n";
	wcout << L"┗━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━┛\n";
}


/*
┏┓┗┛┣┫┳┻╋┃━
╭╮
╰╯ BEAN player 
╭╮
╰╯ BEAN player 
╭╮
╰╯ BEAN player 
╭╮
╰╯ BEAN player 
╭╮
╰╯ BEAN player 

□■
○●

				   ┏━━━━━━━━━━━━━━┓
				   ┃  ?  ?  ?  ?  ┃
				   ┗━━━━━━━━━━━━━━┛
┏━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓
┃   Guessed    ┃   ┃   Player     ┃   ┃   Guessed    ┃
┃   Position   ┃   ┃   Two's      ┃   ┃   only       ┃
┃   & numbers  ┃   ┃   Guesses    ┃   ┃   numbers    ┃
┣━━━━━━━━━━━━━━┫   ┣━━━━━━━━━━━━━━┫   ┣━━━━━━━━━━━━━━┫
┃  ●  ●  ●  ●  ┃   ┃  n  n  n  n  ┃   ┃  ■  ■  ■  ■  ┃
┃              ┃   ┃              ┃   ┃              ┃
┗━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━┛   ┗━━━━━━━━━━━━━━┛





+--------+
|        |
|        |
|        |
+--------+








*/