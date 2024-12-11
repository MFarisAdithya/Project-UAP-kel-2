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
#include <time.h>
#include <windows.h>
#include "game5.h"
//#include "gameover.h"
//#include "enemy.h"
#include "menu2.h"
using namespace std;
void playmusic(const char * musicFile, DWORD flags = SND_ASYNC | SND_LOOP) {
  PlaySound(TEXT(musicFile), NULL, flags);
}

//void stopmusic() {
//  PlaySound(NULL, 0, SND_PURGE);
//}

int main() {
	int keluar = 3;
    initscr();
    //cb();
    noecho();
    cbreak();
	curs_set(0);
	playmusic("musik.wav");
    //keypad(stdscr, TRUE); 
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    
	//login();
	//keluar = getch();
	while (true) {
		if (keluar <= 1) login();
		clear();
		refresh();
		if (keluar <= 2) game();
		clear();
		refresh();
		keluar = gameover();
		clear();
		refresh();
		if (keluar == 3) break;
	}
    endwin(); 
    cout << "TERIMA KASIH SUDAH BERMAIN" << endl << "SEMOGA DAPAT NILAI A" << endl << keluar;
    while (true) {
    	Sleep(100);
	}
    return 0;
}

