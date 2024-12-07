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
#include "game3.h"
#include "gameover.h"
#include "enemy.h"
using namespace std;

void point(bool exist,string ul);
void login();
void registration();
void cb();
void loading(int hw);
void input(int a, int b, char* inp, int c);



int main() {
    initscr();
    cb();
    clear();
    noecho();
    cbreak();
    
	curs_set(0);
	
    keypad(stdscr, TRUE);
	//box(stdscr,1,1);
    // Daftar pilihan menu
    const char *opsi[] = {
        "Registration",
        "Login",
        "Keluar"
    };

    int jumlahopsi = sizeof(opsi) / sizeof(char *);
    int pilihanTerpilih = 0; // Indeks pilihan pertama
    int pilihan = -1; 
	//loading(5);
	game();
	nodelay(stdscr, FALSE);
	gameover();
	getch();
    /*while (1) {
         // Menampilkan menu
		for (int i = 0; i < 3; i++) {
			if (pilihanTerpilih == i) attron(A_REVERSE);
			mvprintw(i+12,55, opsi[i]);
			refresh();
			if (pilihanTerpilih == i) attroff(A_REVERSE);
		}
		pilihanTerpilih;
        int tombol = wgetch(stdscr); // Membaca input dari keyboard
        switch (tombol) {
            case KEY_UP:
                if (pilihanTerpilih == 0) {
                    pilihanTerpilih = 2; // Kembali ke pilihan terakhir
                } else {
                    --pilihanTerpilih; // Pindah ke pilihan sebelumnya
                }
                break;

            case KEY_DOWN:
                if (pilihanTerpilih == 2) {
                    pilihanTerpilih = 0; // Kembali ke pilihan pertama
                } else {
                    ++pilihanTerpilih; // Pindah ke pilihan berikutnya
                }
                break;

            case 10: // Enter
                pilihan = pilihanTerpilih; // Menyimpan pilihan yang dipilih
                break;
        }

        refresh(); 
        if (pilihan == 2) { // Pilih "Keluar"
            break; // Keluar dari loop jika "Keluar" dipilih
        } else 
        if (pilihan == 0) { //pilih Register
        	loading(1);
			registration(); // masuk ke fungsi register
			
			pilihan = -1; //mengembalikan nilai pilihan
		} else
        if (pilihan == 1) {
        	loading(1);
        	login();
 
        	pilihan = -1;
        	
		}
    }*/
    endwin(); // Mengakhiri ncurses
    return 0;
}

void login() {
	refresh();
    ifstream myFile;
    char userLog[100], passLog[100];
    string  userData, storedPass;

    bool exist = false;

	cb();
	//echo();
    mvprintw(9,45,"----------->LOGIN<-----------");
    mvprintw(11,45, "Enter username: ");
    //mvgetnstr(11,61,userLog,99);
    input(11,61,userLog,99);

    mvprintw(12,45,"Enter password: ");
    //mvgetnstr(12,61,passLog,99);
    input(12,61,passLog,99);
    //noecho();


    // Memeriksa apakah username ada di daftar
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
    if (exist){
    	exist= false;
    	myFile.open(UserLog + ".txt");
    	myFile >> storedPass;	
    	if (storedPass == PassLog){
    		exist = true;
		}
		
	}
	cb();
    myFile.close();
    loading(1);
	point(exist, UserLog);
   
}

void point(bool exist,string UserLog) {
	string storedPass;
	 if (exist) {

        if (exist) {
            mvprintw(13,55,"Login successful!");
            

            // Proses skor
            ifstream scoreCheck;
            ofstream scoreFile;
            char topScore[100];
			int currentScore;
            string tumbal;

            scoreCheck.open(UserLog + ".txt");
            getline(scoreCheck, tumbal);  
            scoreCheck >> currentScore;      
            scoreCheck.close();

            mvprintw(16,55,"Input top score: ");
            echo();
            //mvgetnstr(16,71,topScore,99);
            input(16,71,topScore,99);
            noecho();
			cb();
            // Update skor jika skor baru lebih tinggi
            if (atoi(topScore) > currentScore) {
                scoreFile.open(UserLog + ".txt");
                scoreFile << tumbal << endl;  // Simpan kembali password
                scoreFile << topScore;           // Simpan skor baru
                scoreFile.close();
                loading(3);
                mvprintw(14,55,"Your Top Score Is: %s",topScore);
            } else {
            	loading(3);
                mvprintw(14,55,"Your Top Score: %d", currentScore);
            }
        } else {
        	loading(3);
            mvprintw(19,45,"Incorrect password. Please try again."); 
        }
    } else {
        // Jika username tidak ditemukan
        mvprintw(11,40,"----------------------------------------");
        mvprintw(12,40,"                LOGIN ERROR             ");
        mvprintw(13,40,"Please check your username and try again");
        mvprintw(14,40,"----------------------------------------");
    }
    refresh();
    getch();
    cb();
    
}

void cb(){
	clear();
	box(stdscr,0,0);
}

void loading(int hw) {
	cb();
	mvprintw(10, 55, "Loading...");
	for (int i = 0; i < hw; i++) {
		for (int i = 0; i < 25; i++) {
	        mvaddch(12, 40 + i, ACS_CKBOARD); // Menambahkan karakter 'barl'
	        refresh();
	        napms(20); // Delay 150ms
	    }
		 mvprintw(12, 40, "                                                          ");
		 refresh();
	}
	cb();
}

void registration() {
	cb();
    ofstream myFile, accList;
    string userReg, passReg;
	char username[100];
	char password[100];
    mvprintw(9,45, "----------->REGISTER<-----------");
    mvprintw(11,45, "Enter username: ");
	echo();
    //mvgetnstr(11,61, username, 99);
    input(11,61,username,99);
    mvprintw(12,45,"Enter Password: ");
    //mvgetnstr(12,61, password, 99);
    input(12,61, password, 99);
    
	string me = username;
	string mu = password;
    // Membuat file untuk pengguna
    myFile.open(me + ".txt");
    myFile << mu << endl;  
    myFile << 0;               
    myFile.close();

    // Menambahkan username ke daftar akun
    accList.open("ListAccount.txt", ios::app);
    accList << me << endl;
    accList.close();
    cb();
    loading(1);
    mvprintw(13,45,"Registration Successfully");
    getch();
    cb();
}
void input(int a, int b, char *inp, int c) {
    echo();
    curs_set(1);
    
    mvgetnstr(a, b, inp, c);
//    string inpt;
//    int i = 0;
    
//    while (true) {
//    	int me = getch();
//    	mvprintw(6,6,"%d",i);
//    	if (me == 8) {
//    		if (i > 0) {
//    			i--;
//    			inpt.pop_back();
//	    		mvaddch(a,b+i,' ');		
//	    		mvaddch(a,b+i-1,inpt.back());
//	    			
//			}
//			continue;
//		}
//    	if (me == 10) {
//    		break;
//		}
//    	inpt.push_back(me);
//    	mvaddch(a,b+i,me);
//    	i++;
//	}
    noecho();
    curs_set(0);
}

