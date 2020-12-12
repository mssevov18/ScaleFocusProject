//Preprocessor directives, Using, etc     |>-
#include <iostream>
#include "Miscellaneous.h"
#include "windows.h"
#include "conio.h"
#include "math.h"

using namespace std;

//Function Definition                     |>-

void putinUnSInt(unsigned short int& input)
{
	wcin >> input;
	while (!wcin)
	{
		//Err -> input was not of type int
		wcin.clear();
		wcin.ignore();
		wcin >> input;
	}
}

Byte breakIntoDigit(unsigned short int code, unsigned short int position)
{
	return (unsigned short int (code / pow(10, 3 - position)) % 10);
}

unsigned short int combineDigitsIntoCode(Byte digits[])
{
	return (digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3]);
}