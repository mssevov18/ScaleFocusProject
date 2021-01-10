/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*	Sprint: 2																		   *|
|*	Current Branch: Sprint-2-Making-the-game-(from-21.12.2020-till-03.01.2021)		   *|
|*	Ver: 0.2.5																		   *|
|*	Current Stage: Optimisation of game mechanics									   *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * *\
|*                                     *|
|*      What's new!                    *|
|*                                     *|
|*  The game is now playable, input    *|
|*  is checked and filtered            *|
|*                                     *|
|*  Main menu                          *|
|*                                     *|
|*  Pause menu                         *|
|*                                     *|
\* * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * *\
|*                                   *|
|*          TODO                     *|
|*                                   *|
|* 1. Create the tutorial            *|
|*                                   *|
|* 2. Clean up the code              *|
|*  - make comments                  *|
|*  - rename variables to smt better *|
|*  - remove any found bugs          *|
|*  - clean up overused terms (mode) *|
|*                                   *|
|* 3. Cheat sheet?                   *|
|*                                   *|
|* 4. Add audio                      *|
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


//Preprocessor directives, Using, Global Variables         |
#include <iostream>
#include <vector>
#include "stdlib.h"
#include "time.h"
#include "windows.h"
#include "io.h"
#include "fcntl.h"
#include "conio.h"
#include "Miscellaneous.h"
#include "Interface.h"

using namespace std;

//Function Declaration                                     |

//Main                                                     |
int main()
{
	//Sets the seed
	srand(time(NULL));

	//Sets up the cli to work with unicode
	int a = _setmode(_fileno(stdout), _O_U16TEXT);
	a = _setmode(_fileno(stdin), _O_U16TEXT);

	//Sets up the cli to work with colored text
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	/*
	0 - in game,
	1 - winforp1,
	2 - winforp2,
	3 - forfeit,
	4 - pl1 input,
	5 - Start menu,
	6 - Settings menu,
	7 - Pause screen
	*/

	unsigned short int gameStatus = 4; 
	unsigned short int lives = 13, size = 0;
	
	/*Settings*/
	unsigned short int mode = 0;
	bool symbolsCanRepeat = false;
	bool vsBot = true;

	bool NumAndPos[14][4], Num[14][4];

	Code sln, guess[14];

	for (char i = '0'; i < '4'; i++)
		sln.digits[int(i) - 48] = i;

	wstring tempStr = L"", lastInput = L"", inputFilter = L"";
	char tempChar;
	wchar_t tempWChar2 = NULL;

	for (size_t i = 0; i < 4; i++) //Num and pos init
	{
		NumAndPos[0][i] = false;
		Num[0][i] = false;
	}
	
	SetConsoleTextAttribute(hConsole, 7);
	system("CLS");
	
	startMenu(mode, symbolsCanRepeat, vsBot, hConsole);

	inputFilter = getInputFilter(mode);
	
	if (vsBot)
	{
		sln = wstringToCode(getBotInput(inputFilter, symbolsCanRepeat));
		gameStatus = 0;
	}
	else
	{
		while (gameStatus == 4)
		{
			system("CLS");
			//get user1 input
			printInputMode(mode, symbolsCanRepeat, vsBot, hConsole);
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L"Choose the code (";
			SetConsoleTextAttribute(hConsole, 2);
			wcout << L"4 symbols";
			SetConsoleTextAttribute(hConsole, 15);
			wcout << L"): ";
			SetConsoleTextAttribute(hConsole, 9);
			wcout << lastInput;
			tempChar = _getch();
			SetConsoleTextAttribute(hConsole, 7);

			switch (tempChar)
			{
			case 8: //Backspace -> removes the last char of the cheat code
				tempStr = lastInput;
				lastInput = tempStr.substr(0, tempStr.size() - 1);
				break;
			case 27: //Escape -> quits the program
				gameStatus = pauseMenu(4, -1, hConsole);
				if (gameStatus == 3)
					lastInput = L"";
				break;
			case 13: //Enter!
				if (lastInput.length() >= 4)
				{
					sln = wstringToCode(lastInput);
					lastInput = L"";
					gameStatus = 0;
				}
				break;
			default:
				tempWChar2 = returnIfInputIsAllowed(tempChar, inputFilter, mode);
				if (tempChar >= 32 and tempWChar2 != NULL and checkIfInputIsUnique(tempChar, lastInput, symbolsCanRepeat))
					lastInput += tempWChar2;
				tempWChar2 = NULL;
				break;
			}
		}
	}

	//wcout << L"\x1b[1A";

	while (gameStatus == 0)
	{
		system("cls");

		//print map
		printTable(sln, guess, lives, lastInput, NumAndPos, Num, !gameStatus, hConsole);

		printInputMode(mode, symbolsCanRepeat, vsBot, hConsole);

		//get user2 input
		SetConsoleTextAttribute(hConsole, 15);
		wcout << "Input guess (";
		SetConsoleTextAttribute(hConsole, 2);
		wcout << 13 - lives;
		SetConsoleTextAttribute(hConsole, 15);
		wcout << "): ";
		SetConsoleTextAttribute(hConsole, 9);
		wcout << lastInput;
		tempChar = _getch();
		SetConsoleTextAttribute(hConsole, 7);
		switch (tempChar)
		{
		case 8: //Backspace -> removes the last char of the cheat code
			tempStr = lastInput;
			lastInput = tempStr.substr(0, tempStr.size() - 1);
			break;
		case 27: //Escape -> quits the program
			gameStatus = pauseMenu(0, 3, hConsole);
			if (gameStatus == 3)
				lastInput = L"";
			break;
		default:
			tempWChar2 = returnIfInputIsAllowed(tempChar, inputFilter, mode);
			if (tempChar >= 32 and tempWChar2 != NULL and checkIfInputIsUnique(tempChar, lastInput, symbolsCanRepeat))
				lastInput += tempWChar2;
			tempWChar2 = NULL;
			break;
		}

		//check user2 input
		if (lastInput.size() == 4) //Seperate into a function!!!
		{
			guess[13-lives] = wstringToCode(lastInput);
			tempStr = codeToWstring(sln);			
			unsigned short int count = 0;

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

		if (lives == 0)
			gameStatus = 1;

	}

	system("CLS");

	printTable(sln, guess, lives, lastInput, NumAndPos, Num, !gameStatus, hConsole);

	printInputMode(mode, symbolsCanRepeat, vsBot, hConsole);

	switch (gameStatus)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, 158);
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
 
//Function Definition                                      |
