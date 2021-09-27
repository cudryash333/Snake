#include "gview.h"

Gview::Gview()
{
	window.create(sf::VideoMode(500, 500), "Game");
	while (window.isOpen())
    	{
			sf::Event event;
        	while (window.pollEvent(event))
        		{
            		if (event.type == sf::Event::Closed)
					window.close();
        		}
        Gview::draw();

		// window.draw(rabsprite);
		window.display();
		//
    	}
}

Gview::~Gview()
{

}

void Gview::draw()
{
	window.clear(sf::Color::White);
	draw_frame();
}

void Gview::draw_frame()
{
	
}


void Gview::paint(const Coord& r)
{

}

void Gview::paint(const DrawSnake& s)
{

}

void Gview::paint(const DrawUpdateSnake& s)
{

}

int Gview::get_row()
{
	return row;
}

int Gview::get_col()
{
	return col;
}

void Gview::ontimer(const timer_fn, int time)
{

}

void Gview::onkey(const key_fn)
{

}

void Gview::runloop()
{

}

void Gview::quit()
{

}
