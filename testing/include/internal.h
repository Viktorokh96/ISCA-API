#ifndef INTERNAL_H
#define INTERNAL_H

#include <iosystem.h>

void ISCA_ApplicFree(void *apl);

int ISCA_InitApplic();

void ISCA_FreeTree(void *f);

void ISCA_SendEvent(void *frm, ISCA_Event *ev);

#endif
