//Preprocessor directives, Using, etc     |>-
#include <iostream>
#include "Miscellaneous.h"
#include "Interface.h"
#include "windows.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"

using namespace std;

//Function Definition                     |>-

void printTable(Code sln, Code guess[], unsigned short int lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln, HANDLE hConsole)
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
	wcout << L"┃   Positions  ┃   ┃   Two's      ┃   ┃   symbols    ┃\n";
	wcout << L"┃   & symbols  ┃   ┃   Guesses    ┃   ┃   only       ┃\n";
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
	//4 - letters only
	//5 - lowercase letters and numbers
	//6 - uppercase letters and numbers
	//7 - letters and numbers

	//NEW MODE
	//=0 - numbers (0-7) only
	//+1 - numbers 
	//+10 - lowercase letters
	//+100 - uppercase letters



	if (mode == 0)
		return L"01234567";

	wstring filter = L"";
	
	if (mode % 2 == 1)
		filter = L"0123456789";

	mode /= 10;

	if (mode % 2 == 1)
		filter += L"qwertyuiopasdfghjklzxcvbnm";

	mode /= 10;

	if (mode % 2 == 1)
		filter += L"QWERTYUIOPASDFGHJKLZXCVBNM";

	//switch (mode)
	//{
	//case 0:
	//	filter = L"01234567";
	//	break;
	//case 1:
	//	filter = L"0123456789";
	//	break;
	//case 2:
	//	filter = L"qwertyuiopasdfghjklzxcvbnm";
	//	break;
	//case 3:
	//	filter = L"QWERTYUIOPASDFGHJKLZXCVBNM";
	//	break;
	//case 4:
	//	filter = L"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	//	break;
	//case 5:
	//	filter = L"0123456789qwertyuiopasdfghjklzxcvbnm";
	//	break;
	//case 6:
	//	filter = L"0123456789QWERTYUIOPASDFGHJKLZXCVBNM";
	//	break;
	//case 7:
	//	filter = L"0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	//	break;
	//default:
	//	break;
	//}

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

wstring getBotInput(wstring filter, bool symbolsCanRepeat)
{
	wstring out = L"";
	wchar_t test = NULL;
	for (size_t i = 0; i < 4; i++)
	{
		test = filter[rand() % filter.length()];
		if (checkIfInputIsUnique(test, out, symbolsCanRepeat))
			out += test;
		else
			i--;
	}
	return out;
}

void printInputMode(unsigned short int mode, bool symbolsCanRepeat, bool vsBot) 
{
	//ADD COLOURS!!!
	//ADD COLOURS!!!
	//ADD COLOURS!!!
	//ADD COLOURS!!!
	//ADD COLOURS!!!
	wcout << "Input Mode: ";

	bool bMode[4] = { false,false,false,false };
	int amount = 1;
	unsigned short int mem = mode;
	if (mode == 0) //Seperate into a function?
		bMode[0] = true;
	else
	{
		for (int i = 1; i < 4; i++)
		{
			if (mode % 2 == 1)
				bMode[i] = true;
			mode /= 10;
		}

		//if (mode % 2 == 1)
		//	bMode[1] = true;
		//mode /= 10;
		//if (mode % 2 == 1)
		//	bMode[2] = true;
		//mode /= 10;
		//if (mode % 2 == 1)
		//	bMode[3] = true;
	}

	wcout << '\n';

	mode = mem;
	if (mode == 0)
		wcout << "Numbers 0 to 7 only";
	if (mode % 2 == 1)
		wcout << "All numbers\t";
	mode /= 10;
	if (mode % 2 == 1)
		wcout << "All lowercase letters\t";
	mode /= 10;
	if (mode % 2 == 1)
		wcout << "All uppercase letters\t";

	wcout << '\n';

	//switch (mode)
	//{
	//case 0:
	//	wcout << "Numbers 0 to 7\n";
	//	break;
	//case 1:
	//	wcout << "All numbers\n";
	//	break;
	//case 2:
	//	wcout << "All lowercase letters\n";
	//	break;
	//case 3:
	//	wcout << "All uppercase letters\n";
	//	break;
	//case 4:
	//	wcout << "All letters\n";
	//	break;
	//case 5:
	//	wcout << "All numbers and only lowercase letters\n";
	//	break;
	//case 6:
	//	wcout << "All numbers and only uppercase letters\n";
	//	break;
	//case 7:
	//	wcout << "All numbers and all letters\n";
	//	break;
	//default:
	//	break;
	//}

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

void startMenu(unsigned short int &mode, bool &symbolsCanRepeat, bool &vsBot, HANDLE hConsole)
{
	bool ready = false;
	int activeStep = 0;
	char action = NULL;
	int count = 0;
	bool isActivated[11];
	bool bMode[4] = { false,false,false,false };

	mode = 0;
	symbolsCanRepeat = false;
	vsBot = false;

	if (mode == 0) //Seperate into a function?
		bMode[0] = true;
	else
	{
		if (mode % 2 == 1)
			bMode[1] = true;
		mode /= 10;
		if (mode % 2 == 1)
			bMode[2] = true;
		mode /= 10;
		if (mode % 2 == 1)
			bMode[3] = true;
	}

	wstring steps[] = {
		L"Play against a bot?    -No-/╼Yes╾",
		L"  ○ numbers (0-7) only           ",
		L"  ○ numbers                      ",
		L"  ○ lowercase letters            ",
		L"  ○ uppercase letters            ",
		L"Symbols can repeat?    -No-/╼Yes╾",
		L"          S  T  A  R  T          "
	};

	isActivated[0] = vsBot;
	for (int i = 1; i < 5; i++)
		isActivated[i] = bMode[i - 1];
	isActivated[5] = symbolsCanRepeat;
	isActivated[6] = ready;

	SetConsoleTextAttribute(hConsole, 7);
	while (!ready)
	{
		count = 0;

		system("CLS");
		wcout << L"╔═════════════════╗\n";
		wcout << L"║  Code Breakers  ║\n";
		wcout << L"╠═════════════════╩═══════════════════╗\n";
		wcout << L"║  C++ game by '✶ GitHub Cultists ✶'  ║\n";
		wcout << L"╠═════════════════════════════════════╣\n";
		wcout << L"║  add tutorial                       ║\n";
		wcout << L"║  w/d - up/down                      ║\n";
		wcout << L"║  Enter - Cycle between options      ║\n";
		wcout << L"╠═════════════════════════════════════╣\n";
		wcout << L"║  Settings                           ║\n";
		wcout << L"╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢\n";

		printStep(count, activeStep, steps, hConsole, isActivated[count]);

		wcout << L"╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢\n";
		wcout << L"║  Allowed symbols?                   ║\n";

		for (int i = 1; i < 5; i++)
			printStep(count, activeStep, steps, hConsole, isActivated[count]);

		wcout << L"╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢\n";

		printStep(count, activeStep, steps, hConsole, isActivated[count]);

		wcout << L"╠═════════════════════════════════════╣\n";

		printStep(count, activeStep, steps, hConsole, isActivated[count], true);
		
		wcout << L"╚═════════════════════════════════════╝";
	
		action = _getch();
		switch (action)
		{
		case 'w':
		case 'W':
			activeStep--;
			break;
		case 's':
		case 'S':
			activeStep++;
			break;
		case 13: //Enter!
			isActivated[activeStep] = !isActivated[activeStep];
			if (activeStep >= 2 and activeStep <= 4)
				isActivated[1] = false;
			else if (activeStep == 1)
			{
				for (int i = 2; i < 5; i++)
					isActivated[i] = false;
			}
			break;
		default:
			break;
		}

		if (activeStep < 0)
			activeStep = 0;
		if (activeStep > 6)
			activeStep = 6;

		vsBot = isActivated[0];
		for (int i = 1; i < 5; i++)
			bMode[i - 1] = isActivated[i];
		symbolsCanRepeat = isActivated[5];
		ready = isActivated[6];
	}
	
	if (bMode[0])
		mode = 0;
	else
	{
		for (int i = 1; i < 4; i++)
		{
			if (bMode[i])
				mode += 1 * int(pow(10, (i - 1)));
		}
		//OBSOLETE
		//if (bMode[1])
		//	mode += 1;
		//if (bMode[2])
		//	mode += 10;
		//if (bMode[3])
		//	mode += 100;
	}

}

void printStep(int& count, int activeStep, wstring steps[], HANDLE hConsole, bool isActivated, bool isSpecial)
{
	if (count == activeStep)
		SetConsoleTextAttribute(hConsole, 143);
	else
		SetConsoleTextAttribute(hConsole, 7);
	wcout << L"║  ";
	if (isSpecial)
		SetConsoleTextAttribute(hConsole, 150);
	else if (isActivated)
		SetConsoleTextAttribute(hConsole, 47);
	else if (!isActivated)
		SetConsoleTextAttribute(hConsole, 64);
	wcout << steps[count++];
	if (count - 1 == activeStep)
		SetConsoleTextAttribute(hConsole, 143);
	else
		SetConsoleTextAttribute(hConsole, 7);
	wcout << L"  ║\n";
		SetConsoleTextAttribute(hConsole, 7);
}

void pauseMenu()
{
	//CLEAR SCREEN
	//print a grey? bg
	//say "GAME PAUSED"
	//Give options to stop the game
	//idk?

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

|  game name
|------------------------
|  made by team name
|------------------------
|  rules/tutorial
|------------------------
|  settings
|------------------------
|  start

------------------------------------------------

┌┐└┘├┤┬┴┼─│╶╴╷╵
○●

┌────┬─────┐
│ No │╼Yes╾│
└────┴─────┘

┌──┬───┐
│No│Yes│
└──┴───┘

┌────┬─────┐
│╶No╴│╼Yes╾│
└────┴─────┘

No│Yes

 No │╼Yes╾
 
╶No╴│╼Yes╾ no is selected

------------------------------------------------

┌┐└┘├┤┬┴┼─│╶╴╷╵
○●

● numbers (0-7) only
○ numbers only
○ lowercase letters only
○ uppercase letters only
○ letters only
○ lowercase letters and numbers
○ uppercase letters and numbers
○ letters and numbers

╔╗╚╝╠╣╦╩╬═║╟─╢
✶⛤
┌┐└┘├┤┬┴┼─│╶╴╷╵
○●
┅┄
╶No╴│╼Yes╾ no is selected

╔═════════════════╗
║  Code Breakers  ║  //OBSOLETE!!!!!!!!!!
╠═════════════════╩═══════════════════╗
║  C++ game by "✶ GitHub Cultists ✶"  ║
╠═════════════════════════════════════╣
║  add tutorial                       ║
║  w/d - up/down                      ║
║  Enter - Cycle between options      ║
╠═════════════════════════════════════╣
║  Settings                           ║
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢
║  Play against a bot?    -No-/╼Yes╾  ║
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢
║  Allowed symbols?                   ║
║    ● numbers (0-7) only             ║
║    ○ numbers only                   ║
║    ○ lowercase letters only         ║
║    ○ uppercase letters only         ║
║    ○ letters only                   ║
║    ○ lowercase letters and numbers  ║
║    ○ uppercase letters and numbers  ║
║    ○ letters and numbers            ║
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢ //s6
║  Symbols can repeat?    -No-/╼Yes╾  ║
╠═════════════════════════════════════╣ //s7
║            S  T  A  R  T            ║
╚═════════════════════════════════════╝ //cap

╔═════════════════╗
║  Code Breakers  ║
╠═════════════════╩═══════════════════╗
║  C++ game by "✶ GitHub Cultists ✶"  ║
╠═════════════════════════════════════╣
║  add tutorial                       ║
║  w/d - up/down                      ║
║  Enter - Cycle between options      ║
╠═════════════════════════════════════╣
║  Settings                           ║
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢
║  Play against a bot?    -No-/╼Yes╾  ║
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢
║  Allowed symbols?                   ║
║    ○ numbers (0-7) only             ║
║    ○ all numbers                    ║
║    ○ lowercase letters              ║
║    ○ uppercase letters              ║
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢
║  Symbols can repeat?    -No-/╼Yes╾  ║
╠═════════════════════════════════════╣
║            S  T  A  R  T            ║
╚═════════════════════════════════════╝

*/