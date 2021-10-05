#include "view.h"
#include "game.h"
#include <algorithm>
#include <cmath>

Game::Game(View* myview) 
{
	v = myview;
	int col = v->get_col();
	int row = v->get_row();
	srand(time(NULL));
	for (int i = 0; i < 5; ++i)
	{
		int x = rand() % (col - 3) + 2;
		int y = rand() % (row - 3) + 2;
		rabbits.push_back(Rabbit(x, y));
	}
	Coord begin;
	begin.x = col / 2;
	begin.y = row / 2;	
	v->ontimer(bind(&Game::tick, this), 100);
	snakes.push_back(Snake(begin, 10, 0));
}

void Game::updatestate(Snake& s)
{
	int col = v->get_col();
	int row = v->get_row();
	DrawUpdateSnake draw;
	draw.tail = s.get_body().back();
	draw.direct = s.get_direct();
	draw.body = s.get_head();
	draw.color = s.get_style();
	draw.is_tail = true;
	switch (s.get_direct())
	{
		case LEFT:
			s.inc_dec_head("inc", 'x', row, col);
			break;
		case RIGHT:
			s.inc_dec_head("dec", 'x', row, col);
			break;
		case UP:
			s.inc_dec_head("dec", 'y', row, col);
			break;
		case DOWN:
			s.inc_dec_head("inc", 'y', row, col);
			break;
	}
	s.push_cell(s.get_head());
	draw.head = s.get_head();
	if (find_rabbit(s.get_head()) == cend(get_rabbits()))
	{
		s.erase_tail();
	}
	else
	{
		draw.is_tail = false;
	}
	v->paint(draw);
}

void Game::updatestate(list<Rabbit>& rabs)
{
	for (auto& snake : snakes)
	{
		list<Rabbit>::const_iterator this_it = find_rabbit(snake.get_head());
		if (this_it != cend(rabbits))
		{
			list<Rabbit>::iterator it = rabbits.begin();
			while(it != rabbits.end())
			{
				if (it == this_it)
				{
					rabbits.erase(it);
					break;
				}
				else
				{
					it++;
				}
			}
		}
	}
	if (rabbits.size() < 3)
	{
		int col = v->get_col();
		int row = v->get_row();
		for (int i = 0; i < 3; ++i)
		{
			int x = rand() % (col - 3) + 2;
			int y = rand() % (row - 3) + 2;
			rabbits.push_back(Rabbit(x, y));
			Coord c;
			c.x = x;
			c.y = y;
			v->paint(c);
		}
	}
}

void Game::tick()
{
	for (auto& fn : move_fn_)
	{
		fn();
	}
	for (auto& snake : snakes)
	{
		updatestate(snake);
	}
	updatestate(rabbits);
}

void Game::onmove(move_fn fn)
{
	move_fn_.push_back(fn);
}

list<Rabbit>::const_iterator Game::find_rabbit(Coord coord)
{
	for (list<Rabbit>::const_iterator it = cbegin(get_rabbits()); it != cend(get_rabbits()); it++)
	{
		if ((*it).get_coord().x == coord.x && (*it).get_coord().y == coord.y)
		{
			return it;
		}
	}
	return cend(get_rabbits());
}

list<Snake>& Game::get_snakes()
{
	return snakes;
}

Snake& Game::create_snake()
{
	list<Snake>::iterator it = snakes.end();
	it--;
	snakes.push_back(Snake({5, 5}, 10, (*it).get_style() + 1));
	return snakes.back();
}

list<Rabbit>& Game::get_rabbits()
{
	return rabbits;
}

Rabbit& Game::nearest_rabbit(Snake& s)
{
	int min = 1000000;
	list<Rabbit>::iterator ans = rabbits.begin();
	for (list<Rabbit>::iterator it = rabbits.begin(); it != rabbits.end(); ++it)
	{
		if (s.get_body().front().get_distance(it->get_coord()) < min)
		{
			min = s.get_body().front().get_distance(it->get_coord());
			ans = it;
		}
	}
	return (*ans);
}

int Game::distance_head_to_rabbit(list<Rabbit>::iterator it_rab)
{
	return snakes.back().get_body().front().get_distance(it_rab->get_coord());
}

Direction Game::get_direct_to_rabbit(Rabbit& rab, Snake& s)
{
	Coord h = s.get_body().front();
	Coord r = rab.get_coord();
	Direction d = s.get_direct();
	if (r.x < h.x)
	{
		if (d != LEFT)
		{
			d = RIGHT;
		}
	}
	else if (r.x > h.x)
	{
		if (d != RIGHT)
		{
			d = LEFT;
		}
	}
	else
	{
		if (r.y > h.y)
		{
			if (d != UP)
			{
				d = DOWN;
			}
		}
		else
		{
			if (d != DOWN)
			{
				d = UP;
			}
		}
	}
	return d;
}

Rabbit::Rabbit(int x, int y)
{
	c.x = x;
	c.y = y;
}

Coord Rabbit::get_coord() const
{
	return c;
}

Snake::Snake()
{
	Coord c = {2, 2};
	for (int j = 0; j < 6; ++j)
	{
		for (int i = 0; i < 3; ++i)
		{
			body.push_front(c);
			c.x++;
		}
		for (int i = 0; i < 3; ++i)
		{
			body.push_front(c);
			c.y++;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		body.push_front(c);
		c.x++;
	}
	head = c;
	direct = LEFT;
}

Snake::Snake(Coord begin, int len, int style_)
{
	for (int i = 0; i < len; ++i)
	{
		body.push_front(begin);
		begin.x++;
	}
	head = begin;
	head.x--;
	style = style_;
	direct = LEFT;
}

list<Coord> Snake::get_body() const
{
	return body;
}

Coord Snake::get_head() const
{
	return head;
}

Coord Snake::get_tail() const
{
	return body.back();
}

int Snake::get_style() const
{
	return style;
}

Direction Snake::get_direct() const
{
	return direct;
}

void Snake::set_direct(Direction d)
{
	direct = d;
}

void Snake::inc_dec_head(string flag, char obj, int row, int col)
{
	if (flag == "inc")
	{
		if (obj == 'x')
		{
			head.x++;
		}
		else if (obj == 'y')
		{
			head.y++;
		}
	}
	else if (flag == "dec")
	{
		if (obj == 'x')
        {
            head.x--;
        }
        else if (obj == 'y')
        {
            head.y--;
        }
	}
}

void Snake::push_cell(Coord c)
{
	body.push_front(c);
}

void Snake::erase_tail()
{
	list<Coord>::iterator it = body.end();
	it--;
	body.erase(it);
}

int Coord::get_distance(Coord end)
{
	return abs(x - end.x) + abs(y - end.y);
}
