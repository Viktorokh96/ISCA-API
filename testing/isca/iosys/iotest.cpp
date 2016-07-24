#include <termios.h>
#include <cstdio>
#include <unistd.h>
#include "iosystem.h"
using namespace std;

int main()
{
 	ISCA_Event ev;

	while(true) {
		ISCA_PollEvent(&ev);
		ISCA_Log(clog, "%c\n",ev.kb);
	}
	

	return 0;
}
