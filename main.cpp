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
#include "game5.h"
//#include "gameover.h"
//#include "enemy.h"
#include "menu.h"
using namespace std;


int main() {
    initscr();
    cb();
    noecho();
    cbreak();
	curs_set(0);
    keypad(stdscr, TRUE); 
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    
	login();
	game();
    endwin(); 
    return 0;
}
