#pragma once

#include <vector>
#include "windows.h"
#include "Miscellaneous.h"

using namespace std;

//# Function Declaration                    |>-

/*Prints a table
The table displays:
- The code, hidden or not
- A table containing guessed positions and symbols
- A table containing the 2nd player's guesses
- A table containing only the guessed symbols
*/
void printTable(Code sln, Code guess[], Byte lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln = false, HANDLE hConsole = NULL);

//Returns the input filter
wstring getInputFilter(Byte mode);

//Checks if the input is a part of the allowed symbols
wchar_t returnIfInputIsAllowed(char in, wstring filter, Byte mode = 0);

//Check if pl input is repeating
bool checkIfInputIsUnique(wchar_t in, wstring lastInput, bool symbolsCanRepeat);

//Make the different modes - vs ai/pl
wstring getBotInput(wstring filter, bool symbolsCanRepeat);

//Prints the start menu
void startMenu(Byte &mode, bool& symbolsCanRepeat, bool& vsBot, HANDLE hConsole = NULL);

//Prints the current step
int printStep(int count, int activeStep, wstring step, HANDLE hConsole = NULL, bool isActivated = false, bool isSpecial = false, int specialClr = 7, bool printBorders = true, wstring offset = L"");

//Prints the pause menu
Byte pauseMenu(int continueVal, int exitVal, HANDLE hConsole = NULL);

//Prints the input modes
void printInputMode(Byte mode, bool symbolsCanRepeat, bool vsBot, HANDLE hConsole = NULL);
