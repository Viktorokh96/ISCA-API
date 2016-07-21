#include <isca.h>
#include <internal.h>

#define LOGFILE "./initlog.log"

ISCA_StdForm *ISCA_Applic;

void ISCA_ApplicFree(void *apl)
{
	ISCA_StdForm *a = (ISCA_StdForm *) apl;
	delete a;
}

int ISCA_InitApplic()
{
	ISCA_Applic = new ISCA_StdForm;		// Выделение памяти под корень дерева
	if(!ISCA_Applic) return -1;

	ISCA_Rect rect;
	ISCA_Assign(&rect, 0, 0 , ISCA_GetWidth(), ISCA_GetHeight());
	
	ISCA_Applic->owner = NULL;
	ISCA_Applic->next = NULL;
	ISCA_Applic->chil = NULL;
	ISCA_Applic->curr = NULL;

	ISCA_Applic->free = ISCA_ApplicFree;
	ISCA_Applic->event_handler = ISCA_StdEventHandl;

	ISCA_Applic->title = "Applic Main";

	return 0;
}

// Рекурсивное удаление дерева форм
void ISCA_FreeTree(void *f)
{
	ISCA_StdForm *tmp, *frm = (ISCA_StdForm *) f;

	ISCA_Log(LOGFILE, "Удаление дерева с вершины %s\n", frm->title.c_str());
	while(frm->chil) {
		tmp = (ISCA_StdForm *) frm->chil;
		frm->chil = ((ISCA_StdForm *) (frm->chil))->next;
		ISCA_FreeTree(tmp);
	}
	
	ISCA_Log(LOGFILE, "Удаление вершины %s\n", frm->title.c_str());
	ISCA_FreeForm(frm);
}

void ISCA_SendEvent(void *frm, ISCA_Event *ev)
{
	ISCA_StdForm *tmp, *f = (ISCA_StdForm *) frm;

	tmp = (ISCA_StdForm *) f->chil;
	while(tmp) {
		ISCA_SendEvent(tmp, ev);
		tmp = (ISCA_StdForm *)tmp -> next;
	}

	ISCA_StdEventHandl(f, ev);
	if(f->event_handler)
		f->event_handler(f, ev);
}

