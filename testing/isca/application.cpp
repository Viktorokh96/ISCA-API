#include <application.h>
#include <iosystem.h>

#define LOGFILE "./initlog.log"

void ISCA_ApplicFree(void *apl);

int ISCA_InitApplic();

void ISCA_FreeTree(void *f);

void ISCA_SendEvent(void *frm, ISCA_Event *ev);

ISCA_StdForm *ISCA_Applic;			// Application tree root

void ISCA_ApplicFree(void *apl)
{
	ISCA_StdForm *a = (ISCA_StdForm *) apl;
	delete a;
}

int ISCA_InitApplic()
{
	ISCA_Applic = new ISCA_StdForm;		// Выделение памяти под корень дерева
	if(!ISCA_Applic) return -1;

	ISCA_Rect rect;
	ISCA_Assign(&rect, 0, 0 , ISCA_GetWidth(), ISCA_GetHeight());

	ISCA_InitStdForm(ISCA_Applic, rect, "Applic Main", true);		
	ISCA_RegisterForm(ISCA_Applic, ISCA_ApplicFree, NULL, NULL); 

	ISCA_Applic->free = ISCA_ApplicFree;

	return 0;
}

// Рекурсивное удаление дерева форм
void ISCA_FreeTree(void *f)
{
	ISCA_StdForm *tmp, *frm = (ISCA_StdForm *) f;

	ISCA_Log(LOGFILE, "Удаление дерева с вершины %s\n", frm->title.c_str());
	while(frm->chil) {
		tmp = (ISCA_StdForm *) frm->chil;
		frm->chil = ((ISCA_StdForm *) (frm->chil))->next;
		ISCA_FreeTree(tmp);
	}
	
	ISCA_Log(LOGFILE, "Удаление вершины %s\n", frm->title.c_str());
	ISCA_FreeForm(frm);
}

void ISCA_SendEvent(void *frm, ISCA_Event *ev)
{
	ISCA_StdForm *tmp, *f = (ISCA_StdForm *) frm;

	tmp = (ISCA_StdForm *) f->chil;
	while(tmp) {
		ISCA_SendEvent(tmp, ev);
		tmp = (ISCA_StdForm *)tmp -> next;
	}

	ISCA_StdEventHandl(f, ev);
	if(f->event_handler)
		f->event_handler(f, ev);
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


