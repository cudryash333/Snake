#include <termios.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include "tview.h"

void tview::cls() {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);
	printf("\e[H]");
	printf("\e[J]");
}
