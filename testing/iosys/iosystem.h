#ifndef _IO_SYS_
#define _IO_SYS_
	#include <iostream>

	/* Запись логов в поток вывода */	
	void ISCA_Log(std::ostream &out, std::string fmt, ...);

	/* Запись логов в файловый поток вывода */	
	void ISCA_Log(std::string filename, std::string fmt, ...);

#endif
