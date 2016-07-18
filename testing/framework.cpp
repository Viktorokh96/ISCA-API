#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "../iscalib/system/isca.h"
#include "./iosys/iosystem.h"
using std::string;

#define LOGFILE "./initlog.log"

struct ISCA_Rect {
	int x,y;	// Начальные координаты формы
	int w,h;	// Ширина и высота формы
};

typedef unsigned int opt_t;
typedef void (*drawhandler_t)(void *ths);
typedef void (*eventhandler_t)(void *ths, void *event);
typedef void (*deletehandler_t)(void *ths);

/* Стандартные поля формы:
 * next - слудующая форма (соседний узел в дереве), 
 * которая принадлежит владельцу этого окна.
 * owner - владелец текущей формы.
 * chil - указатель на голову спискa потомков формы.
 * curr - указатель на текущую форму (для поддержки модальности).
 * event_handler - метод обработчика событий.
 * draw - метод отрисовки формы.
*/
#define STD_FORM\
	void *next;\
	void *owner;\
	void *chil;\
	void *curr;\
	std::string title;\
	ISCA_Rect rect;\
	eventhandler_t event_handler;\
	drawhandler_t draw;\
	deletehandler_t free;\


struct ISCA_StdForm {
	STD_FORM
} *ISCA_Applic;			// Корень дерева форм приложения

struct ISCA_Win {
	STD_FORM
	opt_t options;
};

struct ISCA_Button {
	STD_FORM
};

void ISCA_StdEventHandl(void *ths, void *event)
{
	return;
}

void ISCA_StdDraw(void *ths)
{
	return;
}

void ISCA_ApplicFree(void *apl)
{
	ISCA_StdForm *a = (ISCA_StdForm *) apl;
	delete a;
}

int ISCA_RegisterForm(void *frm, deletehandler_t fr,
		eventhandler_t evt = ISCA_StdEventHandl,
		drawhandler_t drw = ISCA_StdDraw
)
{
	if(!frm)
		return -1;

	ISCA_StdForm *f = (ISCA_StdForm *) frm;

	f->event_handler = evt;
	f->draw = drw;
	f->free = fr;
	
	return 0;
}

void ISCA_FreeForm(void *frm)
{
	ISCA_StdForm *f = (ISCA_StdForm *) frm;

	ISCA_Log(LOGFILE, "Освобождение формы %s\n",
			f->title.c_str());

	f->free(f);
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

	ISCA_Applic = new ISCA_StdForm;		// Выделение памяти под корень дерева

	ISCA_Rect rect;
	ISCA_Assign(&rect, 0, 0 , ISCA_GetWidth(), ISCA_GetHeight());
	
	ISCA_Applic->owner = NULL;
	ISCA_Applic->next = NULL;
	ISCA_Applic->chil = NULL;
	ISCA_Applic->curr = NULL;

	ISCA_Applic->free = ISCA_ApplicFree;

	ISCA_Applic->title = "Applic Main";

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

/* Статус прекращения работы не возвращается */
void ISCA_Quit() 
{		
	ISCA_FreeTree(ISCA_Applic);		// Рекурсивное удаление дерева

	ISCA_Log(LOGFILE, "Прекращение работы ISCA...\n");	
}

void ISCA_Run()
{
/*
 * while(!ExitFlag) {
 *	check events
 *	send events to main form
 *	ExitFlag = exit event?
 *	repeat	
 * }
 */		
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

void ISCA_FreeWin(void *win)
{
	ISCA_Win *w = (ISCA_Win *) win;
	delete w;
}

ISCA_Win *ISCA_CreateWin(ISCA_Rect rect, std::string title, opt_t options)
{
	ISCA_Win *win = new ISCA_Win;
	if (!win)
		return NULL;
	
	win->title = title;		
	win->rect = rect;
	win->next = NULL;
	win->chil = NULL;
	win->owner = NULL;
	win->curr = NULL;
	win->options = options;

	win->event_handler = NULL;
	win->draw = NULL;
	
	// После постройки формы - необходима регистрация
	ISCA_RegisterForm(win, ISCA_FreeWin);	/* Регистрация формы окна */ 

	ISCA_Log(LOGFILE, "Создана форма %s\n", win->title.c_str());

	return win;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

ISCA_Win  *win;
ISCA_Win  *win1;
ISCA_Win  *win2;
ISCA_Win  *win3;

void InitForms()
{
	ISCA_Rect rect;

	ISCA_Assign(&rect, 10, 10, 50, 40);	
	win = ISCA_CreateWin(rect, "win", 0); 

	ISCA_Assign(&rect, 20, 20, 80, 50);
	win1 = ISCA_CreateWin(rect, "win1", 0); 
	
	ISCA_Assign(&rect, 20, 20, 90, 60);
	win2 = ISCA_CreateWin(rect, "win2", 0); 

	ISCA_Assign(&rect, 20, 20, 20, 10);
	win3 = ISCA_CreateWin(rect, "win3", 0); 

	ISCA_Insert(ISCA_Applic, win);
	ISCA_Insert(win, win1);
	ISCA_Insert(win1, win2);
	ISCA_Insert(win1, win3);
}

int main(int argc, char const *argv[])
{
	ISCA_Log(LOGFILE, "\n------------------------------------------------------\n");

	if(ISCA_Init() < 0) {	/* Инициализация оконной системы */
		std::cerr << 
			"Ошибка оконной системы! Завершение работы!" << std::endl;
		exit(1);
	}

	InitForms();			/* Регистрация рабочего окружения */
	
	ISCA_Run();			/* Главный цикл выполнения приложения */
	
	ISCA_Quit();			/* Прекращение работы оконной системы */
	return 0;
}
