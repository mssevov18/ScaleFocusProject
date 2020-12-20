#pragma once

#include "windows.h"
#include <vector>

using namespace std;

void printTable(Code sln, Code guess[], unsigned short int lives, wstring lastInput, bool NumAndPos[14][4], bool Num[14][4], bool showSln = false, HANDLE  hConsole = NULL);