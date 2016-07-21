#ifndef STDFORM_H
#define STDFORM_H

#include <types.h>
#include <isca.h>

/* Стандартные поля формы:
 * next - слудующая форма (соседний узел в дереве), 
 * которая принадлежит владельцу этого окна.
 * owner - владелец текущей формы.
 * chil - указатель на голову спискa потомков формы.
 * curr - указатель на текущую форму (для поддержки модальности).
 * event_handler - метод обработчика событий.
 * draw - метод отрисовки формы.
*/
#define STD_FORM\
	void *next;\
	void *owner;\
	void *chil;\
	void *curr;\
	std::string title;\
	ISCA_Rect rect;\
	eventhandler_t event_handler;\
	drawhandler_t draw;\
	deletehandler_t free;\

struct ISCA_StdForm {
	STD_FORM
};

extern ISCA_StdForm *ISCA_Applic;			// Корень дерева форм приложения

struct ISCA_Win {
	STD_FORM
	opt_t options;
};

struct ISCA_Button {
	STD_FORM
};

void ISCA_StdEventHandl(void *ths, ISCA_Event *event);

void ISCA_StdDraw(void *ths);

void ISCA_FreeForm(void *frm);

#endif