#include "tview.h"

using namespace std;

function<void(void)> tview::onwinch;

void tview::cls() {
	printf("\e[H");
	printf("\e[J");
}

void tview::set_winsize() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	col = w.ws_col;
	row = w.ws_row;
}

tview::tview() {
	set_winsize();
	onwinch = bind(&tview::draw, this);
	signal(SIGWINCH, &tview::winch);
}

void tview::winch(int n) {
	onwinch();
}

void tview::gotoxy(int x, int y)
{
	printf("\e[%d;%dH", y, x);
}

void tview::vline(int x, int y, int len) {
	gotoxy(x, y);
	for(int i = y; i <= len + y; ++i) {
		gotoxy(x, i);
		printf("|");
	}
}

void tview::gline(int x, int y, int len) {
        gotoxy(x, y);
        for(int i = x; i <= len + x; ++i) {
                gotoxy(i, y);
                printf("_");
        }
}

void tview::frame() {
	vline(0, 0, row);
	vline(col, 0, row);
	gline(0, 0, col);
	gline(0, row, col);
}

void tview::draw() {
	setbuf(stdout, NULL);
	cls();
	set_winsize();
	frame();
}

