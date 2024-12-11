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
	int pointT = 0;
	int pointH = 0;
	chtype c = ACS_LANTERN ;
	//char c = 'X' ;
};
struct enem {
	int idx;
	unsigned long long int time;
	int delay;
	int type;
	bool model1 = false;
	bool model2 = false;
	bool model3 = false;
};
struct bullet {
	int x;
	int y;
	chtype c;
	chtype fl;
	int jeda;
	unsigned long long int time;
	bool model1;
	bool model2;
	bool model3;
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

void printMove(vector<bullet> &bullets, mychar &mc, WINDOW* gameplay);
void printMoveMe(int &change,int plus,chtype &inv,WINDOW *gameplay, mychar &mc, vector<bullet> &bullets);
void moveMe(mychar &mc, WINDOW *gameplay, chtype &inv, vector<bullet> &bullets,vector<sBlock> &blocks);
bool hitCheck(vector<bullet> &bullets, mychar &mc, WINDOW* gameplay);
bool block(int x, int y, vector<sBlock> &blocks);
void printBlock(vector<sBlock> &blocks, WINDOW* gameplay);

void enemy_one_shot(vector<bullet> &bullets, unsigned long long int time,mychar &mc,WINDOW* gameplay);
void enemy_one_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,WINDOW* gameplay);
void enemy_two_shot(vector<bullet> &bullets,unsigned long long int time, mychar &mc,WINDOW* gameplay);
void enemy_two_spawnshot(vector<bullet> &bullets,enem &i,unsigned long long int time,mychar &mc,WINDOW* gameplay);
//void enemy_three_shot(vector<bullet> &bullets, vector<enem> &enemys, unsigned long long int time, mychar &mc,WINDOW* gameplay, int i, chtype &inv);
//void enemy_three_spawnshot(vector<sBlock> &blocks, vector<bullet> &bullets, enem &i, unsigned long long int time, WINDOW* gameplay);

void enemy_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc, WINDOW* gameplay);
void enemy_spawnshot(vector<bullet> &bullets,vector<enem> &enemys,vector<sBlock> &blocks,unsigned long long int time,mychar &mc,WINDOW* gameplay);


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
		enemy_spawnshot(bullets,enemys,blocks,time,mc,gameplay);
		enemy_shot(bullets,time,mc,gameplay);
		moveMe(mc, gameplay, inv, bullets, blocks);
		if(hitCheck(bullets,mc,gameplay)) return;
		printMove(bullets, mc,gameplay);
		time++;
//		mvwprintw(gameplay,mc.y,mc.x,"X");
//		mvprintw(1,150,"%llu",time);
//		refresh();
		napms(10);
		//box(gameplay,0,0);
		//wrefresh(gameplay);
	}	
}
void printEnem() {
	
}
void printMove(vector<bullet> &bullets, mychar &mc, WINDOW* gameplay) {
	box(stdscr,0,0);
	refresh();
	wclear(gameplay);
	mvprintw(4,1,"                                                                                                                                ");
	for (bullet i: bullets) {
		if (i.isD) {
			wattron(gameplay,COLOR_PAIR(1));
			mvwaddch(gameplay,i.y,i.x,i.c);
			wattroff(gameplay,COLOR_PAIR(1));
		} else mvwaddch(gameplay,i.y,i.x,i.c);
	}
	mvwaddch(gameplay,mc.y,mc.x,mc.c);
	mvprintw(3,60,"HP");
	for (int i = 0; i < mc.hp; i++) mvaddch(4,60+i-(mc.hp/2),ACS_BLOCK);
	mvprintw(6,60,"POINT");
	mvprintw(7,60,"%d",mc.pointT);	
	mvprintw(8,60,"%d",mc.hp);	
	box(gameplay,0,0);
	wrefresh(gameplay);
}

bool hitCheck(vector<bullet> &bullets, mychar &mc, WINDOW* gameplay) {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].x == mc.x && bullets[i].y == mc.y && !(bullets[i].type==2&&!bullets[i].isD&&bullets[i].step==1)) {
			//if (!(bullets[i].type==2&&!bullets[i].isD&&bullets[i].step==1)) {
			if (bullets[i].isD) {
				if (bullets[i].type==1) {
					mc.point1++;
					if (bullets[i].model1) mc.point1++;
					if (bullets[i].model2) mc.point1++;
				}
				else {
					mc.point2++;
					if (bullets[i].model1) mc.point2++;
					if (bullets[i].model2) mc.point2++;
					if (bullets[i].model3) mc.point2++;
				}
				mc.pointT = mc.point1 + mc.point2;
				if ((int)mc.pointT/1 > mc.pointH) {
					mc.pointH++;
					mc.hp++;
				}
				//for (int i = 0; i < enemys.size(); i++) if (&enemys[i] == bullets[i].parent) enemys.erase(enemys.begin() + i);
			} else {
				mc.hp--;
				//mvaddch(2,6+mc.hp,' ');
				//refresh();
				if (mc.hp <= 0) {
					nodelay(gameplay, FALSE);
    				keypad(gameplay, FALSE);
    				delwin(gameplay);
					return true;
				}
			}
			bullets.erase(bullets.begin() + i);
			//}
//			else {
//				inv = bullets[i].c;
//			}
		}
	}
	return false;
}
//void printMoveMe(int &change,int plus,chtype &inv,WINDOW *gameplay, mychar &mc, vector<bullet> &bullets) {
//	if (inv != ' ') mvwaddch(gameplay,mc.y,mc.x,inv);
//	else mvwaddch(gameplay,mc.y,mc.x,' ');
//	inv = ' ';
//	change += plus;
//	mvwaddch(gameplay,mc.y,mc.x,'X');
//}
void moveMe(mychar &mc, WINDOW *gameplay, chtype &inv, vector<bullet> &bullets,vector<sBlock> &blocks) {
	int inp = wgetch(gameplay);
	switch(inp) { 
		case 259: if (block(mc.x,mc.y-1,blocks)) mc.y--;//printMoveMe(mc.y,-1,inv,gameplay,mc,bullets); 
		break;
		case 261: if (block(mc.x+1,mc.y,blocks)) mc.x++;//printMoveMe(mc.x,1,inv,gameplay,mc,bullets); 
		break;
		case 258: if (block(mc.x,mc.y+1,blocks)) mc.y++;//printMoveMe(mc.y,1,inv,gameplay,mc,bullets);
		break;
		case 260: if (block(mc.x-1,mc.y,blocks)) mc.x--;//printMoveMe(mc.x,-1,inv,gameplay,mc,bullets); 
		break;
	}
}
bool block(int x, int y, vector<sBlock> &blocks) {
	if (x <= 0 || x >= lebar-1) return false;
	else if (y <= 0 || y >= tinggi-1) return false;
}


void enemy_one_spawnshot(vector<bullet> &bullets,unsigned long long int time,enem &i,WINDOW* gameplay) {
	if (rand()%100>=0) {
		int x, y;
		chtype c, fl;
		bool isD = !(rand()%10);
		if (i.model1) {
			x = 1+rand()%(lebar-2);
			y = 1+rand()%(tinggi-2);
		} else {
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
		}
		bullets.push_back({
			x,
			y,
			c,
			fl,
			10,
			time,
			i.model1,
			i.model2,
			i.model3,
			isD,
			1
		});
		i.model1 = false;
		i.model2 = false;
		i.model3 = false;
//		if (isD) {
//			wattron(gameplay,COLOR_PAIR(1));
//			mvwaddch(gameplay,y,x,c);
//			wattroff(gameplay,COLOR_PAIR(1));
//		} else mvwaddch(gameplay,y,x,c);
		//refresh();
		//wrefresh(gameplay);
		//box(gameplay,0,0);
	}
}
void enemy_one_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc,WINDOW* gameplay,int i) {
	if (bullets[i].c==ACS_DARROW) bullets[i].y++; else
	if (bullets[i].c==ACS_LARROW) bullets[i].x--; else
	if (bullets[i].c==ACS_UARROW) bullets[i].y--; else
	if (bullets[i].c==ACS_RARROW) bullets[i].x++;
	if (bullets[i].model2) {
		int x=0,y=0;
		if (bullets[i].c==ACS_DARROW) y--; else
		if (bullets[i].c==ACS_LARROW) x++; else
		if (bullets[i].c==ACS_UARROW) y++; else
		if (bullets[i].c==ACS_RARROW) x--;
		bullets.push_back({bullets[i].x+x, bullets[i].y+y, ACS_HLINE, ACS_HLINE, bullets[i].jeda,time,false, false, false,false,1});
		bullets.push_back({bullets[i].x+x+x,bullets[i].y+y+y,ACS_HLINE,ACS_HLINE,bullets[i].jeda,time,false, false, false,false,1});
		bullets[i].model2 = false;
	}
//	if (bullets[i].isD) {
//		wattron(gameplay,COLOR_PAIR(1));
//		mvwaddch(gameplay,bullets[i].y,bullets[i].x,bullets[i].c);
//		wattroff(gameplay,COLOR_PAIR(1));
//	} else mvwaddch(gameplay,bullets[i].y,bullets[i].x,bullets[i].c);
//	wrefresh(gameplay);
	if (bullets[i].x<=0 || bullets[i].y <= 0 || bullets[i].x >= lebar+1 || bullets[i].y >= tinggi+1) {
		bullets.erase(bullets.begin() + i);
	}
}

void enemy_two_spawnshot(vector<bullet> &bullets,unsigned long long int time,mychar &mc,enem &i,WINDOW* gameplay) {
	if (rand()%100>=0) {
		int x, y;
		if (i.model1) {
			x = mc.x;
			y = mc.y;
		} else {
			x = 1+rand()%(lebar-2),
			y = 1+rand()%(tinggi-2);
		}
		bool isD = !(rand()%10);
		bullets.push_back({
			x,
			y,
			ACS_BULLET,
			ACS_DIAMOND,
			100,
			time,
			i.model1,
			i.model2,
			i.model3,
			isD,
			2,
			1
		});
		i.model1 = false;
		i.model2 = false;
		i.model3 = false;
//		if (isD) {
//			wattron(gameplay,COLOR_PAIR(1));
//			mvwaddch(gameplay,y,x,ACS_BULLET);
//			wattroff(gameplay,COLOR_PAIR(1));
//		} mvwaddch(gameplay,y,x,ACS_BULLET);
//		wrefresh(gameplay);
	}
}
void enemy_two_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc,WINDOW* gameplay, int i) {
	if (bullets[i].step == 1) {
//		if (bullets[i].isD) {
//			wattron(gameplay,COLOR_PAIR(1));
//			mvwaddch(gameplay, bullets[i].y, bullets[i].x, bullets[i].fl);
//			wattroff(gameplay,COLOR_PAIR(1));
//		} else mvwaddch(gameplay, bullets[i].y, bullets[i].x, bullets[i].fl);
		//wrefresh(gameplay);
		bullets[i].jeda = bullets[i].isD?300:100;
		bullets[i].c = bullets[i].fl;
		if (false) {
			bullets.push_back({bullets[i].x+1,bullets[i].y,ACS_DIAMOND,ACS_DIAMOND,100,time,false,false,bullets[i].model3,false,2,2});
			bullets.push_back({bullets[i].x-1,bullets[i].y,ACS_DIAMOND,ACS_DIAMOND,100,time,false,false,bullets[i].model3,false,2,2});
			bullets.push_back({bullets[i].x,bullets[i].y+1,ACS_DIAMOND,ACS_DIAMOND,100,time,false,false,bullets[i].model3,false,2,2});
			bullets.push_back({bullets[i].x,bullets[i].y-1,ACS_DIAMOND,ACS_DIAMOND,100,time,false,false,bullets[i].model3,false,2,2});
		}
//		refresh();
		bullets[i].step++;
	} else if (bullets[i].step == 2) {
		//mvwaddch(gameplay,bullets[i].y,bullets[i].x,' ');
		bullets.erase(bullets.begin() + i);
		chtype c;
		switch (rand()%4) {
			case 0: c = ACS_DARROW; break;
			case 1: c = ACS_UARROW; break;
			case 2: c = ACS_LARROW; break;
			case 3: c = ACS_RARROW; break;
		}
		bullets.push_back({
			bullets[i].x,
			bullets[i].y,
			c,
			c,
			10,
			time,
			false,
			false,
			false,
			!(rand()%10),
			1
		});
//		wrefresh(gameplay);
//		refresh();
	}
}

void enemy_spawnshot(vector<bullet> &bullets,vector<enem> &enemys, vector<sBlock> &blocks, unsigned long long int time,mychar &mc,WINDOW* gameplay) {
	for (enem &i: enemys) {
		if (i.time+i.delay <= time) {
			i.time = time;
			if (i.type == 1) {
				if (rand()%100<=-1) i.model1 = true;
				if (rand()%100<=-1) i.model2 = true;
				if (rand()%100<=-1) i.model3 = true;
				enemy_one_spawnshot(bullets,time,i,gameplay);
			} 
			else if (i.type == 2) {
				if (rand()%100<=-1) i.model1 = true;
				if (rand()%100<=-1) i.model2 = true;
				if (rand()%100<=-1) i.model3 = true;
				enemy_two_spawnshot(bullets,time,mc,i,gameplay);
			} 
			
		}
	}
}
void enemy_shot(vector<bullet> &bullets, unsigned long long int time, mychar &mc, WINDOW* gameplay) {
	for (int i = 0; i < bullets.size(); i++) {
		if (bullets[i].time+bullets[i].jeda<=time) {
			bullets[i].time = time;
			if (bullets[i].type == 1) enemy_one_shot(bullets,time,mc,gameplay,i);
			else if (bullets[i].type == 2) enemy_two_shot(bullets, time, mc, gameplay, i);
		}
	}
}

#endif
