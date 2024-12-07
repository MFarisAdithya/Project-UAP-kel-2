#ifndef ENEMY_H
#define ENEMY_H

void enemy_a(int x,int y) {
	mvaddch(y,x,ACS_ULCORNER);
	mvaddch(y,x+1,ACS_HLINE);
	mvaddch(y,x+2,ACS_HLINE);
	mvaddch(y,x+3,ACS_HLINE);
	mvaddch(y,x+3,ACS_URCORNER);
	mvaddch(y+1,x+3,ACS_VLINE);
	mvaddch(y+2,x+3,ACS_VLINE);
	mvaddch(y+3,x+3,ACS_LRCORNER);
	mvaddch(y+3,x+2,ACS_HLINE);
	mvaddch(y+3,x+1,ACS_HLINE);
	mvaddch(y+3,x,ACS_HLINE);
	mvaddch(y+3,x,ACS_LLCORNER);
	mvaddch(y+2,x,ACS_VLINE);
	mvaddch(y+1,x,ACS_VLINE);
	refresh();
}



#endif
