#ifndef _IO_SYS_
#define _IO_SYS_
	#include <sys/types.h>
	#include "./log.h"

enum event_type { key, mouse, cmd, null }; 

typedef u_int16_t kb_t;	
typedef u_int32_t coord_t;

struct ISCA_Event {
	event_type type;		// type of event
	union {
		kb_t kb;		// Keybord code
		coord_t coord;		// Mouse coordinats
	};
};

int ISCA_ConvertToXY(coord_t coord, short *x, short *y);

int ISCA_ConvertToCoord(coord_t *coord, short x, short y);

int ISCA_PollEvent(ISCA_Event *ev);

int ISCA_PushEvent(ISCA_Event ev);

int ISCA_InitEvents();

#endif
