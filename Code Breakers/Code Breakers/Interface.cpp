//# Preprocessor directives, Using, etc     |>-
#include <iostream>
#include "Miscellaneous.h"
#include "Interface.h"
#include "windows.h"
#include "stdlib.h"
#include "conio.h"
#include "math.h"

using namespace std;

//# Function Definition                     |>-

void printTable(Code sln, Code guess[], Byte lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln, HANDLE hConsole)
{
	SetConsoleTextAttribute(hConsole, 7); //Black bg; white txt
	wcout << L"                   ┏━━━━━━━━━━━━━━┓\n                   ┃  ";
	SetConsoleTextAttribute(hConsole, 14);
	if (showSln)
		wcout << "?  ?  ?  ?  "; //Represents the solution
	else
	{
		for (size_t i = 0; i < 4; i++)
			wcout << char(sln.digits[i]) << L"  "; //If show solution is true -> show the solution
	}
	SetConsoleTextAttribute(hConsole, 7);
	wcout << L"┃\n                   ┗━━━━━━━━━━━━━━┛\n";
	wcout << L"┏━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓   ┏━━━━━━━━━━━━━━┓\n";
	wcout << L"┃   Guessed    ┃   ┃   Player     ┃   ┃   Guessed    ┃\n";
	wcout << L"┃   Positions  ┃   ┃   Two's      ┃   ┃   symbols    ┃\n";
	wcout << L"┃   & symbols  ┃   ┃   Guesses    ┃   ┃   only       ┃\n";
	wcout << L"┣━━━━━━━━━━━━━━┫   ┣━━━━━━━━━━━━━━┫   ┣━━━━━━━━━━━━━━┫\n";
	for (Byte i = 0; i < 13 - lives; i++)
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
			wcout << char(guess[i].digits[j]) << "  ";
		SetConsoleTextAttribute(hConsole, 7); 
		wcout << L"┃   ┃  ";
		SetConsoleTextAttribute(hConsole, 13);
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

wstring getInputFilter(Byte mode)
{
	//mode
	//=0 - numbers (0-7) only
	//+1 - numbers 
	//+10 - lowercase letters
	//+100 - uppercase letters

	bool* bModePtr;
	bool bMode[4];
	bModePtr = bMode;
	bModePtr = convertModeToBMode(mode);

	if (bModePtr[0])
		return L"01234567";
	wstring filter = L"";
	if (bModePtr[1])
		filter = L"0123456789";
	if (bModePtr[2])
		filter += L"qwertyuiopasdfghjklzxcvbnm";
	if (bModePtr[3])
		filter += L"QWERTYUIOPASDFGHJKLZXCVBNM";

	return filter;
}

wchar_t returnIfInputIsAllowed(char in, wstring filter, Byte mode)
{
	for (size_t i = 0; i < filter.length(); i++)
	{
		if (in == filter[i])
			return in;
	}

	return NULL;
}

bool checkIfInputIsUnique(wchar_t in, wstring lastInput, bool symbolsCanRepeat)
{
	if (symbolsCanRepeat)
		return true;
	for (size_t j = 0; j < lastInput.length(); j++)
	{
		if (lastInput[j] == NULL)
			continue;
		if (lastInput[j] == in)
			return false;
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

void printInputMode(Byte mode, bool symbolsCanRepeat, bool vsBot, HANDLE hConsole)
{
	SetConsoleTextAttribute(hConsole, 11);
	wcout << "Input Type: ";

	bool* bModePtr;
	bool bMode[4];
	bModePtr = bMode;
	bModePtr = convertModeToBMode(mode);

	int amount = 1;

	int count = 0;
	wstring sMode[4];

	if (bModePtr[0])
		sMode[count++] = L"Numbers 0 to 7 only";
	if (bModePtr[1])
		sMode[count++] = L"All numbers";
	if (bModePtr[2])
		sMode[count++] = L"All lowercase letters";
	if (bModePtr[3])
		sMode[count++] = L"All uppercase letters";

	for (int i = 0; i < count; i++)
	{
		SetConsoleTextAttribute(hConsole, 6);
		wcout << sMode[i];
		if (i + 1 != count)
		{
			SetConsoleTextAttribute(hConsole, 11);
			wcout << " and ";
		}
	}

	SetConsoleTextAttribute(hConsole, 11);
	wcout << L"\nSymbols ";
	
	SetConsoleTextAttribute(hConsole, 6);
	if (symbolsCanRepeat)
		wcout << L"can";
	else
		wcout << L"can't";
	
	SetConsoleTextAttribute(hConsole, 11);
	wcout << L" repeat";
	
	SetConsoleTextAttribute(hConsole, 11);
	wcout << L"\nPlaying against ";
	
	SetConsoleTextAttribute(hConsole, 6);
	if (vsBot)
		wcout << L"a Bot\n";
	else
		wcout << L"another Player\n";
	
	SetConsoleTextAttribute(hConsole, 7);
}

void startMenu(Byte &mode, bool &symbolsCanRepeat, bool &vsBot, HANDLE hConsole)
{
	bool ready = false;
	int activeStep = 0;
	char action = NULL;
	int count = 0;
	bool isActivated[7];

	mode = 0;
	symbolsCanRepeat = false;
	vsBot = false;

	bool* bModePtr;
	bool bMode[4];
	bModePtr = bMode;
	bModePtr = convertModeToBMode(mode);

	wstring steps[] = {
		L"Play against a bot?    ",
		L" numbers (0-7) only           ",
		L" numbers                      ",
		L" lowercase letters            ",
		L" uppercase letters            ",
		L"Symbols can repeat?    ",
		L"          S  T  A  R  T          "
	};

	isActivated[0] = vsBot;
	for (int i = 1; i < 5; i++)
		isActivated[i] = bModePtr[i - 1];
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
		wcout << L"║  w/d - up/down                      ║\n";
		wcout << L"║  Enter - Toggle setting             ║\n";
		
		printStep(-1, -3, L"Yes - This option is turned on   ", hConsole, true, false);
		printStep(-1, -3, L"No - This option is turned off   ", hConsole, false, false);

		wcout << L"║  For more information on how the    ║\n";
		wcout << L"║  game is played, read the tutorial  ║\n";
		wcout << L"║  in the game directory              ║\n";
		wcout << L"╠═════════════════════════════════════╣\n";
		wcout << L"║  Settings                           ║\n";
		wcout << L"╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢\n";

		count = printStep(count, activeStep, steps[count] + (isActivated[count] ? L"    /╼Yes╾" : L"-No-/     "), hConsole, isActivated[count]);

		wcout << L"╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢\n";
		wcout << L"║  Allowed symbols?                   ║\n";

		for (int i = 1; i < 5; i++)
			count = printStep(count, activeStep, (isActivated[count] ? L"●" : L"○") + steps[count], hConsole, isActivated[count], false, 7, true, L"  ");

		wcout << L"╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢\n";

		count = printStep(count, activeStep, steps[count] + (isActivated[count] ? L"    /╼Yes╾" : L"-No-/     "), hConsole, isActivated[count]);

		wcout << L"╠═════════════════════════════════════╣\n";

		printStep(count, activeStep, steps[count], hConsole, isActivated[count], true, 150);

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
			bModePtr[i - 1] = isActivated[i];
		symbolsCanRepeat = isActivated[5];
		ready = isActivated[6];
	}
	
	mode = convertBModeToMode(bModePtr);
}

int printStep(int count, int activeStep, wstring step, HANDLE hConsole, bool isActivated, bool isSpecial, int specialClr, bool printBorders, wstring offset)
{
	if (count == activeStep)
		SetConsoleTextAttribute(hConsole, 143);
	else
		SetConsoleTextAttribute(hConsole, 7);
	if (printBorders)
		wcout << L"║  " << offset;
	if (isSpecial)
		SetConsoleTextAttribute(hConsole, specialClr);
	else if (isActivated)
		SetConsoleTextAttribute(hConsole, 47);
	else if (!isActivated)
		SetConsoleTextAttribute(hConsole, 64);
	wcout << step;
	if (count == activeStep)
		SetConsoleTextAttribute(hConsole, 143);
	else
		SetConsoleTextAttribute(hConsole, 7);
	if (printBorders)
		wcout << L"  ║";

	wcout << L'\n';
	SetConsoleTextAttribute(hConsole, 7);
	
	return (count + 1);
}

Byte pauseMenu(int continueVal, int exitVal, HANDLE hConsole)
{
	bool paused = true;
	char action = NULL;
	wstring offset = L"\t\t\t";
	int clr = 112;
	while (paused)
	{
		SetConsoleTextAttribute(hConsole, 143);
		system("CLS");
		wcout << "\n\n\n\n";

		wcout << offset << "\t";
		printStep(-1, -3, L"PAUSED", hConsole, false, true, clr, false);
		wcout << offset;
		printStep(-1, -3, L"Press Enter to continue", hConsole, false, true, clr, false);
		if (exitVal != -1)
		{
			wcout << offset;
			printStep(-1, -3, L"Press Escape to end the game", hConsole, false, true, clr, false);
		}

		action = _getch();
		SetConsoleTextAttribute(hConsole, 7);
		switch (action)
		{
		case 13: //Enter
			return continueVal;
		case 27: //Escape
			if (exitVal != -1)
				return exitVal;
		default:
			break;
		}
	}
	
	SetConsoleTextAttribute(hConsole, 7);
	return continueVal;
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
║  Play against a bot?    -No-/╼Yes╾  ║ 0
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢
║  Allowed symbols?                   ║
║    ○ numbers (0-7) only             ║ 1
║    ○ all numbers                    ║ 2
║    ○ lowercase letters              ║ 3
║    ○ uppercase letters              ║ 4
╟──┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄──╢
║  Symbols can repeat?    -No-/╼Yes╾  ║ 5
╠═════════════════════════════════════╣
║            S  T  A  R  T            ║ 6
╚═════════════════════════════════════╝ //cap

*/