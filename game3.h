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
#include "enemy.h"

using namespace std;
int startX = 50, startY = 15, lebar = 40, tinggi = 20;
int health = 3;

struct mychar {
	int x = 20;
	int y = 10;
	int hp = 1000;
	int time = 0;
};
struct enem {
	unsigned long long int time;
	int delay;
	int type;
};
struct bullet {
	int x;
	int y;
	chtype c;
	chtype fl;
	enem parent;
	int jeda;
	unsigned long long int time;
	int type;
	int step = 0;
};
//struct bullet_two {
//	int x;
//	int y;
//	chtype c;
//	chtype fl;
//	enem parent;
//	int jeda;
//	unsigned long long int time;
//	int step = 1;
//	int type = 2;
//};
//
void moveMe(int& mex,int& mey, WINDOW *gameplay);
bool hitCheck(int x1, int y1, mychar &mc, WINDOW* gameplay);
bool block(int x, int y);

void enemy_one_shot(vector<bullet> &bullets,unsigned long long int time,mychar &mc,WINDOW* gameplay);
void enemy_one_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay);
void enemy_two_shot(vector<bullet> &bullets,unsigned long long int time, mychar &mc,WINDOW* gameplay);
void enemy_two_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay);

bool enemy_shot(vector<bullet> &bullets,unsigned long long int time,mychar &mc,WINDOW* gameplay);
//bool enemy_shot(vector<bullet_two> &bullets,unsigned long long int time,mychar &mc,WINDOW* gameplay);
bool enemy_spawnshot(vector<bullet> &bullets,vector<enem> &enemys,unsigned long long int time,WINDOW* gameplay);
//bool enemy_spawnshot(vector<bullet_one> &bullets,vector<enem> &enemys,unsigned long long int time,WINDOW* gameplay);
//void moveBot(int x, int y, int &refX, int &refY);
//void shotChance(vector<bullet>& var, enemy &i);

void game() {
	nodelay(stdscr, FALSE);
	
	WINDOW *gameplay = newwin(tinggi, lebar, startY, startX);
	nodelay(gameplay, TRUE);
    keypad(gameplay, TRUE);
	box(gameplay,0,0);
	


	unsigned long long int time = 0;
	
	
	vector<enem> enemys;
	vector<bullet> bullets; 
	wrefresh(gameplay);
	box(gameplay,0,0);
	int mex=20, mey=10;
	
	mychar mc;
	enem test;
	mvprintw(2,2,"HP: ");
	for (int i=0; i < mc.hp; i++) {
		mvaddch(2,6+i,(char)196u);	
	}
	
	enemys.push_back({time,10,1});
	enemys.push_back({time,10,2});
	int counter = 0;
	int timeline = 0;
	int abcd = 0;
	//bullets.push_back({1+rand()%(lebar-2),1+rand()%(tinggi-2),ACS_BULLET,ACS_DIAMOND,enemys[0],30,time});
	wgetch(gameplay);
	nodelay(stdscr, TRUE);
	
	while(true) {
		
		int x, y;
		
		
		
		if(enemy_spawnshot(bullets,enemys,time,gameplay)) return;
		if(enemy_shot(bullets,time,mc,gameplay)) return;
		moveMe(mc.x,mc.y, gameplay);
		time++;
		mvwprintw(gameplay,mc.y,mc.x,"X");
		mvprintw(1,150,"%llu",time);
		refresh();
		napms(10);
		box(gameplay,0,0);
		wrefresh(gameplay);
		
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
//	mvprintw(2,90,"%d",mex);
//	mvprintw(4,95,"%d",mey);
}
bool hitCheck(int x1, int y1, mychar &mc, WINDOW* gameplay) {
	refresh();
	if (x1 == mc.x && y1 == mc.y) {
		mc.hp--;
		mvaddch(2,6+mc.hp,' ');
		refresh();
		if (mc.hp <= 0) {
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

//void moveBot(int x, int y, int &refx, int &refy) {
//	if ((x != lebar && x != -1) && (y == tinggi || y == -1)) {
//		refx = (rand()%2==0?-1:1);
//	}
//	if ((x == lebar || x == -1) && (y != tinggi && y != -1)) {
//		refy = (rand()%2==0?-1:1);
//	}
//	
//	if (y == tinggi && x == lebar) {
//		if (rand()%2 == 0) refx = -1;
//		else refy = -1;
//	} else
//	if (y == tinggi && x == -1) {
//		if (rand()%2 == 0) refx = 1;
//		else refy = -1;
//	} else
//	if (y == -1 && x == lebar) {
//		if (rand()%2 == 0) refx = -1;
//		else refy = 1;
//	} else
//	if (y == -1 && x == -1) {
//		if (rand()%2 == 0) refx = 1;
//		else refy = 1;
//	} 
//}
//void shotChance(vector<bullet>& var, enemy &i) {
//	if ((rand()%100>=95) && !( 
//		(i.y >= tinggi-2 && i.x >= lebar-2) ||
//		(i.y >= tinggi-2 && i.x <= 1) ||
//		(i.y <= 1 && i.x >= lebar-2) ||
//		(i.y <= 1 && i.x <= 1)
//	)) {
//		if (i.y == tinggi) var.push_back({i.x,i.y-1,-1,'y','|'});
//		else if (i.y == -1) var.push_back({i.x,i.y+1,1,'y','|'});
//		else if (i.x == lebar) var.push_back({i.x-1,i.y,-1,'x','-'});
//		else if (i.x == -1) var.push_back({i.x+1,i.y,1,'x','-'});
//	}
//}




bool enemy_one_shot(vector<bullet> &bullets,unsigned long long int time, mychar &mc,WINDOW* gameplay,int i) {
	//if (bullets[i].time+bullets[i].jeda<=time) {
		//bullets[i].time = time;
	mvwaddch(gameplay,bullets[i].y,bullets[i].x,' ');
	if (bullets[i].c==ACS_DARROW) bullets[i].y++; else
	if (bullets[i].c==ACS_LARROW) bullets[i].x--; else
	if (bullets[i].c==ACS_UARROW) bullets[i].y--; else
	if (bullets[i].c==ACS_RARROW) bullets[i].x++;
	
//		mvprintw(i+1,80,"%d",bullets[i].x);
//		mvprintw(i+1,85,"%d",bullets[i].y);
	
	mvwaddch(gameplay,bullets[i].y,bullets[i].x,bullets[i].c);
	wrefresh(gameplay);
	if (bullets[i].x<=0 || bullets[i].y <= 0 || bullets[i].x >= lebar+1 || bullets[i].y >= tinggi+1) {
		bullets.erase(bullets.begin() + i);
	}
	return hitCheck(bullets[i].x,bullets[i].y,mc,gameplay);
	//}
}

void enemy_one_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay) {
	//for (enem &i: enemys) {
	//if (i.time <= time) {
	if (rand()%100>=80) {
		switch (rand()%4) {
			case 0: bullets.push_back({rand()%(lebar-2),0,ACS_DARROW,ACS_VLINE,i,20,time,1}); break;
			case 1: bullets.push_back({lebar-1,rand()%(tinggi-2),ACS_LARROW,ACS_HLINE,i,5,time,1}); break;
			case 2: bullets.push_back({rand()%(lebar-2),tinggi-1,ACS_UARROW,ACS_VLINE,i,5,time,1}); break; 
			case 3: bullets.push_back({0,rand()%(tinggi-2),ACS_RARROW,ACS_HLINE,i,20,time,1}); break;
		}
		mvwaddch(gameplay,bullets[bullets.size()-1].y,bullets[bullets.size()-1].x,bullets[bullets.size()-1].c);
		refresh();
		wrefresh(gameplay);
		box(gameplay,0,0);
	}
	//}
//	}
}
bool enemy_two_shot(vector<bullet> &bullets,unsigned long long int time, mychar &mc,WINDOW* gameplay, int i) {
//	for (int i = 0; i < bullets.size(); i++) {
//		mvprintw(i+1,130,"%d",bullets[i].x);
//		mvprintw(i+1,135,"%d",bullets[i].y);
//		mvprintw(i+1,140,"%d",bullets[i].time+bullets[i].jeda);
//		//mvprintw(1,95,"%d",time);
//		refresh();
	//if (bullets[i].time+bullets[i].jeda<=time) {
//	bullets[i].time = time;
	if (bullets[i].step == 1) {
		mvwaddch(gameplay,bullets[i].y,bullets[i].x,bullets[i].fl);
		wrefresh(gameplay);
		bullets[i].jeda = 125;
		refresh();
		bullets[i].step++;
	} else if (bullets[i].step == 2) {
		mvwaddch(gameplay,bullets[i].y,bullets[i].x,' ');
		bullets.erase(bullets.begin() + i);
		wrefresh(gameplay);
		refresh();
	}
	return hitCheck(bullets[i].x,bullets[i].y,mc,gameplay);
//}
//	}
}
void enemy_two_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay) {
	//for (enem &i: enemys) {
//	mvprintw(1,1,"%d",i.time);
//	refresh();
	//if (i.time+i.delay <= time) {
	//i.time = time;
	if (rand()%100>=0) {
		int x = 1+rand()%(lebar-2),
			y = 1+rand()%(tinggi-2);
		bullets.push_back({x,y,ACS_BULLET,ACS_DIAMOND,i,100,time,2,1});
		mvwaddch(gameplay,y,x,ACS_BULLET);
		wrefresh(gameplay);
	}
	//}
	//}
}



bool enemy_shot(vector<bullet> &bullets,unsigned long long int time,mychar &mc,WINDOW* gameplay) {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].time+bullets[i].jeda<=time) {
			bullets[i].time = time;
			if (bullets[i].type == 1) {
				return enemy_one_shot(bullets,time,mc,gameplay,i);
			}
			else if (bullets[i].type == 2) {
				return enemy_two_shot(bullets,time, mc, gameplay, i);
			}
		}
	}
}
//bool enemy_shot(vector<bullet> &bullets,unsigned long long int time,mychar &mc,WINDOW* gameplay) {
//	for (int i = 0; i < bullets.size(); i++) {
//		if (bullets[i].time+bullets[i].jeda<=time) {
//			bullets[i].time = time;
//			if (bullets[i].type == 1) {
//				return enemy_one_shot(bullets,time,mc,gameplay,i);
//			}
//			else if (bullets[i].type == 2) {
//				return enemy_two_shot(bullets,time, mc, gameplay, i);
//			}
//		}
//	}
//}
bool enemy_spawnshot(vector<bullet> &bullets,vector<enem> &enemys,unsigned long long int time,WINDOW* gameplay) {
	for (enem &i: enemys) {
		if (i.time+i.delay <= time) {
			i.time = time;
			if (i.type == 1) {
				return enemy_one_spawnshot(bullets,i,time,gameplay);
			}
			else if (i.type == 2) {
				return enemy_two_spawnshot(bullets,i,time,gameplay);
			}
		}
	}
}
//bool enemy_spawnshot(vector<bullet_one> &bullets,vector<enem> &enemys,unsigned long long int time,WINDOW* gameplay) {
//	for (enem &i: enemys) {
//		if (i.time+i.delay <= time) {
//			i.time = time;
//			if (i.type == 1) {
//				return enemy_one_spawnshot(bullets,i,time,gameplay);
//			}
//			else if (i.type == 2) {
//				return enemy_two_spawnshot(bullets,i,time,gameplay);
//			}
//		}
//	}
//}
#endif
