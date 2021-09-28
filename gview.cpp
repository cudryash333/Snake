#include "gview.h"

Gview::Gview()
{
	window.create(sf::VideoMode(500, 500), "Game");
	window.setVerticalSyncEnabled(true);
	//const Coord& r;
	//const DrawSnake& s;
	while (window.isOpen())
    	{
			sf::Event event;
        	while (window.pollEvent(event))
        		{
            		if (event.type == sf::Event::Closed)
					window.close();
        		}
        Gview::draw();
	//paint(r);
	//paint(s);
	window.display();
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
	sf::RectangleShape line(sf::Vector2f(500.f, 500.f));
	line.setOutlineColor(sf::Color::Red); 
	line.setOutlineThickness(10.f);	
	window.draw(line);
}


void Gview::paint(const Coord& r)
{
	sf::Sprite rabsprite;
	sf::Texture texture;
	texture.loadFromFile("rabbit-clip-art-5.png");
	rabsprite.setTexture(texture);
	rabsprite.setTextureRect(sf::IntRect(r.x, r.y, 30, 30));
	window.draw(rabsprite);
}

void Gview::paint(const DrawSnake& s)
{
	sf::Sprite sprite_head;
	sf::Sprite sprite_body;
	sf::Sprite sprite_tail;
	sf::Texture texture_tail;
	sf::Texture texture_head;
	sf::Texture texture_body;
	bool first = true;
        for (Coord c : s.body)
        {
                if (!first)
                {
                      	texture_body.loadFromFile("AvNKgAB5V6c.png");
			sprite_body.setTexture(texture_body);
			sprite_body.setTextureRect(sf::IntRect(c.x, c.y, 50, 50));
			window.draw(sprite_body);
                } else {
			texture_tail.loadFromFile("tail.png");
			sprite_head.setTexture(texture_tail);
			sprite_tail.setTextureRect(sf::IntRect(c.x, c.y, 50, 50));
			window.draw(sprite_tail);
		}	
		first = false;
        }
        Coord head = s.body.front();
	texture_head.loadFromFile("547-5471472_snake-mask.png");
	sprite_head.setTexture(texture_head);
	sprite_head.setTextureRect(sf::IntRect(head.x, head.y, 50, 50));
	switch (s.direct)
	{
		case 3:
			break;
		case 2:
			sprite_head.setRotation(180.f);
			break;
		case 1:
			sprite_head.setRotation(90.f);
			break;
		case 0:
			sprite_head.setRotation(270.f);
			break;
	}
	window.draw(sprite_head);
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

void Gview::ontimer(const timer_fn f, int time)
{
	timer.first = f;
	timer.second = time;
}

void Gview::onkey(const key_fn k)
{
	pressed.push_back(k);
}

void Gview::runloop()
{
	struct pollfd fds[] = { {0, POLLIN, 0} };
	finished = false;
	int flag = 1;
	while(!finished)
	{
		int n = poll(fds, 1, timer.second * flag);
		flag = 1;
		if (n == 0)
		{
			timer.first();
		}
		else
		{
			flag = 0;
			char buf[1];
			read(0, buf, 1);
			for (auto f : pressed)
			{
				f(buf[0]);
			}
		}
	}
}

void Gview::quit()
{
	finished = true;
}
