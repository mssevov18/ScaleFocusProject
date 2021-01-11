#pragma once

#include <vector>
#include "windows.h"
#include "Miscellaneous.h"

using namespace std;

//# Function Declaration                    |>-

void printTable(Code sln, Code guess[], Byte lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln = false, HANDLE hConsole = NULL);

wstring getInputFilter(Byte mode);

//Check if the char is a part of the allowed characters
wchar_t returnIfInputIsAllowed(char in, wstring filter, Byte mode = 0);

//Check if pl input is repeating
bool checkIfInputIsUnique(wchar_t in, wstring lastInput, bool symbolsCanRepeat);

//Make the different modes - vs ai/pl
wstring getBotInput(wstring filter, bool symbolsCanRepeat);

//start menu
void startMenu(Byte &mode, bool& symbolsCanRepeat, bool& vsBot, HANDLE hConsole = NULL);

int printStep(int count, int activeStep, wstring step, HANDLE hConsole = NULL, bool isActivated = false, bool isSpecial = false, int specialClr = 7, bool printBorders = true);

//pause menu
Byte pauseMenu(int continueVal, int exitVal, HANDLE hConsole = NULL);

//print mode
void printInputMode(Byte mode, bool symbolsCanRepeat, bool vsBot, HANDLE hConsole = NULL);
