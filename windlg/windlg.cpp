#include "windlg.h"

using namespace std;

const string win_ver = "2.0";

void windlg_ver() {
	erase();
	printw("|WinDLG API----------------------|\n");
	printw("|Version:                     2.0|\n");
	printw("|                                |\n");
	printw("|Autor:         Dmitriy Volchenko|\n");
	printw("|E-mail:     dima201246@gmail.com|\n");
	printw("|                                |\n");
	printw("|                                |\n");
	printw("|Build date: %s %s|\n", __DATE__, __TIME__);
	printw("|--------------------------------|\n");
	getch();
}

/*unsigned int active_input(bool	resize, unsigned int	&firstItem, unsigned int	&lastItem,) {

}*/

void balance_vector(vector <string>	&items, unsigned int	max_l) {
	string			temp_item;

	for (unsigned int	i	= 0; i < items.size(); i++) {	// Добавление пробелов в конец для выравнивания
		temp_item	= items[i];

		if (llength(temp_item) < max_l) {
			while (max_l != llength(temp_item))
				temp_item += " ";
		} else if (llength(temp_item) > max_l) {
			temp_item.erase(max_l, llength(temp_item));
		}

		items[i]	= temp_item;
	}
}

unsigned int find_max_length(vector <string>	&items) {	// Поиск самой длиной строки в векторе
	unsigned int	max_l;

	string			temp_item;

	max_l			= 0;

	for (unsigned int	i	= 0; i < items.size(); i++) {	// Поиск самой длинной строки
		temp_item	= items[i];
		if (max_l < llength(temp_item))
			max_l	= llength(temp_item);
	}

	return max_l;
}

#ifdef _DEBUG
void fill_field() {
	unsigned int	maxX,
					maxY,
					es;

	string			fill_str;

	fill_str.clear();

	getmaxyx(stdscr, maxY, maxX);	// Получение размеров экрана

	for (es	= 0; es <= maxX; fill_str	+= " ", es++);
	
	attron(COLOR_PAIR(TEXT_BLACK_GREEN) | A_BOLD);

	for (es	= 0; es <= maxY; mvprintw(es, 0, "%s", fill_str.c_str()), es++);

	attroff(COLOR_PAIR(TEXT_BLACK_GREEN) | A_BOLD);
}
#endif

unsigned int menu_winV2(MENSTR*	menu_conf, string	title, vector <string>	items, int	win_color) {

	unsigned int	posX,
					posY,
					posXmax,		// Ограничение размера окошка
					posYmax,
					maxX,			// Размеры экрана
					maxY,
					firstItem,		// Если не лезет в экран, то с какого элемента выводить
					lastItem,		// Если не лезет в экран, то до какого элемента выводить
					selected,		// Выбранный элемент
					maxItemLenght,	// Максимальная длина строки
					i,
					j;

	bool			progressBar,	// Выводить ли прогресс-бар
					cycle;

	int				key_pressed,
					win_color_selected,
					border_fix;

	string			tempItem,
					emptySpace;		// Для очистки области окна

	getmaxyx(stdscr, maxY, maxX);	// Получение размеров экрана

	if (menu_conf == NULL) {
		posX 		= 0;
		posY 		= 0;
		posXmax		= 0;
		posYmax		= 0;
		border_fix	= 2;	// Если включены границы окна, то добавить ещё две строки
	} else {
		if (menu_conf->no_border) {
			border_fix	= 0;
		} else {
			border_fix	= 2;
		}

		posX		= menu_conf->posX;
		posY		= menu_conf->posY;
		posXmax		= menu_conf->posXmax;
		posYmax		= menu_conf->posYmax;
	}

	if ((border_fix == 0) && (!title.empty()))
		border_fix	= 1;

	firstItem			= 0;
	lastItem			= items.size();
	win_color_selected	= get_inv_color(win_color);

	if ((posYmax != 0) && (posYmax < items.size())) {	// Если элементов больше, чем фиксированный размер окна 
		lastItem	= posYmax;
		progressBar	= true;
	}

	if (((posYmax != 0) && ((posY + posYmax + border_fix) >= maxY)) || ((posYmax == 0) && ((posY + items.size() + border_fix) >= maxY))) {	// Если окошко не влезает в экран попытаться вернуть его туда
		if (posYmax != 0) {
			if ((posYmax + border_fix) >= maxY) {		// Если фиксированный размер окна больше размера экрана
				if ((posY + border_fix) >= maxX)
					posY	= 0;

				if ((items.size() + border_fix) >= maxY) {
					lastItem	= (maxY - border_fix - posY);
					progressBar	= true;
				}

				posYmax		= maxY - border_fix - posY;
			} else {
				posY	= maxY - (posYmax + border_fix);
			}
		} else {
			if ((items.size() + border_fix) >= maxY) {	// Если колличество элементов больше экрана
				lastItem	= (maxY - border_fix - posY);
				progressBar	= true;
				posYmax		= maxY - border_fix - posY;
			} else {
				posY	= maxY - (items.size() + border_fix);
			}
		}
	}

	cycle			= true;
	selected		= 0;
	key_pressed		= KEY_UP;

	if (posXmax == 0) {
		maxItemLenght	= find_max_length(items);
	} else {
		maxItemLenght	= posXmax;
	}

	if (border_fix == 2) {	// Проверка влезания по X
		if ((posX + maxItemLenght + border_fix) >= maxX) {
			if ((posX + border_fix) >= maxX) {
				if ((maxItemLenght + border_fix) >= maxX)
					maxItemLenght	= (maxX / 3) - border_fix;

				posX			= maxX - (maxItemLenght + border_fix);
			}

			if ((maxItemLenght + border_fix) >= maxX) {
				if (((maxItemLenght + border_fix) - maxX) >= maxX) {
				printw("OK"); getch();
					maxItemLenght	= maxX - (posX + border_fix);
				} else {
					posX			= (maxItemLenght + border_fix) - maxX;
				}
			}

			if ((posX + maxItemLenght + border_fix) >= maxX) {
				maxItemLenght	= (maxX / 3) - border_fix;
				posX			= maxX - (maxItemLenght + border_fix);
			}
		}
	} else {
		if ((posX + maxItemLenght) >= maxX) {
			if ((posX) >= maxX) {
				if (maxItemLenght >= maxX)
					maxItemLenght	= (maxX / 3);

				posX			= maxX - maxItemLenght;
			}

			if ((maxItemLenght) >= maxX) {
				if (((maxItemLenght) - maxX) >= maxX) {
					maxItemLenght	= maxX - (posX);
				} else {
					posX			= maxItemLenght - maxX;
				}
			}

			if ((posX + maxItemLenght) >= maxX) {
				maxItemLenght	= (maxX / 3);
				posX			= maxX - maxItemLenght;
			}
		}
	}

	balance_vector(items, maxItemLenght);

	emptySpace.clear();

	for (j	= 0; j < maxItemLenght; emptySpace	+= " ", j++);	// Заполнение пробелами чистилки области

	timeout(-1);	// Задержка чтения кнопки с клавиатуры

	#ifdef _DEBUG
	fill_field();
	#endif

	if (border_fix == 2) {
		attron(COLOR_PAIR(win_color) | A_BOLD);

		if (posYmax != 0) {
			for (j	= 0; j <= posYmax; mvprintw(j + posY, posX + 1, "%s", emptySpace.c_str()), j++);
		}/* else {
			for (j	= 0; j <= items.size() + 1; mvprintw(j + posY, posX, "%s", emptySpace.c_str()), j++);
		}*/

		if (title.empty()) {
			for (j	= 0; j <= maxItemLenght; mvprintw(posY, posX + j, "-"), j++);	// Верхняя граница
			attroff(COLOR_PAIR(win_color) | A_BOLD);
		} else {
			for (j	= 0; j <= maxItemLenght; mvprintw(posY, posX + j, "-"), j++);	// Верхняя граница
			attroff(COLOR_PAIR(win_color) | A_BOLD);

			if (llength(title) > maxItemLenght) {	// Обрезка заголовка если слишком длинный
				title.erase(maxItemLenght - 3, llength(title));
				title	+= "...";
			}

			attron(COLOR_PAIR(win_color_selected) | A_BOLD);
			mvprintw(posY, posX + 1, "%s", title.c_str());	// Вывод заголовка
			attroff(COLOR_PAIR(win_color_selected) | A_BOLD);
		}

		attron(COLOR_PAIR(win_color) | A_BOLD);

		if (posYmax != 0) {
			for (j	= 0; j <= maxItemLenght; mvprintw(posY + posYmax + 1, posX + j, "-"), j++);	// Нижняя граница
		} else {
			for (j	= 0; j <= maxItemLenght; mvprintw(posY + items.size() + 1, posX + j, "-"), j++);	// Нижняя граница
		}

		attroff(COLOR_PAIR(win_color) | A_BOLD);

		posX++;
		posY++;
	} else if (border_fix == 1) {
		attron(COLOR_PAIR(win_color) | A_BOLD);

		if (posYmax != 0)
			for (j	= 0; j <= posYmax; mvprintw(j + posY, posX, "%s", emptySpace.c_str()), j++);

		for (j	= 0; j < maxItemLenght; mvprintw(posY, posX + j, "-"), j++);	// Верхняя граница

		attroff(COLOR_PAIR(win_color) | A_BOLD);

		if (llength(title) > (maxItemLenght - 2)) {	// Обрезка заголовка если слишком длинный
			title.erase(maxItemLenght - 5, llength(title));
			title	+= "...";
		}

		attron(COLOR_PAIR(win_color_selected) | A_BOLD);
		mvprintw(posY, posX + 1, "%s", title.c_str());	// Вывод заголовка
		attroff(COLOR_PAIR(win_color_selected) | A_BOLD);

		posY++;
	} else if ((border_fix == 0) && (posYmax != 0)) {
			for (j	= 0; j <= posYmax ; mvprintw(j + posY, posX, "%s", emptySpace.c_str()), j++);
	}


	while (cycle) {

		if ((key_pressed == KEY_UP) || (key_pressed == KEY_DOWN)) {		// Обновлять экран только при нажатии этих кнопок
			j 	= 0;

			attron(COLOR_PAIR(win_color) | A_BOLD);

			if (border_fix == 2) {	// Вывод левых и правых границ
				if (posYmax) {
					for (j	= 0; j <= posYmax + 1; mvprintw(posY + j - 1, posX - 1, "|"), mvprintw(posY + j - 1, posX + maxItemLenght, "|"), j++);
				} else {
					for (j	= 0; j <= items.size() + 1; mvprintw(posY + j - 1, posX - 1, "|"), mvprintw(posY + j - 1, posX + maxItemLenght, "|"), j++);
				}
			}

			attroff(COLOR_PAIR(win_color) | A_BOLD);

			j 	= 0;

			for (i	= firstItem; i < lastItem; i++, j++) {
				tempItem	= items[i];

				if (i == selected) {
					attron(COLOR_PAIR(win_color_selected) | A_BOLD);	// Выделение выбранного элемента
				} else {
					attron(COLOR_PAIR(win_color) | A_BOLD);
				}

				mvprintw(posY + j, posX, "%s", tempItem.c_str());

				if (i == selected) {
					attroff(COLOR_PAIR(win_color_selected) | A_BOLD);
				} else {
					attroff(COLOR_PAIR(win_color) | A_BOLD);
				}
			}

			attron(COLOR_PAIR(win_color) | A_BOLD);

			// items.size()	=	posYmax
			// selected		=	???
			if ((border_fix) && (progressBar)) {
				mvprintw(((selected * posYmax) / items.size()) + posY, posX - 1, "]");
			} else if (progressBar) {
				mvprintw(((selected * posYmax) / items.size()) + posY, posX - 1, "]");
			attron(COLOR_PAIR(win_color) | A_BOLD);
			}

			attroff(COLOR_PAIR(win_color) | A_BOLD);
		}

		key_pressed	= getch();

		switch (key_pressed) {
			case KEY_UP:			if (selected != 0)
										selected--;
									if ((progressBar) && (selected + 1 == firstItem)) {
										firstItem--;
										lastItem--;
									}
									break;

			case KEY_DOWN:			if (selected != (items.size() - 1))
										selected++;
									if ((progressBar) && (selected == lastItem)) {
										firstItem++;
										lastItem++;
									}
									break;

			case H_KEY_ENTER:		if (menu_conf != NULL) {
										if (border_fix == 2) {
											menu_conf->returned_x	= maxItemLenght + 1;
										} else {
											menu_conf->returned_x	= maxItemLenght;
										}

										menu_conf->returned_y	= posY + (selected - firstItem);
										getch();
									}
									return selected + 1;
									break;

			case H_KEY_BACKSPACE:	return 0;
									break;

			case H_KEY_ESC:			return 0;
									break;

			case H_KEY_CtrlF1:		windlg_ver();
									break;
		}

	}
}