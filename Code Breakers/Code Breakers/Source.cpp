/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
|*	Sprint: 1																		   *|
|*	Current Branch: Sprint-1-Understanding-the-assignment-(from-09.12-till-13.12)	   *|
|*	Ver: 0.1.2																		   *|
|*	Current Stage: General Architecture of the project								   *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * *\
|*                                     *|
|*      What's new!                    *|
|*                                     *|
|*  The game is now playable, input    *|
|*  is !not checked and filtered       *|
|*                                     *|
\* * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * *\
|*          TODO                     *|
|*                                   *|
|* 1. Make functions to check pl in- *|
|*    put.                           *|
|*                                   *|
|*                                   *|
|*                                   *|
|*                                   *|
\* * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
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
|*                                                       *|
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * */


//Preprocessor directives, Using, Global Variables         |
#include <iostream>
#include <vector>
#include <thread>
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
	int a = _setmode(_fileno(stdout), _O_U16TEXT);
	a = _setmode(_fileno(stdin), _O_U16TEXT);

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);

	unsigned short int gameStatus = 0; //0 - in game, 1 - winforp1, 2 - winforp2, 3 - forfeit
	bool NumAndPos[14][4], Num[14][4];

	for (size_t i = 0; i < 4; i++) //Num and pos init
	{
		NumAndPos[0][i] = false;
		Num[0][i] = false;
	}

	unsigned short int lives = 13, input, size = 0;
	
	Code sln, guess[14];

	wstring tempStr = L"", lastInput = L"";
	char sym;

	SetConsoleTextAttribute(hConsole, 7);
	wcout << L"Choose the code...";
	putinUnSInt(input);
	for (unsigned short int i = 0; i < 4; i++)
		sln.digits[i] = Byte(breakIntoDigit(input, i) + 48);

	//wcout << L"\x1b[1A";

	while (gameStatus == 0)
	{
		system("cls");

		//print map
		printTable(sln, guess, lives, lastInput, NumAndPos, Num, !gameStatus, hConsole);
		
		//get user2 input
		wcout << "Input guess (" << 13 - lives << "): " << lastInput;
		sym = _getch();
		switch (sym)
		{
		case 8: //Backspace -> removes the last char of the cheat code
			tempStr = lastInput;
			lastInput = tempStr.substr(0, tempStr.size() - 1);
			break;
		case 27: //Escape -> quits the program
			lastInput = L"";
			gameStatus = 3;
			break;
		default:
			if (sym >= 32)
				lastInput += sym;
			break;
		}

		//check user2 input
		if (lastInput.size() == 4) //Seperate into a function!!!
		{
			guess[13-lives].digits[0] = Byte(lastInput[0]);
			guess[13-lives].digits[1] = Byte(lastInput[1]);
			guess[13-lives].digits[2] = Byte(lastInput[2]);
			guess[13-lives].digits[3] = Byte(lastInput[3]);
			
			tempStr =  sln.digits[0];
			tempStr += sln.digits[1];
			tempStr += sln.digits[2];
			tempStr += sln.digits[3];
			
			unsigned short int count = 0;

			if (lastInput == tempStr)
				gameStatus = 2;

			for (size_t i = 0; i < 4; i++) //Num and pos init
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
						lastInput[j] = L'!';
						break;
					}
				}
			}

			count = 0;
			for (size_t i = 0; i < 4; i++) //Num check
			{
				for (size_t j = 0; j < 4; j++)
				{
					if (lastInput[j] == L'!')
						continue;

					if (lastInput[j] == tempStr[i])
					{
						Num[13 - lives][count++] = true;
						lastInput[j] = L'!';
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

	switch (gameStatus)
	{
	case 1:
		wcout << L"\nPLAYER 1 WINS!";
		break;
	case 2:
		wcout << L"\nPLAYER 2 WINS!";
		break;
	case 3:
		wcout << L"\nA PLAYER FOREFEITED!";
		break;
	default:
		break;
	}
}
 
//Function Definition                                      |
