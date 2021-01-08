//Preprocessor directives, Using, etc     |>-
#include <iostream>
#include "Miscellaneous.h"
#include "Interface.h"
#include "windows.h"
#include "stdlib.h""

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

wstring getInputFilter(unsigned short int mode)
{
	//Mode
	//0 - numbers (0-7) only
	//1 - numbers only
	//2 - lowercase letters only
	//3 - uppercase letters only
	//4 - letters only
	//5 - lowercase letters and numbers
	//6 - uppercase letters and numbers
	//7 - letters and numbers
	wstring filter = L"";
	switch (mode)
	{
	case 0:
		filter = L"01234567";
		break;
	case 1:
		filter = L"0123456789";
		break;
	case 2:
		filter = L"qwertyuiopasdfghjklzxcvbnm";
		break;
	case 3:
		filter = L"QWERTYUIOPASDFGHJKLZXCVBNM";
		break;
	case 4:
		filter = L"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
		break;
	case 5:
		filter = L"0123456789qwertyuiopasdfghjklzxcvbnm";
		break;
	case 6:
		filter = L"0123456789QWERTYUIOPASDFGHJKLZXCVBNM";
		break;
	case 7:
		filter = L"0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
		break;
	default:
		break;
	}

	return filter;
}

wchar_t checkIfInputIsAllowed(char in, wstring filter, unsigned short int mode)
{
	for (size_t i = 0; i < filter.length(); i++)
	{
		if (in == filter[i])
			return in;
	}

	return NULL;
}

bool checkIfInputIsUnique(char in, wstring lastInput, bool symbolsCanRepeat)
{
	for (size_t j = 0; j < lastInput.length(); j++)
	{
		if (lastInput[j] == NULL)
			continue;

		if (lastInput[j] == in)
		{
			return false;
		}
	}
	return true;
}

wstring getBotInput(wstring filter)
{
	wstring out = L"";
	for (size_t i = 0; i < 4; i++)
	{
		out += filter[rand() % filter.length()];
	}
	return out;
}

void printInputMode(unsigned short int mode, bool symbolsCanRepeat, bool vsBot)
{
	wcout << "Input Mode: ";
	switch (mode)
	{
	case 0:
		wcout << "Numbers 0 to 7\n";
		break;
	case 1:
		wcout << "All numbers\n";
		break;
	case 2:
		wcout << "All lowercase letters\n";
		break;
	case 3:
		wcout << "All uppercase letters\n";
		break;
	case 4:
		wcout << "All letters\n";
		break;
	case 5:
		wcout << "All numbers and only lowercase letters\n";
		break;
	case 6:
		wcout << "All numbers and only uppercase letters\n";
		break;
	case 7:
		wcout << "All numbers and all letters\n";
		break;
	default:
		break;
	}

	wcout << L"Symbols ";
	if (symbolsCanRepeat)
		wcout << L"can";
	else
		wcout << L"can't";
	wcout << L" repeat\n";
	
	wcout << L"Playing against ";
	if (vsBot)
		wcout << L"a Bot\n";
	else
		wcout << L"another Player\n";
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