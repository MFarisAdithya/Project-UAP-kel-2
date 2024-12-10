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
//#include "game3.h"
//#include "gameover.h"
//#include "enemy.h"
//#include "apasi.h"
#include "menu.h"
using namespace std;


int main() {
    initscr();
    cb();
    noecho();
    cbreak();
	curs_set(0);
	
    keypad(stdscr, TRUE); 
	//loading(1);
	start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
	WINDOW *menu = newwin(12, 12, 12, 12);
    box(menu,0,0);
	wrefresh(menu);
	login();
	//game();
	//nodelay(stdscr, FALSE);
	//gameover();
    endwin(); 
    return 0;
}

//curs_set(0);
//	
//    keypad(stdscr, TRUE);
//    const char *opsi[] = {
//        "Registration",
//        "Login",
//        "Keluar"
//    };
//
//    int jumlahopsi = sizeof(opsi) / sizeof(char *);
//    int pilihanTerpilih = 0; // Indeks pilihan pertama
//    int pilihan = -1; 
//	//loading(5);
//	game();
//	nodelay(stdscr, FALSE);
//	gameover();
//	getch();
//    /*while (1) {
//         // Menampilkan menu0
//		for (int i = 0; i < 3; i++) {
//			if (pilihanTerpilih == i) attron(A_REVERSE);
//			mvprintw(i+12,55, opsi[i]);
//			refresh();
//			if (pilihanTerpilih == i) attroff(A_REVERSE);
//		}
//		pilihanTerpilih;
//        int tombol = wgetch(stdscr); // Membaca input dari keyboard
//        switch (tombol) {
//            case KEY_UP:
//                if (pilihanTerpilih == 0) {
//                    pilihanTerpilih = 2; // Kembali ke pilihan terakhir
//                } else {
//                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
//                }
//                break;
//
//            case KEY_DOWN:
//                if (pilihanTerpilih == 2) {
//                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
//                } else {
//                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
//                }
//                break;
//
//            case 10: // Enter
//                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
//                break;
//        }
//
//        refresh(); 
//        if (pilihan == 2) { // Pilih "Keluar"
//            break; // Keluar dari loop jika "Keluar" dipilih
//        } else 
//        if (pilihan == 0) { //pilih Register
//        	loading(1);
//			registration(); // masuk ke fungsi register
//			
//			pilihan = -1; //mengembalikan nilai pilihan
//		} else
//        if (pilihan == 1) {
//        	loading(1);
//        	login();
// 
//        	pilihan = -1;
//        	
//		}
//    }*/
//    endwin(); // Mengakhiri ncurses
//    return 0;
//}
