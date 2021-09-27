#pragma once

#include <iterator>
#include <ctime>
#include <iostream>
#include <list>
#include <unistd.h>
#include <functional>

using namespace std;
using move_fn = function<void(void)>;

class View; 

class Coord
{
public:
	int x;
	int y;
	int get_distance(Coord end);
};


class Rabbit{
public:
	Rabbit(int x, int y);
	Coord get_coord() const;
private:
	Coord c;
};

enum Direction {LEFT, RIGHT, UP, DOWN};

class Snake
{
public:
	Snake();
	Snake(Coord begin, int len, int style);
	list<Coord> get_body() const;
	Coord get_head() const;
	Coord get_tail() const;
	int get_style() const;
	Direction get_direct() const;
	void set_direct(Direction d);
	void erase_tail();
	void push_cell(Coord c);
	void inc_dec_head(string flag, char obj, int row, int col);
	void inc_dec_tail(string flag, char obj, int row, int col);
private:
	list<Coord> body;
	Coord head;
	Direction direct;
	int style;
};

class Game{
public:
	Game(View* v);
	list<Rabbit>& get_rabbits();
	list<Snake>& get_snakes();
	void tick();
	Snake& create_snake();
	int get_distance();
	Rabbit& nearest_rabbit(Snake& s);
	Direction get_direct_to_rabbit(Rabbit& r, Snake& s);
	void onmove(const move_fn fn);
	View* get_view();
private:
	View* v;
	std::list<Snake> snakes;
	std::list<Rabbit> rabbits;
	void updatestate(Snake& s);
	void updatestate(list<Rabbit>& r);
	list<Rabbit>::const_iterator find_rabbit(Coord c);
	int distance_head_to_rabbit(list<Rabbit>::iterator it_rab);
	list<move_fn> move_fn_;
};

