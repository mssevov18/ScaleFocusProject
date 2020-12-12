#pragma once

//Structures and custom types             |>-

using Byte = unsigned char; 
//capital 'B' due to redefinition issues

struct Code
{
	Byte digits[4];
};

//Function Declaration                    |>-

//Function to input and check an integer
void putinUnSInt(unsigned short int& input);

//Breaks code into a digit (position = { 0, 1, 2, 3 })
Byte breakIntoDigit(unsigned short int code, unsigned short int position);

//Combines digits into a code
unsigned short int combineDigitsIntoCode(Byte digits[]);