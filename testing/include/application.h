#ifndef APPLIC_H
#define APPLIC_H

#include <stdform.h>
#include <types.h>

/* 
 * Функции для работы инициализации и работы GUI в 
 * библиотеке ISCA.
 * ISCA_RegisterForm - регистрация формы
 * ISCA_Assign - инициализация структуры ISCA_Rect
 * ISCA_GetWidth - получение ширины окна
 * ISCA_GetHeight - получение высоты окна 
 * ISCA_Init - Инициализация приложения GUI для ISCA
 * ISCA_Run - запуск приложения
 * ISCA_Quit - завершение приложения
 * ISCA_Insert - insert one form to other
*/

int ISCA_RegisterForm(void *frm, deletehandler_t fr,
			eventhandler_t evt, 
			drawhandler_t drw);

int ISCA_Assign(ISCA_Rect *rect, int x, int y, int w, int h);

int ISCA_GetWidth();

int ISCA_GetHeight();

int ISCA_Init();

void ISCA_Quit();

void ISCA_Run();

int ISCA_Insert(void* dst, void* src);

#endif
