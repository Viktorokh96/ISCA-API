#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "../iscalib/system/isca.h"
#include "./iosystem.h"

struct ISCA_Win {

};

int ISCA_RegisterWindow(ISCA_Win win)
{
	return 0;
}

int ISCA_Init() 
{
	ISCA_Log("./initlog.log", "Инициализация ISCA...\n");

	/* Успешная  инициализация */
	return 0;			
}

/* Статус прекращения работы не возвращается */
void ISCA_Quit() 
{		
	ISCA_Log("./initlog.log", "Прекращение работы ISCA...\n");	
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

ISCA_Win  *win;

void InitForms()
 {
	//win = ISCA_CreateWin(startx, starty, width, height, "title", options); 
	ISCA_RegisterWindow(win);	/* Регистрация формы окна */ 
	ISCA_Insert(win, but);
}

int main(int argc, char const *argv[])
{

	if(ISCA_Init() < 0) {	/* Инициализация оконной системы */
		std::cerr << 
			"Ошибка оконной системы! Завершение работы!" << std::endl;
		exit(1);
	}

	InitForms();			/* Регистрация рабочего окружения */
	
	ISCA_Quit();			/* Прекращение работы оконной системы */
	return 0;
}
