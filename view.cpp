#include "view.h"
#include "tview.h"
#include "gview.h"

bool View::IsGui()
{
	return is_gui;
}

void View::set_flag(bool flag)
{
	is_gui = flag;
}

View* View::create(char type)
{
	View* v;
	if (type == 't') 
	{
		v = new Tview;
	}
	if (type == 'g')
	{
		v = new Gview;
	}
	return v;
}
