/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*	Sprint: 3																		   *|
|*	Current Branch: Sprint-3-Final-touches-(from-10.01.2021-till-12.01.2021)		   *|
|*	Ver: 0.3.2																		   *|
|*	Current Stage: Final touches and clean up    									   *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * *\
|*                                     *|
|*      What's new!                    *|
|*                                     *|
|*  The game is now playable, input    *|
|*  is checked and filtered            *|
|*                                     *|
|*  Main menu                          *|
|*  Pause menu                         *|
|*  Tutorial                           *|
|*                                     *|
\* * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * *\
|*                                   *|
|*          TODO                     *|
|*                                   *|
|* 1. Clean up the code              *|
|*  - make comments                  *|
|*  - rename variables to smt better *|
|*  - remove any found bugs          *|
|*  - clean up overused terms (mode) *|
|*  - generalise variables to a few  *|
|*    types (byte, size_t, etc...)   *|
|*  - move functions to the proper   *|
|*    header file                    *|
|*  - add bookmarks                  *|
|*  - add comment headers            *|
|*                                   *|
|* 2. Documentation - ReadMe.md      *|
|*                                   *|
|* 3. Presentation - pptx            *|
|*                                   *|
|* 4. Add audio?                     *|
|*                                   *|
|* 3. Cheat sheet?                   *|
|*                                   *|
\* * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*                                                       *|
|* 1. German -> cin code (4 digit integer)               *|
|*                                                       *|
|* 2. Allies -> try to guess code                        *|
|*   Prnt: display 3 tables: -Guessed pos and num        *|
|*                           -Guessed num                *|
|*                           -Player guesses             *|
|*                                                       *|
|* 3. If more than 13 failed attempts -> end game        *|
|*                                                       *|
|* 4. If the code has been guessed correctly -> end game *|
|*                                                       *|
|* 5. Two modes: against player || against bot           *|
|*                                                       *|
|* 6. Two levels: -without repeating digits              *|
|*                -with repeating digits                 *|
|*                                                       *|
|*                                                       *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


//# Preprocessor directives, Using, Global Variables         |
#include <iostream>
#include <vector>
#include "Miscellaneous.h"
#include "Interface.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"
#include "io.h"
#include "fcntl.h"
#include "conio.h"

using namespace std;

//# Main                                                     |
int main()
{
//## Set up workflow with rand(), wcin/wcout/wstring/etc..., SetConsoleTextAttribute()
	srand(time(NULL)); //Sets the seed

	//Sets up the cli to work with unicode
	int a = _setmode(_fileno(stdout), _O_U16TEXT); //standart out
	a = _setmode(_fileno(stdin), _O_U16TEXT); //standart in

	//Sets up the cli to work with colored text
	HANDLE  hConsole; //Necessary for SetConsoleTextAttribute() to work
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);


//## Declare important variables

	/*Determines the current game state
	gameStatus codes
	0 - in game - it is player 2's turn,
	1 - winforp1 - player 1/the bot has won the game,
	2 - winforp2 - player 2 has won the game,
	3 - forfeit - one of the players have given up,
	4 - pl1 input - player 1 is writing the code,
	5 - Start menu - the game hasn't begun
	*/
	Byte gameStatus = 4; 
	/*Determines what symbols are allowed in the code
	mode codes
	=0 - numbers (0-7) only
	+1 - numbers 
	+10 - lowercase letters
	+100 - uppercase letters
	*/
	Byte mode = 0;
	Byte lives = 13; //Allowed attempts - lives

	bool symbolsCanRepeat = false;
	bool vsBot = true;

	bool NumAndPos[14][4]; //If the num and pos of the guess is correct. 4 bools for every life
	bool Num[14][4]; //If only the num of the guess is correct. 4 bools for every life

	Code sln;
	Code guess[14];

	wstring tempStr = L""; //Temporary wide string
	wstring lastInput = L""; //Contains the player input
	wstring inputFilter = L""; //Filters player and bot input
	char tempChar; //Temporary character
	wchar_t tempWChar2 = NULL; //Temporary wide character

	for (char i = '0'; i < '4'; i++) //Initialise sln as 1234
		sln.digits[int(i) - 48] = i;

	for (size_t i = 0; i < 4; i++) //1st row num and numandpos init
	{
		NumAndPos[0][i] = false;
		Num[0][i] = false;
	}
	

//## Set up and start of the game

	system("CLS");
	
	SetConsoleTextAttribute(hConsole, 7);
	startMenu(mode, symbolsCanRepeat, vsBot, hConsole);

	inputFilter = getInputFilter(mode);
	
	if (vsBot)
	{
		sln = wstringToCode(getBotInput(inputFilter, symbolsCanRepeat)); //sln is a random wstring, it follows the rules
		gameStatus = 0;
	}
	else
	{
		while (gameStatus == 4)
		{
			system("CLS");
			printInputMode(mode, symbolsCanRepeat, vsBot, hConsole);
			
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L"Choose the code (";
			
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"4 symbols";
			
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L"): ";
			
			SetConsoleTextAttribute(hConsole, 9);
			wcout << lastInput; //Displays the player input
			
			tempChar = _getch(); //Gets player input, one char at a time
			
			SetConsoleTextAttribute(hConsole, 7);

			switch (tempChar)
			{
			case 8: //Backspace -> removes the last char of the input wstring
				tempStr = lastInput;
				lastInput = tempStr.substr(0, tempStr.size() - 1); //lastInput = substring of lastInput
				break;
			case 27: //Escape -> opens the pause menu
				gameStatus = pauseMenu(4, -1, hConsole); //Game cannot be stopped from this pause menu
				if (gameStatus == 3)
					lastInput = L"";
				break;
			case 13: //Enter!
				if (lastInput.length() >= 4)
				{
					sln = wstringToCode(lastInput); //First 4 characters become the solution
					lastInput = L"";
					gameStatus = 0;
				}
				break;
			default:
				tempWChar2 = returnIfInputIsAllowed(tempChar, inputFilter, mode);
				if (tempChar >= 32 and tempWChar2 != NULL and checkIfInputIsUnique(tempChar, lastInput, symbolsCanRepeat)) //Adds the input to lastInput if all of the rules are met
					lastInput += tempWChar2;
				tempWChar2 = NULL;
				break;
			}
		}
	}

	//wcout << L"\x1b[1A";


//## Player 2's turn. Time to guess

	while (gameStatus == 0)
	{
		//### Prints the User interface
		system("cls");
		printTable(sln, guess, lives, lastInput, NumAndPos, Num, !gameStatus, hConsole);
		printInputMode(mode, symbolsCanRepeat, vsBot, hConsole);

		//### Get input from player 2
		SetConsoleTextAttribute(hConsole, 15);
		wcout << "Input guess (";

		SetConsoleTextAttribute(hConsole, 2);
		wcout << 14 - lives;

		SetConsoleTextAttribute(hConsole, 15);
		wcout << "): ";

		SetConsoleTextAttribute(hConsole, 9);
		wcout << lastInput; //Displays the player input

		tempChar = _getch(); //Gets player input, one char at a time

		SetConsoleTextAttribute(hConsole, 7);

		switch (tempChar)
		{
		case 8: //Backspace -> removes the last char of the input wstring
			tempStr = lastInput;
			lastInput = tempStr.substr(0, tempStr.size() - 1); //lastInput = substring of lastInput
			break;
		case 27: //Escape -> opens the pause menu
			gameStatus = pauseMenu(0, 3, hConsole); //Game can be stopped from this pause menu
			if (gameStatus == 3)
				lastInput = L"";
			break;
		default:
			tempWChar2 = returnIfInputIsAllowed(tempChar, inputFilter, mode);
			if (tempChar >= 32 and tempWChar2 != NULL and checkIfInputIsUnique(tempChar, lastInput, symbolsCanRepeat)) //Adds the input to lastInput if all of the rules are met
				lastInput += tempWChar2;
			tempWChar2 = NULL;
			break;
		}

		//### Check player 2's input and add it as a guess
		if (lastInput.size() == 4) //Seperate into a function? maybe.
		{
			guess[13-lives] = wstringToCode(lastInput);
			tempStr = codeToWstring(sln);			
			Byte count = 0;

			if (lastInput == tempStr)
				gameStatus = 2;

			for (size_t i = 0; i < 4; i++) //Num and pos for current guess init
			{
				NumAndPos[13 - lives][i] = false;
				Num[13 - lives][i] = false;
			}

			count = 0;
			for (size_t i = 0; i < 4; i++) //Num and pos check
			{
				for (size_t j = 0; j < 4; j++)
				{
					if (lastInput[j] == tempStr[i] and i == j)
					{
						NumAndPos[13 - lives][count++] = true;
						lastInput[j] = NULL;
						tempStr[i] = NULL;
						break;
					}
				}
			}

			count = 0;
			for (size_t i = 0; i < 4; i++) //Num check
			{
				for (size_t j = 0; j < 4; j++)
				{
					if (lastInput[j] == NULL)
						continue;

					if (lastInput[j] == tempStr[i])
					{
						Num[13 - lives][count++] = true;
						lastInput[j] = NULL;
						tempStr[i] = NULL;
					}
				}
			}

			lives--;
			lastInput = L"";
		}

		if (lives <= 0)
			gameStatus = 1;

	}


//## Game has finished

	//### Print game statistics
	system("CLS");
	printTable(sln, guess, lives, lastInput, NumAndPos, Num, !gameStatus, hConsole);
	printInputMode(mode, symbolsCanRepeat, vsBot, hConsole);

	//### Print winner
	switch (gameStatus)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, 158);
		if (vsBot)
			wcout << L"\nTHE BOT WINS!";
		else
			wcout << L"\nPLAYER 1 WINS!";
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, 94);
		wcout << L"\nPLAYER 2 WINS!";
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, 192);
		wcout << L"\nA PLAYER FORFEITED!";
		break;
	default:
		break;
	}
	SetConsoleTextAttribute(hConsole, 7);
}

//Source.cpp - Done