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

void ISCA_StdFree(void *ths)
{
	if(!ths) return;
	ISCA_StdForm *frm = (ISCA_StdForm *) ths;

	ISCA_Log(LOGFILE, "Освобождение формы %s\n", frm -> title.c_str());

	frm -> title.~string();
	delete ths;		// Освобождение формы
}

int ISCA_RegisterForm(void *frm, eventhandler_t evt = ISCA_StdEventHandl,
			drawhandler_t drw = ISCA_StdDraw,
			deletehandler_t fr = ISCA_StdFree)
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

	ISCA_Applic = new ISCA_StdForm;		// Выделение памяти под корень дерева

	ISCA_Rect rect;
	ISCA_Assign(&rect, 0, 0 , ISCA_GetWidth(), ISCA_GetHeight());
	
	ISCA_Applic->owner = NULL;
	ISCA_Applic->next = NULL;
	ISCA_Applic->chil = NULL;
	ISCA_Applic->curr = NULL;

	ISCA_Applic->free = ISCA_StdFree;

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
	frm->free(frm);
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
	win->event_handler = NULL;
	win->draw = NULL;
	win->free = NULL;

	ISCA_Log(LOGFILE, "Создана форма %s\n", win->title.c_str());

	return win;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

ISCA_Win  *win;

void InitForms()
{
	ISCA_Rect rect;

	ISCA_Assign(&rect, 10, 10, 50, 40);	
	win = ISCA_CreateWin(rect, "first win", 0); 

	// После постройки формы - необходима регистрация
	ISCA_RegisterForm(win);	/* Регистрация формы окна */ 

	ISCA_Insert(ISCA_Applic, win);
}

int main(int argc, char const *argv[])
{

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
