#pragma once

#include <functional>
#include <signal.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/ioctl.h>
#include "view.h"

using namespace std;

class tview : public view {
public:
	virtual void draw(void);
	tview();
private:
	int row, col;
	static function<void(void)> onwinch;
	static void winch(int n);
	void set_winsize();
	void vline(int x, int y, int len);
	void gline(int x, int y, int len);
	void frame();
	void gotoxy(int x, int y);
	void cls();
};


