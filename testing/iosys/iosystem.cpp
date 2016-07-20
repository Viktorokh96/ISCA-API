#include "iosystem.h"
#include <cstdio>

#define MAX_Q 64;	// max queue length

ISCA_Event ISCA_GetEvent();

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

	*ev = ISCA_GetEvent();

	return 0;
}


ISCA_Event ISCA_GetEvent()
{
	ISCA_Event event;
	event.type = key;	// temporary

	event.kb = getchar();	// for debug

	return event;
}
