#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <isca.h>
using std::string;
using std::clog;

#define LOGFILE "./initlog.log"

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
	win->event_handler = NULL;
	win->next = NULL;
	win->chil = NULL;
	win->owner = NULL;
	win->curr = NULL;
	win->options = options;

	win->draw = NULL;
	
	// После постройки формы - необходима регистрация
	ISCA_RegisterForm(win, ISCA_FreeWin, NULL, NULL);

	ISCA_Log(LOGFILE, "Создана форма %s\n", win->title.c_str());

	return win;
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

ISCA_Win  *win1;
ISCA_Win  *win2;
ISCA_Win  *win3;
ISCA_Win  *win4;

void InitForms()
{
	ISCA_Rect rect;

	ISCA_Assign(&rect, 10, 10, 50, 40);	
	win1 = ISCA_CreateWin(rect, "win1", 0); 

	ISCA_Assign(&rect, 20, 20, 80, 50);
	win2 = ISCA_CreateWin(rect, "win2", 0); 
	
	ISCA_Assign(&rect, 20, 20, 90, 60);
	win3 = ISCA_CreateWin(rect, "win3", 0); 

	ISCA_Assign(&rect, 20, 20, 20, 10);
	win4 = ISCA_CreateWin(rect, "win4", 0); 

	ISCA_Insert(ISCA_Applic, win1);
	ISCA_Insert(win1, win2);
	ISCA_Insert(win1, win3);
	ISCA_Insert(win2, win4);
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
