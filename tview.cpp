#include "tview.h"

#define ESC "\033"

using namespace std;

function<void(void)> Tview::onwinch;

void Tview::cls() {
	printf(ESC "[H");
	printf(ESC "[J");
}

void Tview::set_winsize() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	col = w.ws_col;
	row = w.ws_row;
}

Tview::Tview() {
	struct termios termios_p;
	tcgetattr(0, &termios_p);
	old = termios_p;
	cfmakeraw(&termios_p);
	tcsetattr(0, TCSAFLUSH, &termios_p);
	set_winsize();
	onwinch = bind(&Tview::draw, this);
	signal(SIGWINCH, &Tview::winch);
}

Tview::~Tview()
{
	tcsetattr(0, TCSAFLUSH, &old);
}

void Tview::runloop()
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

void Tview::quit()
{
	finished = true;
}

void Tview::ontimer(const timer_fn f, int time)
{
	timer.first = f;
	timer.second = time;
}

void Tview::onkey(const key_fn k)
{
	pressed.push_back(k);
}

int Tview::get_row()
{
	return row;
}

int Tview::get_col()
{
	return col;
}

void Tview::winch(int n) {
	onwinch();
}

void Tview::gotoxy(int x, int y)
{
	printf(ESC "[%d;%dH", y, x);
}

void Tview::vline(int x, int y, int len) {
	gotoxy(x, y);
	for(int i = y; i <= len + y; ++i) {
		gotoxy(x, i);
		printf("|");
	}
}

void Tview::gline(int x, int y, int len) {
        gotoxy(x, y);
        for(int i = x; i <= len + x; ++i) {
                gotoxy(i, y);
                printf("_");
        }
}

void Tview::draw_string(int x, int y, string str)
{
	gotoxy(x, y);
	cout << str;
}


void Tview::frame() {
	vline(0, 0, row);
	vline(col, 0, row);
	gline(0, 0, col);
	gline(0, row, col);
}

static const char* colors[] = {"r", "green", "y", "b", "grey"};

void Tview::draw_set_color(string color)
{
	if (color == "r")
	{
		printf(ESC "[31;1m");
	}
	else if (color == "green")
	{
		printf(ESC "[32;1m");
	}
	else if (color == "y")
       	{
		printf(ESC "[33;1m");
	}
	else if (color == "b")
	{
		printf(ESC "[34;1m");
       	}
	else if (color == "grey")
	{
		printf(ESC "[30;1m");
	}
}

void Tview::draw_default_color()
{
	printf(ESC "[0m");
}

void Tview::paint(const Coord& c)
{
	draw_set_color("b");
	draw_string(c.x, c.y, "*");
	draw_default_color();
}

void Tview::paint(const DrawSnake& s)
{
	draw_set_color(colors[s.color]);
	bool first = true;
	for (Coord c : s.body)
	{
		if (!first)
		{
			draw_string(c.x, c.y, "o");
		}
		first = false;
	}
	Coord head = s.body.front();
	string arrow;
	arrow += "><^v"[s.direct];
	draw_string(head.x, head.y, arrow);
	draw_default_color();
}

void Tview::paint(const DrawUpdateSnake& s)
{
	draw_set_color(colors[s.color]);
	draw_string(s.body.x, s.body.y, "o");
	string arrow;
	arrow += "><^v"[s.direct];
	draw_string(s.head.x, s.head.y, arrow);
	if (s.is_tail)
	{
		draw_string(s.tail.x, s.tail.y, " ");
	}
	draw_default_color();
}

void Tview::draw() {
	setbuf(stdout, NULL);
	cls();
	set_winsize();
	frame();
}

