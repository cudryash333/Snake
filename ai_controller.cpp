#include "ai_controller.h"

AiController::AiController(View* v_, Snake* s_, Game* g_):
	v(v_), s(s_), g(g_)
{
	g->onmove(bind(&AiController::update_direct, this));
}

void AiController::update_direct()
{
	Rabbit& nearest_r = g->nearest_rabbit(*s);
	s->set_direct(g->get_direct_to_rabbit(nearest_r, *s));
}
