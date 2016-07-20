#include <cstdio>
#include <termios.h>	// temporary
#include <unistd.h>
#include "iosystem.h"

#define MAX_Q 64	// max queue length

ISCA_Event ISCA_GetEvent();
ISCA_Event ISCA_PopQueue();
bool QueueIsEmpty();

struct ISCA_EventQueue {
	ISCA_Event q[MAX_Q];
	int count;
};

static ISCA_EventQueue EvQueue;

int ISCA_ConvertToXY(coord_t coord, short *x, short *y)
{
	if (!x || !y) return -1;

	*x = (short)(coord >> 16);
	*y = (short)(coord);

	return 0;
}

int ISCA_ConvertToCoord(coord_t *coord, short x, short y)
{
	if (!coord) return -1;

	*coord = (((coord_t) (x << 16)) | ((coord_t) y));

	return 0;
}

int ISCA_PollEvent(ISCA_Event *ev)
{
	if (!ev) return -1;

	if(QueueIsEmpty())
		*ev = ISCA_GetEvent();
	else
		*ev = ISCA_PopQueue();

	return 0;
}

int ISCA_PushEvent(ISCA_Event ev)
{
	if (EvQueue.count >= MAX_Q)
		return -1;

	int i;
	EvQueue.count++;

	for(i = EvQueue.count; i > 0; i--)
		EvQueue.q[i] = EvQueue.q[i-1];

	EvQueue.q[0] = ev;

	return 0;
}

int ISCA_InitEvents()
{
	EvQueue.count = 0;

	return 0;
}

bool QueueIsEmpty()
{
	if(EvQueue.count == 0)
		return true;
	else
		return false;
}

ISCA_Event ISCA_GetEvent()
{
	ISCA_Event event;

	//temporary
	event.type = key;	
	
	termios oldt, newt;
	tcgetattr( STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr ( STDIN_FILENO, TCSANOW, &newt);

	event.kb = getchar();	// for debug
	
	tcsetattr ( STDIN_FILENO, TCSANOW, &oldt);

	return event;
}

ISCA_Event ISCA_PopQueue()
{
	EvQueue.count--;
	return EvQueue.q[EvQueue.count];
}
