//# Preprocessor directives, Using, etc     |>-
#include <iostream>
#include "Miscellaneous.h"
#include "windows.h"
#include "conio.h"
#include "math.h"

using namespace std;

//# Function Definition                     |>-

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

bool* convertModeToBMode(Byte mode)
{
	static bool bMode[4] = { false, false, false, false };

	if (mode == 0)
		bMode[0] = true;
	else
	{
		for (int i = 1; i < 4; i++)
		{
			if (mode % 2 == 1)
				bMode[i] = true;
			mode /= 10;
		}
	}

	return bMode;
}

Byte convertBModeToMode(bool* bMode)
{
	Byte mode = 0;

	if (!bMode[0])
	{
		for (int i = 1; i < 4; i++)
		{
			if (bMode[i])
				mode += 1 * int(pow(10, (i - 1)));
		}
	}

	return mode;
}
