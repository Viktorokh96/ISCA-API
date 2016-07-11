#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "../iscalib/system/isca.h"
#include "./iosys/iosystem.h"

#define LOGFILE "./initlog.log"

struct ISCA_Rect {
	int x,y;	// Начальные координаты формы
	int w,h;	// Ширина и высота формы
};

/* Стандартные поля формы:
 * chil - список потомков формы
 * curr - указатель на текущую форму (для поддержки модальности)
*/
#define STD_FORM\
	void *chil;\
	void *curr;\
	ISCA_Rect rect;\

struct ISCA_StdForm {
	STD_FORM
};

struct ISCA_Win {
	STD_FORM
};

struct ISCA_Button {
	STD_FORM
};

int ISCA_RegisterWindow(ISCA_Win *win)
{
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

int ISCA_Init() 
{
	ISCA_Log(LOGFILE, "Инициализация ISCA...\n");

	/* Успешная  инициализация */
	return 0;			
}

int ISCA_Insert(void* dst, void* src)
{
	ISCA_Log(LOGFILE, "Вставка одной формы в другую\n");
	return 0;
}

/* Статус прекращения работы не возвращается */
void ISCA_Quit() 
{		
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

ISCA_Win  *win;
ISCA_Button *but;

void InitForms()
 {
	ISCA_Rect rect;

	ISCA_Assign(&rect, 10, 10, 50, 40);	
	//win = ISCA_CreateWin(rect, "title", options); 
	
	ISCA_Assign(&rect, 20, 20, 5, 2);
	//but = ISCA_CreateButton(rect, "text", B_OK);

	ISCA_Insert(win, but);		/* Вставка одной формы в другую */

	// После постройки формы - необходима регистрация
	ISCA_RegisterWindow(win);	/* Регистрация формы окна */ 
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
