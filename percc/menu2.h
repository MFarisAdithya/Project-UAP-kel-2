#ifndef MENU_H

#include <iostream> // cin cout
#include <fstream> // untuk membuat file txt
#include <ncurses/curses.h>
#include <string> //untuk menyimpan kalimat di string
#include <cstdlib> //Mengonversi string ke integer
#include <cstring> //string berbasis array karakter
#include <vector> //flexibel array
#include <thread> // delay

using namespace std;
void loading(int hw);
string input(int a, int b, int inp, WINDOW* menu);
void login();
void registration();
int gameover();
void loading(int hw) {
	mvprintw(17, 75, "Loading...");
	for (int i = 0; i < hw; i++) {
		for (int i = 0; i < 55; i++) {
	        start_color(); 
	        init_pair(1, COLOR_CYAN, COLOR_BLACK);
	        attron(COLOR_PAIR(1));
	       mvaddch(20, 50 + i, ACS_CKBOARD);
	        attroff(COLOR_PAIR(1));
	        refresh();
	        napms(10);
	    }
		 mvprintw(20, 50, "                                                          ");
		 clear();
		 refresh();
	}
}
string input(int a, int b, int inp, WINDOW* menu) {
	noecho();
    curs_set(1);
    box(menu,0,0);
    //mvgetnstr(a, b, inp, c);
    string ret;
    int i = 0;
    wmove(menu,a,b);
    while(true) {
    	wmove(menu,a,b+i);
    	int me = wgetch(menu);
    	if (me == 8) {
    		if (i == 0) {
    			waddch(menu,' ');
    			wmove(menu,a,b+i-1);
    			continue;
			}
    		ret.pop_back();
    		i--;
    		wmove(menu,a,b+i);
    		waddch(menu,' ');
    		continue;
		} else if (i==inp) {
			mvwaddch(menu,a,b+i,' ');
			continue;
		} else if (me == 10) break;
		ret.push_back(me);
		mvwaddstr(menu,a,b,ret.c_str());
		i++;
		wrefresh(menu);
	}
    //wnoecho(menu);
    curs_set(0);
    return ret;
}
void registration() {
	const char *opsi[] = {
	    "Enter username:",
	    "Enter password:",
	    "Register",
    };
    int jumlahopsi = sizeof(opsi) / sizeof(char *);
	WINDOW* regis = newwin(6,30,6+jumlahopsi,10);
	box(regis,0,0);
	ofstream myFile, accList;
	string username;
	string password;

    bool exist = false;
	keypad(regis, TRUE);
	nodelay(regis, FALSE);
	
	
    int pilihanTerpilih = 0;
    int pilihan = -1; 
    while (1) {
		for (int i = 0; i < jumlahopsi; i++) {
			if (pilihanTerpilih == i) wattron(regis,COLOR_PAIR(2));
			mvwprintw(regis,i+1,1,opsi[i]);
			wrefresh(regis);
			if (pilihanTerpilih == i) wattroff(regis,COLOR_PAIR(2));
		}
        int tombol = wgetch(regis); // Membaca input dari keyboard
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = jumlahopsi-1; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
            break;

            case KEY_DOWN:
                if (pilihanTerpilih == jumlahopsi-1) {
                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
                } else {
                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
                }
            break;

            case 10: // Enter
                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
            break;
        }
        if (pilihan == 0) { // Pilih "Keluar"
        	mvwprintw(regis,1,16,"        ");
        	//memset(userLog, 0, sizeof(userLog));
			//char userLog1[8];
        	//userLog = userLog1;
        	//for (int i = 0; i < 8; i++) userLog[i] = userLog1[i];
            username = input(1,16,8,regis);
			pilihan = -1; // Keluar dari loop jika "Keluar" dipilih
        } else 
        if (pilihan == 1) { //pilih Register
        	mvwprintw(regis,2,16,"        ");
        	//memset(passLog, 0, sizeof(passLog));
			//char passLog1[8];
        	//passLog = passLog1;
        	//for (int i = 0; i < 8; i++) passLog[i] = passLog1[i];
			password = input(2,16,8,regis); // masuk ke fungsi register
			pilihan = -1; //mengembalikan nilai pilihan
		} else
        if (pilihan == 2) {
        	// Memeriksa apakah username ada di daftar
        	clear();
        	myFile.open(username + ".txt");
		    myFile << password << endl;  
		    myFile << 0;               
		    myFile.close();
		    accList.open("ListAccount.txt", ios::app);
		    accList << username << endl;
		    accList.close();
		    clear();
		    refresh();
		    delwin(regis);
			//point(exist, UserLog);
		 	loading(1);
		    mvprintw(13,45,"Registration Successfully");
		    getch();
		    clear();
		    refresh();
	    	pilihan = -1;
	    	return;
	    }
    }
	
}
void login() {
	const char *opsi[] = {
	    "Enter username:",
	    "Enter password:",
	    "Sign in",
	    "Sign up",
    };
    
    int jumlahopsi = sizeof(opsi) / sizeof(char *);
	WINDOW* menu = newwin(6,30,6+jumlahopsi,10);
	box(menu,0,0);
	ifstream myFile;
    string userLog, passLog;
    string  userData, storedPass;

    bool exist = false;
	keypad(menu, TRUE);
	nodelay(menu, FALSE);
	
	
    int pilihanTerpilih = 0; // Indeks pilihan pertama
    int pilihan = -1; 
    while (1) {
         // Menampilkan menu
        //kotak(19,71,24,100);
		for (int i = 0; i < jumlahopsi; i++) {
			if (pilihanTerpilih == i) wattron(menu,COLOR_PAIR(2));
			mvwprintw(menu,i+1,1,opsi[i]);
			wrefresh(menu);
			if (pilihanTerpilih == i) wattroff(menu,COLOR_PAIR(2));
		}
        int tombol = wgetch(menu); // Membaca input dari keyboard
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = jumlahopsi-1; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
            break;

            case KEY_DOWN:
                if (pilihanTerpilih == jumlahopsi-1) {
                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
                } else {
                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
                }
            break;

            case 10: // Enter
                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
            break;
        }
        if (pilihan == 0) { // Pilih "Keluar"
        	mvwprintw(menu,1,16,"        ");
            userLog = input(1,16,8,menu);
			pilihan = -1; // Keluar dari loop jika "Keluar" dipilih
        } else 
        if (pilihan == 1) { //pilih Register
        	mvwprintw(menu,2,16,"        ");
			passLog = input(2,16,8,menu); // masuk ke fungsi register
			pilihan = -1; //mengembalikan nilai pilihan
		} else
        if (pilihan == 2) {
        	// Memeriksa apakah username ada di daftar
        	clear();
		    myFile.open("ListAccount.txt");
		    while (myFile >> userData) {
		        if (userData == userLog) {
		            exist = true;
		            break;
		        }
		    }
		    myFile.close();
		    string UserLog = userLog;
		    string PassLog = passLog;
		  
		    // Memeriksa apakah password benar
		    if (exist) {
		    	exist= false;
		    	myFile.open(UserLog + ".txt");
		    	myFile >> storedPass;	
		    	if (storedPass == PassLog){
		    		exist = true;
				}
			}
		    myFile.close();
		    loading(1);
		    if (exist) return;
		    else {
		    	clear();
		    	mvprintw(11,40,"----------------------------------------");
		        mvprintw(12,40,"                LOGIN ERROR             ");
		        mvprintw(13,40,"Please check your username and try again");
		        mvprintw(14,40,"----------------------------------------");
		        getch();
		        clear();
		        refresh();
		        box(menu,0,0);
			}
		 
	    	pilihan = -1;
	    } else
        if (pilihan == 3) {
        	loading(1);
        	registration();
        	pilihan = -1;
        	box(menu,0,0);
		}
    }
}
int gameover() {
	const char *opsi[] = {
	    "TRY AGAIN",
	    "MAIN MENU",
	    "EXIT GAME",
    };
    
    int jumlahopsi = sizeof(opsi) / sizeof(char *);
	WINDOW* gameOver = newwin(6,30,6+jumlahopsi,10);
	box(gameOver,0,0);

	keypad(gameOver, TRUE);
	nodelay(gameOver, FALSE);
	
	
    int pilihanTerpilih = 0; // Indeks pilihan pertama
    int pilihan = -1; 
	//loading(3);
	//game();
	//gameover();
	
	//getch();
    while (1) {
         // Menampilkan menu
        //kotak(19,71,24,100);
		for (int i = 0; i < jumlahopsi; i++) {
			if (pilihanTerpilih == i) wattron(gameOver,COLOR_PAIR(2));
			mvwprintw(gameOver,i+1,1,opsi[i]);
			wrefresh(gameOver);
			if (pilihanTerpilih == i) wattroff(gameOver,COLOR_PAIR(2));
		}
        int tombol = wgetch(gameOver); // Membaca input dari keyboard
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = jumlahopsi-1; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
            break;

            case KEY_DOWN:
                if (pilihanTerpilih == jumlahopsi-1) {
                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
                } else {
                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
                }
            break;

            case 10: // Enter
                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
            break;
        }
        if (pilihan == 0) { // Pilih "Keluar"
        	delwin(gameOver);
        	return 2;
        } else 
        if (pilihan == 1) { //pilih Register
        	delwin(gameOver);
        	return 1;
		} else
        if (pilihan == 2) {
        	delwin(gameOver);
        	return 3;
	    }
    }
}
#endif
