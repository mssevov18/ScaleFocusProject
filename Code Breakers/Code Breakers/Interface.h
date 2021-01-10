#pragma once

#include "windows.h"
#include <vector>

using namespace std;

void printTable(Code sln, Code guess[], unsigned short int lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln = false, HANDLE hConsole = NULL);

wstring getInputFilter(unsigned short int mode);

//Check if the char is a part of the allowed characters
wchar_t checkIfInputIsAllowed(char in, wstring filter, unsigned short  int mode = 0);

//Mode
//0 - numbers (0-7) only
//1 - numbers only
//2 - lowercase letters only
//3 - uppercase letters only
//4 - letters only
//5 - lowercase letters and numbers
//6 - uppercase letters and numbers
//7 - letters and numbers

//Check if pl input is repeating
bool checkIfInputIsUnique(char in, wstring lastInput, bool symbolsCanRepeat);

//Make the different modes - vs ai/pl
wstring getBotInput(wstring filter, bool symbolsCanRepeat);

//start menu
void startMenu(unsigned short int& mode, bool& symbolsCanRepeat, bool& vsBot, HANDLE hConsole = NULL);

void printStep(int& count, int activeStep, wstring steps[], HANDLE hConsole, bool isActivated = false, bool isSpecial = false);

//pause menu
void pauseMenu();

//print mode
void printInputMode(unsigned short int mode, bool symbolsCanRepeat, bool vsBot);

/*
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