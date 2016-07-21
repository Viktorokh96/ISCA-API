#include <iosystem.h>
#include <stdform.h>

#define LOGFILE "./initlog.log"
using std::clog;

void ISCA_StdEventHandl(void *ths, ISCA_Event *event)
{
	ISCA_StdForm *frm = (ISCA_StdForm *) ths;

	ISCA_Log(clog, "Form %s get event key %c\n", 	
			frm->title.c_str(), event->kb);
	return;
}

void ISCA_StdDraw(void *ths)
{
	return;
}

void ISCA_FreeForm(void *frm)
{
	ISCA_StdForm *f = (ISCA_StdForm *) frm;

	ISCA_Log(LOGFILE, "Освобождение формы %s\n",
			f->title.c_str());

	f->free(f);
}

