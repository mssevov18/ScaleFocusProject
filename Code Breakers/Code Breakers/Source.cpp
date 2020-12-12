/*-------------------------------------------------------------------------------------*\
|*	Sprint: 1																		   *|
|*	Current Branch: Sprint-1-Understanding-the-assignment-(from-09.12-till-13.12)	   *|
|*	Ver: 0.1.1																		   *|
|*	Current Stage: General Architecture of the project								   *|
\*-------------------------------------------------------------------------------------*/

/*-------------------------------------------------------*\
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
\*-------------------------------------------------------*/


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

	bool inGame = true;
	bool NumAndPos[14][4], Num[14][4];

	unsigned short int lives = 13, input, size = 0;
	
	Code sln, guess[14];

	string tempStr, lastInput = "";
	char sym;

	SetConsoleTextAttribute(hConsole, 10);
	wcout << L"●\n";

	SetConsoleTextAttribute(hConsole, 7);
	wcout << L"Choose the code...";
	putinUnSInt(input);
	for (unsigned short int i = 0; i < 4; i++)
		sln.digits[i] = breakIntoDigit(input, i);

	//wcout << L"\x1b[1A";

	while (inGame)
	{
		//print map
		printTable(sln,guess,lives,lastInput,NumAndPos,Num,!inGame, hConsole);
		
		//get user2 input
		sym = _getch();
		switch (sym)
		{
		case 8: //Backspace -> removes the last char of the cheat code
			tempStr = lastInput;
			lastInput = tempStr.substr(0, tempStr.size() - 1);
			break;
		case 27: //Escape -> quits the program
			lastInput = "";
			inGame = false;
			break;
		default:
			if (sym >= 32)
				lastInput += sym;
			break;
		}

		//check user2 input

		//update tables
		followUpPrint();	
	}
}
 
//Function Definition                                      |
