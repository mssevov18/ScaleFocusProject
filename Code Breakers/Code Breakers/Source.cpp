//Preprocessor directives, Using, Global Variables         |
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <conio.h>

using namespace std;

//Int Main                                                 |

int main()
{
	int a = _setmode(_fileno(stdout), _O_U16TEXT);
	a = _setmode(_fileno(stdin), _O_U16TEXT);


}

/*                                              *\
 *                                              *
 *                                              *
 *                                              *
 *                                              *
 *                                              *
 *                                              *
 *                                              *
\*                                              */