#pragma once

using namespace std;

//Structures and custom types             |>-

using Byte = unsigned char; 
//capital 'B' due to redefinition issues

struct Code
{
	Byte digits[4];
};

//Function Declaration                    |>-

//NOT USED!!! REMOVE IF NOT IN USE
//Function to input and check an integer
void putinUnSInt(unsigned short int& input);

//NOT USED!!! REMOVE IF NOT IN USE
//Breaks code into a digit (position = { 0, 1, 2, 3 })
Byte breakCodeIntoDigits(unsigned short int code, unsigned short int position);

//NOT USED!!! REMOVE IF NOT IN USE
//Combines digits into a code
unsigned short int combineDigitsIntoCode(Byte digits[]);

//Wstring to Code
Code wstringToCode(wstring in);

//Code to Wstring
wstring codeToWstring(Code in);

//Num and pos bool arr row init

//Verify unsigned short int in a range
unsigned short int verifyUnSIntInRange(unsigned short int greaterThanOrEqual, unsigned short int lesserThanOrEqual, unsigned short int in = NULL);