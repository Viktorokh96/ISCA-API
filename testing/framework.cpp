#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdarg>
#include <sstream>
#include <cstdlib>
#include "../iscalib/system/isca.h"

/*################ IO SYSTEM #########################*/

template <class T>
std::string convertNumber(T num)
{
    std::stringstream ss;   // <-- also note namespace qualification
    ss << num;
    return ss.str();
}

void ISCA_Log(std::ostream &out, std::string msg, ...)
{
	va_list p;
	va_start(p, msg);

	std::string buff = "ISCA_LOG:";
	const char *ch = msg.c_str();

	while(*ch) {
		if(*ch == '%') {
			ch++;
			switch(*ch) {
				case 'i':
				case 'd':
				case 'u':
						buff += convertNumber(va_arg(p, int));
					break;

				case 'e':
				case 'f':
				case 'g':
						buff += convertNumber(va_arg(p, double));
					break;

				case 's':
						buff += va_arg(p, char *);
					break;

				case 'c':
						buff.push_back(va_arg(p, int));
					break;
			}
			ch++;
		}

		buff.push_back(*ch);
		ch++;
	}

	out << buff;
}

void ISCA_Log(std::string filename, std::string msg, ...)
{
	std::ofstream out;
	out.open(filename.c_str(), 
		std::ios::out | std::ios::app);

	if(!out) {
		std::cerr << "Не удается открыть файл для ISCA_LOG." 
			<< std::endl;
		return;
	}

	va_list p;
	va_start(p, msg);

	std::string buff = "ISCA_LOG:";
	const char *ch = msg.c_str();

	while(*ch) {
		if(*ch == '%') {
			ch++;
			switch(*ch) {
				case 'i':
				case 'd':
				case 'u':
						buff += convertNumber(va_arg(p, int));
					break;

				case 'e':
				case 'f':
				case 'g':
						buff += convertNumber(va_arg(p, double));
					break;

				case 's':
						buff += va_arg(p, char *);
					break;

				case 'c':
						buff.push_back(va_arg(p, int));
					break;
			}
			ch++;
		}

		buff.push_back(*ch);
		ch++;
	}

	out << buff;

	out.close();
}

/*####################################################*/


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