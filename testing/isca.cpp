#include <isca.h>
#include <internal.h>

#define LOGFILE "./initlog.log"

int ISCA_RegisterForm(void *frm, deletehandler_t fr,
		eventhandler_t evt, 
		drawhandler_t drw = ISCA_StdDraw)
{
	if(!frm)
		return -1;

	ISCA_StdForm *f = (ISCA_StdForm *) frm;

	f->event_handler = evt;
	f->draw = drw;
	f->free = fr;
	
	return 0;
}

int ISCA_Assign(ISCA_Rect *rect, int x, int y, int w, int h)
{
	if (x < 0 || y < 0 || !rect)
		return -1;

	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
	
	return 0;
}


int ISCA_GetWidth() 
{
	return 80;		// temporary
}

int ISCA_GetHeight()
{
	return 25;		// temporary
}


int ISCA_Init() 
{
	ISCA_Log(LOGFILE, "Инициализация ISCA...\n");
	
	ISCA_InitEvents();
	ISCA_InitApplic();

	/* Успешная  инициализация */
	return 0;			
}

int ISCA_Insert(void* dst, void* src)
{
	if(!dst || !src)
		return -1;

	ISCA_StdForm *d = (ISCA_StdForm *) dst;
	ISCA_StdForm *s = (ISCA_StdForm *) src;

	s->next = d->chil;
	d->chil = s;

	s->owner = d;
	d->curr = s;

	ISCA_Log(LOGFILE, "Теперь формой %s владеет  %s\n",
			s->title.c_str(), d->title.c_str());

	return 0;
}

/* Статус прекращения работы не возвращается */
void ISCA_Quit() 
{		
	ISCA_FreeTree(ISCA_Applic);		// Рекурсивное удаление дерева

	ISCA_Log(LOGFILE, "Прекращение работы ISCA...\n");	
}

void ISCA_Run()
{
	bool ExitFlag = false;
	ISCA_Event event;

	while(!ExitFlag) {
		ISCA_PollEvent(&event);

		if(event.type != null) {
			ISCA_SendEvent(ISCA_Applic, &event);

			if(event.type == key &&
			   event.kb == 'q')
				ExitFlag = true;
		}
	}
}


