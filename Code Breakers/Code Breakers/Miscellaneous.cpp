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

//NOT USED!!! REMOVE IF NOT IN USE
Byte breakCodeIntoDigits(unsigned short int code, unsigned short int position)
{
	return (unsigned short int (code / pow(10, 3 - position)) % 10);
}

//NOT USED!!! REMOVE IF NOT IN USE
unsigned short int combineDigitsIntoCode(Byte digits[])
{
	return (digits[0] * 1000 + digits[1] * 100 + digits[2] * 10 + digits[3]);
}

Code wstringToCode(wstring in)
{
	Code out;
	out.digits[0] = Byte(in[0]);
	out.digits[1] = Byte(in[1]);
	out.digits[2] = Byte(in[2]);
	out.digits[3] = Byte(in[3]);
	return out;
}

wstring codeToWstring(Code in)
{
	wstring out = L"";
	out = in.digits[0];
	out += in.digits[1];
	out += in.digits[2];
	out += in.digits[3];
	return out;
}

unsigned short int verifyUnSIntInRange(unsigned short int greaterThanOrEqual, unsigned short int lesserThanOrEqual, unsigned short int in)
{
	putinUnSInt(in);
	if(in >= greaterThanOrEqual and in <= lesserThanOrEqual)
		return in;
	return verifyUnSIntInRange(greaterThanOrEqual, lesserThanOrEqual, in);
}
