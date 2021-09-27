#include <iostream>
#include <string>
#include "tview.h"
#include "gview.h"
#include "view.h"
#include "game.h"
#include "controller.h"
#include "ai_controller.h"

using namespace std;
using namespace std::placeholders;

class Quiter
{
public:
	Quiter(View* myv)
	{
		v = myv;
		v->onkey(bind(&Quiter::key_pressed, this, _1));
	}
	void key_pressed(int key)
	{
		if (key == 'q')
		{
			v->quit();
		}
	}
	View* v;
};

int main(int argc, char* argv[]) {

	char type;
	std::cin >> type;
	View* v = View::create(type);
	// Gview* v;
	Game g(v);
	KeyController c(&g.get_snakes().front(), v);	
	AiController ai(v, &g.create_snake(), &g);
	AiController ai_2(v, &g.create_snake(), &g);
	Quiter q(v);
	v->draw();
	for (auto& rabbit : g.get_rabbits())
	{
		v->paint(rabbit.get_coord());
	}
	int i = 0;
	for (auto& snake : g.get_snakes())
	{
		DrawSnake draw_snake;
		draw_snake.body = snake.get_body();
		draw_snake.direct = snake.get_direct();
		draw_snake.color = i;
		i++;
		v->paint(draw_snake);
	}
	v->runloop();
	return 0;
}
