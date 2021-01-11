#pragma once

using namespace std;

//# Structures and custom types             |>-

using Byte = unsigned char; 
//capital 'B' due to redefinition issues

struct Code
{
	Byte digits[4];
};

//# Function Declaration                    |>-

//Wstring to Code
Code wstringToCode(wstring in);

//Code to Wstring
wstring codeToWstring(Code in);

//mode to boolMode
bool* convertModeToBMode(Byte mode);

//boolMode to mode
Byte convertBModeToMode(bool* bMode);