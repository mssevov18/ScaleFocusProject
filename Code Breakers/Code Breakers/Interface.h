#pragma once

#include "windows.h"
#include <vector>

using namespace std;

void printTable(Code sln, Code guess[], unsigned short int lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln = false, HANDLE hConsole = NULL);

wstring getInputFilter(unsigned short int mode);

//Check if the char is a part of the allowed characters
wchar_t returnIfInputIsAllowed(char in, wstring filter, unsigned short  int mode = 0);

//Mode
//0 - numbers (0-7) only
//1 - numbers only
//2 - lowercase letters only
//3 - uppercase letters only
//4 - letters only
//5 - lowercase letters and numbers
//6 - uppercase letters and numbers
//7 - letters and numbers

//NEW MODE
//=0 - numbers (0-7) only
//+1 - numbers 
//+10 - lowercase letters
//+100 - uppercase letters

//Check if pl input is repeating
bool checkIfInputIsUnique(wchar_t in, wstring lastInput, bool symbolsCanRepeat);

//Make the different modes - vs ai/pl
wstring getBotInput(wstring filter, bool symbolsCanRepeat);

//start menu
void startMenu(unsigned short int& mode, bool& symbolsCanRepeat, bool& vsBot, HANDLE hConsole = NULL);

int printStep(int count, int activeStep, wstring step, HANDLE hConsole = NULL, bool isActivated = false, bool isSpecial = false, int specialClr = 7, bool printBorders = true);

//pause menu
unsigned short int pauseMenu(int continueVal, int exitVal, HANDLE hConsole = NULL);

//print mode
void printInputMode(unsigned short int mode, bool symbolsCanRepeat, bool vsBot, HANDLE hConsole = NULL);

//tutorial
