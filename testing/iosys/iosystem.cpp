#include <cstdarg>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "iosystem.h"

#define PARSE_MSG(buff, msg)\
	do {\
	const char *ch = msg.c_str();\
\
		va_list p;\
		va_start(p, msg);\
\
		while(*ch) {\
			if(*ch == '%') {\
				ch++;\
				switch(*ch) {\
					case 'i':\
					case 'd':\
					case 'u':\
						buff += convertNumber(va_arg(p, int));\
						break;\
\
					case 'e':\
					case 'f':\
					case 'g':\
						buff += convertNumber(va_arg(p, double));\
						break;\
\
					case 's':\
						buff += va_arg(p, char *);\
						break;\
\
					case 'c':\
						buff.push_back(va_arg(p, int));\
						break;\
				}\
				ch++;\
			}\
\
			buff.push_back(*ch);\
			ch++;\
		}\
\
		va_end(p);\
	} while(0);

template <class T>
std::string convertNumber(T num)
{
    std::stringstream ss; 
    ss << num;
    return ss.str();
}

void ISCA_Log(std::ostream &out, std::string msg, ...)
{
	std::string buff = "ISCA_LOG:";

	PARSE_MSG(buff,msg)

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

	std::string buff = "ISCA_LOG:";

	PARSE_MSG(buff,msg)

	out << buff;

	out.close();
}

