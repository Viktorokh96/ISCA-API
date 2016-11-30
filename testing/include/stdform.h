#ifndef STDFORM_H
#define STDFORM_H

#include <types.h>
#include <iostream>

class ISCA_Rect {
	int _x,_y;	// Начальные координаты формы
	int _w,_h;	// Ширина и высота формы
public:
	enum what { x, y, w, h }; 
	void assign(int x, int y, int w, int h) { _x = x; _y = y; _w = w; _h = h; }
	int get(what wh);
};

/* Стандартные поля формы:
 * next - слудующая форма (соседний узел в дереве), 
 * которая принадлежит владельцу этого окна.
 * owner - владелец текущей формы.
 * chil - указатель на голову спискa потомков формы.
 * curr - указатель на текущую форму (для поддержки модальности).
 * visible - флаг указывающий на видимость окна.
 * event_handler - метод обработчика событий.
 * draw - метод отрисовки формы.
 * free - метод освобождения структуры.
*/

class ISCA_Form {
protected:
	ISCA_Form *next;
	ISCA_Form *owner;
	ISCA_Form *chil;
	ISCA_Form *curr;
	bool visible;
	std::string title;
	ISCA_Rect rect;
public:
	void event_handler(ISCA_Event *event); 
	void draw() {}
};

extern ISCA_Form *ISCA_Applic;			// Корень дерева форм приложения

class ISCA_Win : public ISCA_Form {
	opt_t options;
};

ISCA_Form *ISCA_NewForm();

#endif
