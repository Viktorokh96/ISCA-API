#include <stdform.h>
#include <iosystem.h>

ISCA_Rect rect;

int main()
{
	rect.assign(1,1,20,30);

	int x = rect.get(ISCA_Rect::w);

	return 0;
}
