#include <iosystem.h>
#include <stdform.h>

#define LOGFILE "./initlog.log"
using std::clog;

int ISCA_Rect::get(what wh)
{
	switch(wh) {
		case x:
			return _x;
		case y:
			return _y;
		case w: 
			return _w;
		case h:
			return _h;
		default:
			return -1;
	}
}

void ISCA_Form::event_handler(ISCA_Event *event)
{
	ISCA_Log(clog, "Form %s get event key %c\n", 	
			title.c_str(), event->kb);
	return;
}

// Factory
ISCA_Form *ISCA_NewForm()
{
	return new ISCA_Form;
}
