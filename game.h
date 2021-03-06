#pragma once

#include <iostream>
#include <list>
using namespace std;

using coord = std::pair<int, int>;

class Rabbit{
public:
	Rabbit(int x, int y);
	coord c;
};

class game{
public:
	game();
private:
	std::list<Rabbit> rabbits;
};


