//Preprocessor directives, Using, etc     |>-
#include <iostream>
#include "Miscellaneous.h"
#include "Interface.h"
#include "windows.h"

using namespace std;

//Function Definition                     |>-

void printTable(Code sln, Code guess[], unsigned short int lives, string lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln, HANDLE  hConsole)
{
	SetConsoleTextAttribute(hConsole, 7);
	wcout << L"              ┏━━━━━━━━━┓\n              ┃ ";
	if (showSln)
		wcout << L"? ? ? ? ";
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			wcout << sln.digits[i] << L' ';
		}
	}
	wcout << L"┃\n              ┗━━━━━━━━━┛\n";
	wcout << L"┏━━━━━━━━━┓   ┏━━━━━━━━━┓   ┏━━━━━━━━━┓\n";
	wcout << L"┃ Guessed ┃   ┃ Player  ┃   ┃ Guessed ┃\n";
	wcout << L"┃Position ┃   ┃  Two's  ┃   ┃   only  ┃\n";
	wcout << L"┃& numbers┃   ┃ Guesses ┃   ┃ numbers ┃\n";
	wcout << L"┣━━━━━━━━━┫   ┣━━━━━━━━━┫   ┣━━━━━━━━━┫\n┃ ";
	for (unsigned short int i = 0; i < 14 - lives; i++)
	{
		SetConsoleTextAttribute(hConsole, 10);
		for (size_t j = 0; j < 4; j++)
		{
			if(NumAndPos[i][j]) 
				wcout << L"● ";
			else 
				wcout << L"  ";
		}
		SetConsoleTextAttribute(hConsole, 7); 
		wcout << L"┃   ┃ ";
		for (size_t j = 0; j < 4; j++)
		{
			wcout << guess[i].digits[j] << L' ';
		}
		wcout << L"┃   ┃ ";
		SetConsoleTextAttribute(hConsole, 10); //change to red
		for (size_t j = 0; j < 4; j++)
		{
			if(Num[i][j]) 
				wcout << L"■ ";
			else 
				wcout << L"  ";
		}
	}
	SetConsoleTextAttribute(hConsole, 7);
	wcout << L"┃\n┃         ┃   ┃         ┃   ┃         ┃\n";
	wcout << L"┗━━━━━━━━━┛   ┗━━━━━━━━━┛   ┗━━━━━━━━━┛\n";
}

void followUpPrint()
{
	
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

			  ┏━━━━━━━━━┓
			  ┃ ? ? ? ? ┃
			  ┗━━━━━━━━━┛
┏━━━━━━━━━┓   ┏━━━━━━━━━┓   ┏━━━━━━━━━┓
┃ Guessed ┃   ┃  Player ┃   ┃ Guessed ┃
┃Position ┃   ┃  Two's  ┃   ┃   only  ┃
┃& numbers┃   ┃ Guesses ┃   ┃ numbers ┃
┣━━━━━━━━━┫   ┣━━━━━━━━━┫   ┣━━━━━━━━━┫
┃ ● ● ● ● ┃   ┃ n n n n ┃   ┃ ■ ■ ■ ■ ┃
┃         ┃   ┃         ┃   ┃         ┃
┗━━━━━━━━━┛   ┗━━━━━━━━━┛   ┗━━━━━━━━━┛









+--------+
|        |
|        |
|        |
+--------+








*/