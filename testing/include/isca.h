#ifndef ISCA_H
#define ISCA_H

#include <iosystem.h>
#include <stdform.h>
#include <types.h>

int ISCA_RegisterForm(void *frm, deletehandler_t fr,
			eventhandler_t evt, 
			drawhandler_t drw);

int ISCA_Assign(ISCA_Rect *rect, int x, int y, int w, int h);

int ISCA_GetWidth();

int ISCA_GetHeight();

int ISCA_Init();

void ISCA_Quit();

void ISCA_Run();

int ISCA_Insert(void* dst, void* src);

#endif
