#ifndef GAME_H

#include <iostream>
#include <fstream>
#include <ncurses/curses.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <windows.h>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;
int startX = 15, startY = 6, lebar = 60, tinggi = 15;
int health = 3;

struct enemy {
	int x;
	int y;
	char c;
};
struct bullet {
	int x;
	int y;
	int sp;
	char mv;
	char c;
};

void moveMe(int& mex,int& mey, WINDOW *gameplay);
bool hitCheck(int x1, int y1, int x2, int y2, WINDOW* gameplay);
bool block(int x, int y);
void moveBot(int x, int y, int &refX, int &refY);
void shotChance(vector<bullet>& var, enemy &i);

void game() {
	nodelay(stdscr, TRUE);
	
	WINDOW *gameplay = newwin(tinggi, lebar, startY, startX);
	nodelay(gameplay, TRUE);
    keypad(gameplay, TRUE);
	box(gameplay,0,0);
	wgetch(gameplay);

	
	mvprintw(2,2,"HP: ");
	mvaddch(2,6,(char)196u);
	mvaddch(2,7,(char)196u);
	mvaddch(2,8,(char)196u);
	
	vector<enemy> enemys;
	vector<bullet> bullets; 
	wrefresh(gameplay);
	int mex=20, mey=10;
	
	while(true) {
		if (enemys.size() <= 8) {
			int x, y;
			if (rand()%2==0) {
				if (rand()%2 == 0) x = lebar;
				else x = -1;
				y = (rand()%tinggi);
			} else {
				if (rand()%2 == 0) y = tinggi;
				else y = -1;
				x = (rand()%lebar);
			}
			mvwprintw(gameplay,2,12,"%d",x);
			mvwprintw(gameplay,3,12,"%d",y);
			enemys.push_back({x,y,'O'});
		}
		moveMe(mex, mey, gameplay);
		for (enemy &i: enemys) {
			int x = 0, y = 0;
			moveBot(i.x,i.y,x,y);
			mvwaddch(gameplay,i.y,i.x,' ');
			mvwaddch(gameplay,i.y+=y,i.x+=x,i.c);
			
			shotChance(bullets, i);	
			wrefresh(gameplay);
		}
		for (int i = 0; i < bullets.size(); i++) {
			mvwaddch(gameplay,bullets[i].y,bullets[i].x,' ');
			if (bullets[i].mv == 'x') {
				mvwaddch(gameplay,bullets[i].y,bullets[i].x+=bullets[i].sp,bullets[i].c);
				if (bullets[i].sp == 1 && bullets[i].x >= lebar-1) bullets.erase(bullets.begin() + i);
				else if (bullets[i].sp == -1 && bullets[i].x <= 0) bullets.erase(bullets.begin() + i);
			} else {
				mvwaddch(gameplay,bullets[i].y+=bullets[i].sp,bullets[i].x,bullets[i].c);
				if (bullets[i].sp == 1 && bullets[i].y >= tinggi-1) bullets.erase(bullets.begin() + i);
				else if (bullets[i].sp == -1 && bullets[i].y <= 0) bullets.erase(bullets.begin() + i);
			}
			if (hitCheck(bullets[i].x,bullets[i].y,mex,mey,gameplay)) return;
			wrefresh(gameplay);
			refresh();
		}
		box(gameplay,0,0);
		napms(100);
	}
}
void moveMe(int& mex,int& mey, WINDOW *gameplay) {
	int inp = wgetch(gameplay);
	switch(inp) {
		case 259: 
		if (block(mex,mey-1)) {
			mvwprintw(gameplay,mey,mex," ");
			mey--;
			mvwprintw(gameplay,mey,mex,"X");
		}
		break;
		case 261: 
		if (block(mex+1,mey)) {
			mvwprintw(gameplay,mey,mex," ");
			mex++;
			mvwprintw(gameplay,mey,mex,"X");
		}
		break;
		case 258: 
		if (block(mex,mey+1)) {
			mvwprintw(gameplay,mey,mex," ");
			mey++;
			mvwprintw(gameplay,mey,mex,"X");
		}
		break;
		case 260: 
		if (block(mex-1,mey)) {
			mvwprintw(gameplay,mey,mex," ");
			mex--;
			mvwprintw(gameplay,mey,mex,"X");
		}
		break;
	}
}
bool hitCheck(int x1, int y1, int x2, int y2, WINDOW* gameplay) {
	if (x1 == x2 && y1 == y2) {
		health--;
		mvwaddch(gameplay,2,6+health,' ');
		if (health <= 0) {
			nodelay(gameplay, FALSE);
			return true;
		}
	}
	return false;
}
bool block(int x, int y) {
	if (x <= 0 || x >= lebar-1) return false;
	else if (y <= 0 || y >= tinggi-1) return false;
}
void moveBot(int x, int y, int &refx, int &refy) {
	if ((x != lebar && x != -1) && (y == tinggi || y == -1)) {
		refx = (rand()%2==0?-1:1);
	}
	if ((x == lebar || x == -1) && (y != tinggi && y != -1)) {
		refy = (rand()%2==0?-1:1);
	}
	
	if (y == tinggi && x == lebar) {
		if (rand()%2 == 0) refx = -1;
		else refy = -1;
	} else
	if (y == tinggi && x == -1) {
		if (rand()%2 == 0) refx = 1;
		else refy = -1;
	} else
	if (y == -1 && x == lebar) {
		if (rand()%2 == 0) refx = -1;
		else refy = 1;
	} else
	if (y == -1 && x == -1) {
		if (rand()%2 == 0) refx = 1;
		else refy = 1;
	} 
}
void shotChance(vector<bullet>& var, enemy &i) {
	if ((rand()%100>=95) && !( 
		(i.y >= tinggi-2 && i.x >= lebar-2) ||
		(i.y >= tinggi-2 && i.x <= 1) ||
		(i.y <= 1 && i.x >= lebar-2) ||
		(i.y <= 1 && i.x <= 1)
	)) {
		if (i.y == tinggi) var.push_back({i.x,i.y-1,-1,'y','|'});
		else if (i.y == -1) var.push_back({i.x,i.y+1,1,'y','|'});
		else if (i.x == lebar) var.push_back({i.x-1,i.y,-1,'x','-'});
		else if (i.x == -1) var.push_back({i.x+1,i.y,1,'x','-'});
	}
}
#endif
