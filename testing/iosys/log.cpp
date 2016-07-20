#include <cstdarg>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "iosystem.h"

void ISCA_Log(std::ostream &out, std::string fmt, ...)
{
	char sbf[256]; 
	std::string buff = "ISCA_LOG:";

	va_list ap;
	va_start(ap, fmt);
	vsprintf(sbf, fmt.c_str(), ap);
	va_end(ap);

	buff += sbf;

	out << buff;
}

void ISCA_Log(std::string filename, std::string fmt, ...)
{
	char sbf[256]; 
	std::ofstream out;
	out.open(filename.c_str(), 
		std::ios::out | std::ios::app);

	if(!out) {
		std::cerr << "Не удается открыть файл для ISCA_LOG." 
			<< std::endl;
		return;
	}

	std::string buff = "ISCA_LOG:";

	va_list ap;
	va_start(ap, fmt);
	vsprintf(sbf, fmt.c_str(), ap);
	va_end(ap);

	buff += sbf;

	out << buff;

	out.close();
}

