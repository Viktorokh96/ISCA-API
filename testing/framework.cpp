#include <iostream>
#include <string>
#include <unistd.h>
#include "../iscalib/system/isca.h"

void ISCA_Log(std::ostream &out, char *msg)
{
	out << "ISCA_LOG: " << msg << std::endl;
}

int ISCA_Init() 
{
	ISCA_Log(std::clog,"Инициализация ISCA...");

	/* Успешная  инициализация */
	return 0;			
}

/* Статус прекращения работы не возвращается */
void ISCA_Quit() 
{		
	ISCA_Log(std::clog,"Прекращение работы ISCA...");	
}

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

int main(int argc, char const *argv[])
{
	if(ISCA_Init() < 0) {	/* Инициализация оконной системы */
		std::cerr << 
			"Ошибка оконной системы! Завершение работы!" << std::endl;
		exit(1);
	}
	

	ISCA_Quit();			/* Прекращение работы оконной системы */
	return 0;
}