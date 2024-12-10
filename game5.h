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
int startX = 50, startY = 15, lebar = 40, tinggi = 20, cLebar = 0 , cTinggi = 0;
int health = 3;

struct mychar {
	int x = 20;
	int y = 10;
	int hp = 5;
	int time = 0;
	int point1 = 0;
	int point2 = 0;
};
struct enem {
	int idx;
	unsigned long long int time;
	int delay;
	int type;
};
struct bullet {
	int x;
	int y;
	chtype c;
	chtype fl;
	enem *parent;
	int jeda;
	unsigned long long int time;
	bool isD;
	int type;
	int step = 0;
};
struct sBlock {
	chtype c;
	int panj;
	int posX;
	int posY;
	int exce;
};

void printMoveMe(int &change,int plus,chtype &inv,WINDOW *gameplay, mychar &mc, vector<bullet> &bullets);
void moveMe(mychar &mc, WINDOW *gameplay, chtype &inv, vector<bullet> &bullets,vector<sBlock> &blocks);
bool hitCheck(vector<bullet> &bullets, mychar &mc, WINDOW* gameplay, chtype &inv);
bool block(int x, int y, vector<sBlock> &blocks);
void printBlock(vector<sBlock> &blocks, WINDOW* gameplay);

void enemy_one_shot(vector<bullet> &bullets, unsigned long long int time,mychar &mc,WINDOW* gameplay, chtype &inv);
void enemy_one_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay);
void enemy_two_shot(vector<bullet> &bullets,unsigned long long int time, mychar &mc,WINDOW* gameplay, chtype &inv);
void enemy_two_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay);
//void enemy_three_shot(vector<bullet> &bullets, vector<enem> &enemys, unsigned long long int time, mychar &mc,WINDOW* gameplay, int i, chtype &inv);
//void enemy_three_spawnshot(vector<sBlock> &blocks, vector<bullet> &bullets, enem &i, unsigned long long int time, WINDOW* gameplay);

void enemy_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc, WINDOW* gameplay, chtype &inv);
void enemy_spawnshot(vector<bullet> &bullets,vector<enem> &enemys,vector<sBlock> &blocks,unsigned long long int time,WINDOW* gameplay);


void game() {
	WINDOW *gameplay = newwin(tinggi, lebar, startY, startX);
	nodelay(gameplay, TRUE);
    keypad(gameplay, TRUE);
	box(gameplay,0,0);
	
	unsigned long long int time = 0;
	
	vector<enem> enemys;
	vector<bullet> bullets;
	vector<sBlock> blocks;
	wrefresh(gameplay);
	box(gameplay,0,0);
	int mex=20, mey=10;
	
	mychar mc;
	enem test;
	mvprintw(2,2,"HP: ");
	for (int i=0; i < mc.hp; i++) mvaddch(2,6+i,ACS_BLOCK);
	for (int i = 0; i < lebar; i++) cLebar += i;
	for (int i = 0; i < tinggi; i++) cTinggi += i;
	chtype inv = ' ';
	
	enemys.push_back({0,time,25,1});
	enemys.push_back({1,time,10,2});
	//enemys.push_back({2,time,10,3});
	
	blocks.push_back({' ',lebar-1,0,0});
	blocks.push_back({' ',tinggi-1,0,0});
	blocks.push_back({' ',lebar-1,0,tinggi-1});
	blocks.push_back({' ',tinggi-1,lebar-1,0});
	
	while(true) {
		int x, y;
		enemy_spawnshot(bullets,enemys,blocks,time,gameplay);
		enemy_shot(bullets,time,mc,gameplay,inv);
		moveMe(mc, gameplay, inv, bullets, blocks);
		if(hitCheck(bullets,mc,gameplay,inv)) return;
		time++;
		mvwprintw(gameplay,mc.y,mc.x,"X");
		mvprintw(1,150,"%llu",time);
		refresh();
		napms(10);
		box(gameplay,0,0);
		wrefresh(gameplay);
	}	
}

void printBlock(vector<sBlock> &blocks, WINDOW* gameplay) {
	for (sBlock i: blocks) {
		if (i.c != ' ') {
			if (i.c == ACS_HLINE) {
				for (int j = 0; j < i.panj; j++) {
					if (i.posX+j != i.exce) mvwaddch(gameplay,i.posY,i.posX+j,ACS_HLINE);
					else {
						wattron(gameplay,COLOR_PAIR(1));
						mvwaddch(gameplay,i.posY,i.posX+j,ACS_HLINE);
						wattroff(gameplay,COLOR_PAIR(1));
					}
				}
			} else if (i.c == ACS_VLINE) {
				for (int j = 0; j < i.panj; j++) {
					if (i.posY+j != i.exce) mvwaddch(gameplay,i.posY+j,i.posX,ACS_VLINE);
					else {
						wattron(gameplay,COLOR_PAIR(1));
						mvwaddch(gameplay,i.posY+j,i.posX,ACS_VLINE);
						wattroff(gameplay,COLOR_PAIR(1));
					}
				}
			}
		}
	}
}
bool hitCheck(vector<bullet> &bullets, mychar &mc, WINDOW* gameplay, chtype &inv) {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].x == mc.x && bullets[i].y == mc.y) {
			if (!(bullets[i].type==2&&!bullets[i].isD&&bullets[i].step==1)) {
				if (bullets[i].isD) {
					if (bullets[i].type==1) mc.point1++;
					else mc.point2++;
					//for (int i = 0; i < enemys.size(); i++) if (&enemys[i] == bullets[i].parent) enemys.erase(enemys.begin() + i);
				} else {
					mc.hp--;
					mvaddch(2,6+mc.hp,' ');
					refresh();
						
					mvprintw(8,100,"%d",mc.hp);
					refresh();
					if (mc.hp <= 0) {
						nodelay(gameplay, FALSE);
						return true;
					}
				}
				bullets.erase(bullets.begin() + i);
				mvprintw(5,100,"%d",mc.point1);
				mvprintw(5,105,"%d",mc.point2);
				refresh();
			} else {
				inv = bullets[i].c;
				mvaddch(10,2,inv);
				refresh();
			}
		}
	}
	return false;
}
void printMoveMe(int &change,int plus,chtype &inv,WINDOW *gameplay, mychar &mc, vector<bullet> &bullets) {
	if (inv != ' ') mvwaddch(gameplay,mc.y,mc.x,inv);
	else mvwaddch(gameplay,mc.y,mc.x,' ');
	inv = ' ';
	change += plus;
	mvwaddch(gameplay,mc.y,mc.x,'X');
}
void moveMe(mychar &mc, WINDOW *gameplay, chtype &inv, vector<bullet> &bullets,vector<sBlock> &blocks) {
	int inp = wgetch(gameplay);
	switch(inp) { 
		case 259: if (block(mc.x,mc.y-1,blocks)) printMoveMe(mc.y,-1,inv,gameplay,mc,bullets); break;
		case 261: if (block(mc.x+1,mc.y,blocks)) printMoveMe(mc.x,1,inv,gameplay,mc,bullets); break;
		case 258: if (block(mc.x,mc.y+1,blocks)) printMoveMe(mc.y,1,inv,gameplay,mc,bullets); break;
		case 260: if (block(mc.x-1,mc.y,blocks)) printMoveMe(mc.x,-1,inv,gameplay,mc,bullets); break;
	}
}
bool block(int x, int y, vector<sBlock> &blocks) {
	if (x <= 0 || x >= lebar-1) return false;
	else if (y <= 0 || y >= tinggi-1) return false;
}


void enemy_one_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay) {
	if (rand()%100>=0) {
		int x, y;
		chtype c, fl;
		bool isD = !(rand()%10);
		switch (rand()%4) {
			case 0: x = rand()%(lebar-2);
					y = 0;
					c = ACS_DARROW;
					fl = ACS_VLINE;
					break;
			case 1: x = lebar-1;
					y = rand()%(tinggi-2);
					c = ACS_LARROW;
					fl = ACS_HLINE;
					break;
			case 2: x = rand()%(lebar-2);
					y = tinggi-1;
					c = ACS_UARROW;
					fl = ACS_VLINE;
					break;
			case 3: x = 0;
					y = rand()%(tinggi-2);
					c = ACS_RARROW;
					fl = ACS_HLINE;
					break;
		}
		bullets.push_back({x,y,c,fl,&i,10,time,isD,1});
		if (isD) {
			wattron(gameplay,COLOR_PAIR(1));
			mvwaddch(gameplay,y,x,c);
			wattroff(gameplay,COLOR_PAIR(1));
		} else mvwaddch(gameplay,y,x,c);
		refresh();
		wrefresh(gameplay);
		box(gameplay,0,0);
	}
}
void enemy_one_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc,WINDOW* gameplay,int i, chtype &inv) {
	mvwaddch(gameplay,bullets[i].y,bullets[i].x,' ');
	if (bullets[i].c==ACS_DARROW) bullets[i].y++; else
	if (bullets[i].c==ACS_LARROW) bullets[i].x--; else
	if (bullets[i].c==ACS_UARROW) bullets[i].y--; else
	if (bullets[i].c==ACS_RARROW) bullets[i].x++;
	
	if (bullets[i].isD) {
		wattron(gameplay,COLOR_PAIR(1));
		mvwaddch(gameplay,bullets[i].y,bullets[i].x,bullets[i].c);
		wattroff(gameplay,COLOR_PAIR(1));
	} else mvwaddch(gameplay,bullets[i].y,bullets[i].x,bullets[i].c);
	wrefresh(gameplay);
	if (bullets[i].x<=0 || bullets[i].y <= 0 || bullets[i].x >= lebar+1 || bullets[i].y >= tinggi+1) {
		bullets.erase(bullets.begin() + i);
	}
}

void enemy_two_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay) {
	if (rand()%100>=0) {
		int x = 1+rand()%(lebar-2),
			y = 1+rand()%(tinggi-2);
		bool isD = !(rand()%10);
		bullets.push_back({x,y,ACS_BULLET,ACS_DIAMOND,&i,100,time,isD,2,1});
		if (isD) {
			wattron(gameplay,COLOR_PAIR(1));
			mvwaddch(gameplay,y,x,ACS_BULLET);
			wattroff(gameplay,COLOR_PAIR(1));
		} mvwaddch(gameplay,y,x,ACS_BULLET);
		wrefresh(gameplay);
	}
}
void enemy_two_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc,WINDOW* gameplay, int i, chtype &inv) {
	if (bullets[i].step == 1) {
		if (bullets[i].isD) {
			wattron(gameplay,COLOR_PAIR(1));
			mvwaddch(gameplay, bullets[i].y, bullets[i].x, bullets[i].fl);
			wattroff(gameplay,COLOR_PAIR(1));
		} else mvwaddch(gameplay, bullets[i].y, bullets[i].x, bullets[i].fl);
		wrefresh(gameplay);
		bullets[i].jeda = bullets[i].isD?300:100;
		refresh();
		bullets[i].step++;
	} else if (bullets[i].step == 2) {
		mvwaddch(gameplay,bullets[i].y,bullets[i].x,' ');
		bullets.erase(bullets.begin() + i);
		wrefresh(gameplay);
		refresh();
	}
}

void enemy_spawnshot(vector<bullet> &bullets,vector<enem> &enemys, vector<sBlock> &blocks, unsigned long long int time,WINDOW* gameplay) {
	for (enem &i: enemys) {
		if (i.time+i.delay <= time) {
			i.time = time;
			if (i.type == 1) enemy_one_spawnshot(bullets,i,time,gameplay);
			else if (i.type == 2) enemy_two_spawnshot(bullets,i,time,gameplay);
			
		}
	}
}
void enemy_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc, WINDOW* gameplay, chtype &inv) {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].time+bullets[i].jeda<=time) {
			bullets[i].time = time;
			if (bullets[i].type == 1) enemy_one_shot(bullets,time,mc,gameplay,i,inv);
			else if (bullets[i].type == 2) enemy_two_shot(bullets, time, mc, gameplay, i, inv);
		}
	}
}

#endif
