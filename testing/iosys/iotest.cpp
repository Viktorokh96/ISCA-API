#include <termios.h>
#include <cstdio>
#include <unistd.h>
#include "iosystem.h"
using namespace std;

int main()
{
 	ISCA_Event ev;

	termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr ( STDIN_FILENO, TCSANOW, &newt);

	while(true) {
		ISCA_PollEvent(&ev);
		ISCA_Log(clog, "%c\n",ev.kb);
	}
	
	tcsetattr ( STDIN_FILENO, TCSANOW, &oldt);

	return 0;
}
