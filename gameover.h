#ifndef GAMEOVER_H
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

void gameover() {
	int awalx = 0, awaly = 0; // Inisialisasi posisi awal
    int lebar = 20, tinggi = 10;

    // Membuat window menu
    WINDOW *menu_win = newwin(tinggi, lebar, awaly, awalx);

    keypad(menu_win, TRUE);
	box(menu_win,0,0);
	wgetch(menu_win);
}

#endif
