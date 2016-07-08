#ifndef WINDLG_H
#define WINDLG_H

	#include <string>
	#include <vector>
	#include <unistd.h>
	#include <stdio.h>
	#include "../lang/lang.h"
	#include "../screen/screen.h"
	#include "../system/system_defines.h"

	/*Styles*/
	#define WHITE_WIN TEXT_WHITE_BLACK
	#define RED_WIN TEXT_RED_BLACK
	#define GREEN_WIN TEXT_GREEN_BLACK
	#define BLUE_WIN TEXT_BLUE_BLACK
	#define YELLOW_WIN TEXT_YELLOW_BLACK
	#define MAGENTA_WIN TEXT_MAGENTA_BLACK
	#define CYAN_WIN TEXT_CYAN_BLACK

	struct MENSTR {
		bool			no_border;

		unsigned int	posX,
						posY,
						posXmax,
						posYmax,
						returned_x,
						returned_y;
	};

	unsigned int menu_winV2(MENSTR*, std::string, std::vector <std::string>, int);

#endif
