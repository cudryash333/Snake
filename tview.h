#pragma once

#include <string>
#include <poll.h>
#include <cstdio>
#include <functional>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include "view.h"
#include <termios.h>

using namespace std;

class Tview : public View {
public:
	Tview();
	~Tview();
	void draw();
	void paint(const Coord& rabbit);
	void paint(const DrawSnake& snake);
	void paint(const DrawUpdateSnake& s);
 	int get_row();
	int get_col();
	void ontimer(const timer_fn, int time);
	void onkey(const key_fn);
	void runloop();
	void quit();

private:
	bool finished;
	int row, col;
	struct termios old;
	list<key_fn> pressed;
	pair<timer_fn, int> timer;
	static function<void(void)> onwinch;
	static void winch(int n);
	void set_winsize();
	void draw_set_color(string color);
	void draw_default_color();
	void draw_string(int x, int y, string str);
	void vline(int x, int y, int len);
	void gline(int x, int y, int len);
	void frame();
	void gotoxy(int x, int y);
	void cls();
};
